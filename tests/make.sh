#/bin/bash

mkdir ./tests/$1
echo "$2" > ./tests/$1/command.txt
./minishell -c "$2" > ./tests/$1/output.txt