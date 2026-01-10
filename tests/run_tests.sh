#!/bin/bash

gcc -std=c23 -Wall -Wextra -Werror main.c -I../include/ -o tests.out

if [[ $? == 0 ]]; then
   ./tests.out
   rm ./tests.out
fi
