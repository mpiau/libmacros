#!/bin/bash

gcc -std=c23 -Wall -Wextra tests/main.c -Iinclude/ -o tests.out

if [[ $? == 0 ]]; then
   ./tests.out
   rm ./tests.out
fi
