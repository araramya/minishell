# Minishell

## Todo

A todo list from the subject.

- [x] Not interpret unclosed quotes or unspecified special characters like \ or ;.
- [x] Not use more than one global variable, think about it and be ready to explain why you do it.
- [x] Show a prompt when waiting for a new command.
- [x] Have a working History.
- [x] Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- [x] It must implement the builtins:
  - [x] echo with option -n
  - [x] cd with only a relative or absolute path
  - [x] pwd with no options
  - [x] export with no options
  - [x] unset with no options
  - [x] env with no options or arguments
  - [x] exit with no options
- [x] ’ inhibit all interpretation of a sequence of characters.
- [x] " inhibit all interpretation of a sequence of characters except for $.
- [ ] Redirections
  - [ ] < should redirect input.
  - [ ] > should redirect output.
  - [ ] “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
  - [ ] “>>” should redirect output with append mode.
- [ ] Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- [x] Environment variables ($ followed by characters) should expand to their values.
- [x] $? should expand to the exit status of the most recently executed foreground
      pipeline.
- [ ] ctrl-C ctrl-D ctrl-\ should work like in bash.
- When interactive:
  - [ ] ctrl-C print a new prompt on a newline.
  - [x] ctrl-D exit the shell.
  - [ ] ctrl-\ do nothing.

## Checklist

This is very handy to check if everything is working as espected.

- [ ] Simple Command & global
  - [ ] Execute a simple command with an absolute path like /bin/ls or any other command without options
  - [ ] How many global variables? why? Give a concrete example of why it feels mandatory or logical.
  - [ ] Test an empty command
  - [ ] Test only spaces or tabs.
- [ ] Arguments & history
  - [ ] Execute a simple command with an absolute path like /bin/ls or any other command with arguments   but without quotes and double quotes.
  - [ ] Repeat multiple times with different commands and arguments
- [ ] Echo
  - [ ] Execute the echo command with or without arguments or -n
  - [ ] Repeat multiple times with different arguments
- [ ] Exit
  - [ ] Execute exit command with or without arguments
  - [ ] Repeat multiple times with different arguments
- [ ] Return value of a process
  - [ ] Execute a simple command with an absolute path like /bin/ls or any other command with arguments but without quotes and double quotes then execute echo $?
  - [ ] Check the printed value. You can repeat the same in bash and compare it
  - [ ] Repeat multiple times with different commands and arguments, use some failing commands like '/bin ls filethatdoesntexist'
  - [ ] anything like expr $? + $?
- [ ] Signals
  - [ ] Try ctrl-C in an empty prompt should show a new line with a new prompt
  - [ ] Try ctrl-\ in an empty prompt should not do anything
  - [ ] Try ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
  - [ ] Try ctrl-C in a prompt after you wrote some stuff should show a new line with a new prompt
  - [ ] Try ctrl-D in a prompt after you wrote some stuff should not do anything
  - [ ] Try ctrl-\ in a prompt after you wrote some stuff should quit minishell --> RELAUNCH!
  - [ ] Try ctrl-C after running a blocking command like cat or grep without arguments
  - [ ] Try ctrl-\ after running a blocking command like cat or grep without arguments
  - [ ] Try ctrl-D after running a blocking command like cat or grep without arguments
  - [ ] Repeat multiple times with different commands
- [ ] Double Quotes
  - [ ] Execute a simple command with arguments but this time double quotes (you should include whitespaces)
  - [ ] a command like : echo "cat lol.c | cat > lol.c"
  - [ ] anything except $.
- [ ] Simple Quotes
  - [ ] Execute commands with simple quotes as an argument
  - [ ] Try empty arguments
  - [ ] Try environment variables, whitespaces, pipes, redirection in the simple quotes
  - [ ] echo '$USER' must print $USER
  - [ ] Nothing should be interprated
- [ ] Env
  - [ ] Check if env shows you the current environment variables
- [ ] Export
  - [ ] Export environment variables, create new ones, and replace old ones
  - [ ] Check them with env
- [ ] Unset
  - [ ] Export environment variables, create new ones, and replace old ones
  - [ ] Use unset to remove some of them
  - [ ] Check the result with env
- [ ] Cd
  - [ ] Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
  - [ ] Repeat multiple times with working and not working cd
  - [ ] try '.' '..' as arguments too
- [ ] Pwd
  - [ ] Use the command pwd
  - [ ] Repeat multiple times in multiple directories
- [ ] Relative Path
  - [ ] Execute commands but this time use a relative path
  - [ ] Repeat multiple times in multiple directories with a complex relative path (lots of ..)
- [ ] Environment Path
  - [ ] Execute commands but this time without any path. (ls, wc, awk etc...)
  - [ ] Unset the $PATH and check if it is not working anymore
  - [ ] Set the $PATH to a multiple directory value (directory1:directory2) and check that directories are checked in order from left to right
- [ ] Redirection
  - [ ] Execute commands with redirections < and/or >
  - [ ] Repeat multiple times with different commands and arguments and sometimes change > with >>
  - [ ] Check if multiple of the same redirections fail
  - [ ] Test << redirection (it doesn't need to update history).
- [ ] Pipes
  - [ ] Execute commands with pipes like 'cat file | grep bla | more'
  - [ ] Repeat multiple times with different commands and arguments
  - [ ] Try some failing commands like 'ls filethatdoesntexist | grep bla | more'
  - [ ] Try to mix pipes and redirections.
- [ ] Go Crazy and history
  - [ ] type a command line then use ctrl-C then press enter the buffer should be clean and nothing try to execute.
  - [ ] Can we navigate through history with up and down and retry some command
  - [ ] Execute commands that should not work like 'dsbksdgbksdghsd' and check if the shell doesn't crash and prints an error.
  - [ ] Try to execute a long command with a ton of arguments
  - [ ] Have fun with that beautiful minishell and enjoy it
- [ ] Environment Variables
  - [ ] Execute echo with some $ variables as argumentss
  - [ ] Check that $ is interprated as an environment variable
  - [ ] Check that double quotes interpolate $
  - [ ] Check that $USER exist or set it.
  - [ ] echo "$USER" should print the value of $USER

No checklist for bonus, because we are not doing it :P

## Resources

* Lexing/Parsing: https://craftinginterpreters.com/contents.html
* AST: https://astexplorer.net/
* dup() and dup2(): https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
* envp: https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
* bsdutils: https://github.com/dcantrell/bsdutils
* coreutils: https://github.com/coreutils/coreutils
* Bash parser: https://vorpaljs.github.io/bash-parser-playground/