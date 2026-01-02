#!/bin/bash

gcc -std=c23 -Wall -Wextra generator.c -o generator.out

if [[ $? == 0 ]]; then
   ./generator.out "."
   rm ./generator.out
fi
