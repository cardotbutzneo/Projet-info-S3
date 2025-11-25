#!/bin/bash

if [ "$1" = "--arbo" ]; then
    ./bash/main.sh
elif [ "$1" = "-r" ] || [ -z "$1" ]; then
    make
elif [ "$1" = "-c" ] || [ "$1" = "--clean" ];then
make clean 
fi
