#!/bin/bash
# flags="-fsanitize=undefined -fsanitize=bounds --std=c++20"
flags="--std=c++20"
arg=$1
file_name="${arg}.cpp"
target="build/${arg}.exe"
echo $arg
if [ $arg = "day4" ]
then
    file_name+=" md5.cpp"
fi
cmd="clang++ $flags $file_name -o $target"
echo $cmd
TIMEFORMAT=%R
time $cmd || exit 1
echo "-------------"
time "./${target}"