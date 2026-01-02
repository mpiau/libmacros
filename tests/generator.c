#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SJ_IMPL
#include "sj.h"


static void write_separator_line(FILE *const fp)
{
   fprintf(fp, "//================================================================================================\n");
}

static void write_file_header_comment(FILE *const fp, char const *configFilename)
{
   write_separator_line(fp);
   fprintf(fp, "// THIS FILE HAS BEEN GENERATED. PLEASE DO NOT MANUALLY MODIFY\n");
   fprintf(fp, "// -----------------------------------------------------------\n");
   fprintf(fp, "// Script used:   %s\n", program_invocation_name);
   fprintf(fp, "// Configuration: %s\n", configFilename);
   write_separator_line(fp);
   fprintf(fp, "\n");
}

// From Sj test
static bool eq(sj_Value const val, char const *s)
{
   size_t const len = val.end - val.start;
   return strlen(s) == len && !memcmp(s, val.start, len);
}

struct Member
{
   char name[64];
   uint64_t value;
   bool valueSpecified;
   char desc[64];
};
typedef struct Member Member;

struct ParserData
{
   char includeList[16][64];
   int  includeIdx;
   char enumName[64];
   char enumType[64];
   Member members[16]; // All these values are temporary for that PoC.
   int membersCount;
};
typedef struct ParserData ParserData;

static void pascal_to_snake_case(char *dest, char const *src)
{
   char const *const start = src;
   while (*src != '\0')
   {
      if (isupper(*src))
      {
         if (src != start)
         {
            *dest++ = '_';
         }
         *dest++ = tolower(*src++);
      }
      else
      {
         *dest++ = *src++;
      }
   }
}

static void write_fn_count(FILE *fp, ParserData const *data)
{
   char snakeCase[64] = {};
   pascal_to_snake_case(snakeCase, data->enumName);

   fprintf(fp, "\n// Returns the number of members in the enum\n");
   fprintf(fp, "[[nodiscard]] inline %s %s_count(void)\n", data->enumType, snakeCase);
   fprintf(fp, "{\n");
   fprintf(fp, "   return %i;\n", data->membersCount);
   fprintf(fp, "}\n\n");
}

/*
Fn declarations to generate:
[[nodiscard]] inline WindDirection wind_direction_default(void);

[[nodiscard]] inline bool wind_direction_is_contiguous(void);
[[nodiscard]] inline bool wind_direction_is_binary_mask(void);
[[nodiscard]] inline bool wind_direction_is_unique(void);
[[nodiscard]] inline bool wind_direction_contains(uint8_t v);

// Returns nullptr if given value is not valid.
[[nodiscard]] inline char const *wind_direction_member_name(WindDirection v);
// Short name doesn't contain the prefix WindDirection_
[[nodiscard]] inline char const *wind_direction_member_short_name(WindDirection v);
[[nodiscard]] inline char const *wind_direction_member_desc(WindDirection v);
*/

