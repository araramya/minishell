#/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

if norminette | grep -q KO; then
    printf $RED;
    else
    printf $GREEN;
fi

printf "Norminete Check$NC\n\n";
echo "Commands:";

make -sC .
cat tests/commands.txt | while read -r cmd; do 
    EXPECTED=$(bash -c "$cmd" 2>/dev/null);
    EXPECTED_CODE=$?;
    ACTUAL=$(./minishell -c "$cmd" 2>/dev/null);
    ACTUAL_CODE=$?;
    ERROR=1;

    if [ "$EXPECTED" == "$ACTUAL" ]; then
        if [ "$EXPECTED_CODE" == "$ACTUAL_CODE" ]; then
            ERROR=0;
        fi
    fi

    if [ "$ERROR" == "0" ]; then
        printf $GREEN;
    else
        printf $RED;
    fi
    printf "$cmd$NC\n";
done