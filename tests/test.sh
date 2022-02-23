#/bin/bash

make -sC .
for folder in ./tests/*/
do
    name=$(basename $folder);
    path="./tests/$name";
    command_path="$path/command.txt";
    expected_path="$path/output.txt";
    actual_path="$path/actual.txt";
    command=$(cat $command_path);
    ./minishell -c "$command" > $actual_path;
    if cmp -s $actual_path $expected_path; then
        printf "\033[0;32m";
    else
        printf "\033[0;31m";
    fi
    echo "$name: $command\033[0;31m";
done