static void parse_file(char const *filename)
{
   FILE *const jsonFp = fopen(filename, "r");

   if (jsonFp == nullptr)
      return;

   fseek(jsonFp, 0L, SEEK_END);
   long const fileSize = ftell(jsonFp);
   fseek(jsonFp, 0L, SEEK_SET);

   char *const fileContent = malloc(fileSize + 1);

   fread(fileContent, sizeof(char), fileSize, jsonFp);
   fileContent[fileSize] = '\0';

   fclose(jsonFp);

   char const *fileExt = strrchr(filename, '.');
   int const filenameWithoutExtLength = fileExt - filename;

   char targetFilename[255] = {};
   sprintf(targetFilename, "%.*s_enum_generated.h", filenameWithoutExtLength, filename);

   FILE *const fpTarget = fopen(targetFilename, "w");
   if (fpTarget == nullptr)
      return;

   write_file_header_comment(fpTarget, filename);

   ParserData pData = {};
   // READ JSON FILE
   sj_Reader reader = sj_reader(fileContent, fileSize);
   sj_Value mainObj = sj_read(&reader);

   sj_Value key, value;
   while (sj_iter_object(&reader, mainObj, &key, &value))
   {
      if (eq(key, "include_list"))
      {
         sj_Value includeV;
         while (sj_iter_array(&reader, value, &includeV))
         {
            sprintf(pData.includeList[pData.includeIdx], "%.*s", (int)(includeV.end-includeV.start), includeV.start);
            pData.includeIdx += 1;
         }
      }
      else if (eq(key, "name"))
      {
         sprintf(pData.enumName, "%.*s", (int)(value.end-value.start), value.start);
      }
      else if (eq(key, "type"))
      {
         sprintf(pData.enumType, "%.*s", (int)(value.end-value.start), value.start);
      }
      else if (eq(key, "members"))
      {
         sj_Value arrayIt;
         while(sj_iter_array(&reader, value, &arrayIt))
         {
            sj_Value memberKey, memberValue;
            Member *const memberElem = &pData.members[pData.membersCount];

            // Init the enum value by applying contiguous logic
            if (pData.membersCount == 0)
               memberElem->value = 0;
            else
               memberElem->value = pData.members[pData.membersCount].value + 1;

            while (sj_iter_object(&reader, arrayIt, &memberKey, &memberValue))
            {
               if (eq(memberKey, "name"))
               {
                  sprintf(memberElem->name, "%.*s", (int)(memberValue.end-memberValue.start), memberValue.start);
               }
               else if (eq(memberKey, "desc"))
               {
                  sprintf(memberElem->desc, "%.*s", (int)(memberValue.end-memberValue.start), memberValue.start);
               }
               else if (eq(memberKey, "value"))
               {
                  memberElem->value = strtol(memberValue.start, nullptr, 10);
                  memberElem->valueSpecified = true;
               }
            }
            pData.membersCount += 1;
         }
      }
   }

   for (int idx = 0; idx < pData.includeIdx; ++idx)
   {
      fprintf(fpTarget, "#include %s\n", pData.includeList[idx]);
   }
   fprintf(fpTarget, "\n\n");
   fprintf(fpTarget, "enum %s", pData.enumName);
   if (pData.enumType[0] != '\0')
   {
      fprintf(fpTarget, " : %s", pData.enumType);
   }
   fprintf(fpTarget, "\n");

   // Enum Content
   fprintf(fpTarget, "{\n");

   for (int idx = 0; idx < pData.membersCount; ++idx)
   {
      Member const *member = &pData.members[idx];
      char const *prefix = (idx == 0) ? "     " : "   , ";
      fprintf(fpTarget, "%s%s_%s", prefix, pData.enumName, member->name);
      if (member->valueSpecified)
      {
         fprintf(fpTarget, " = %lu", member->value);
      }
      fprintf(fpTarget, "\n");
   }
   fprintf(fpTarget, "};\n");
   fprintf(fpTarget, "typedef enum %s %s;\n\n", pData.enumName, pData.enumName);

   write_fn_count(fpTarget, &pData);

   fclose(fpTarget);
}


static void find_enumgen_files(char const *dirpath)
{
   if (dirpath == nullptr)
      return;

   DIR *const dirStream = opendir(dirpath);
   if (dirStream == nullptr)
      return;

   struct dirent const *dirInfo = nullptr;
   while ((dirInfo = readdir(dirStream)) != nullptr)
   {
      if (strcmp(dirInfo->d_name, ".")  == 0
       || strcmp(dirInfo->d_name, "..") == 0)
      {
         continue;
      }

      if (dirInfo->d_type == DT_DIR)
      {
         chdir( dirInfo->d_name );
//         printf("--- Subfolder: %s/\n", dirInfo->d_name);
         find_enumgen_files( "." );
//         printf("--- Quitting folder: %s/\n", dirInfo->d_name);
         chdir( ".." );
         continue;
      }

//      printf("Checking file: %s\n", dirInfo->d_name);

      char const *fileExt = strrchr(dirInfo->d_name, '.');
      if (fileExt == nullptr || strcmp(fileExt, ".enum") != 0)
      {
         continue;
      }

      printf("Found file: %s\n", dirInfo->d_name);
      parse_file(dirInfo->d_name);
   }

   closedir( dirStream );
}

int main(int const argc, char **const argv)
{
   for (int argIdx = 1; argIdx < argc; ++argIdx)
   {
      find_enumgen_files(argv[argIdx]);
   }

   return 0;
}