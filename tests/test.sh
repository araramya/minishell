#/bin/bash

make -sC .
cat tests/commands.txt | while read -r cmd; do 
    if cmp -s <(bash -c "$cmd" 2>/dev/null) <(./minishell -c "$cmd" 2>/dev/null); then
        printf "\033[0;32m";
    else
        printf "\033[0;31m";
    fi
    printf "$cmd\033[0m\n";
done