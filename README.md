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
- [x] Redirections
  - [x] < should redirect input.
  - [x] > should redirect output.
  - [x] “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
  - [x] “>>” should redirect output with append mode.
- [x] Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command.
- [x] Environment variables ($ followed by characters) should expand to their values.
- [x] $? should expand to the exit status of the most recently executed foreground
      pipeline.
- [x] ctrl-C ctrl-D ctrl-\ should work like in bash.
- When interactive:
  - [x] ctrl-C print a new prompt on a newline.
  - [x] ctrl-D exit the shell.
  - [x] ctrl-\ do nothing.

## Checklist

This is very handy to check if everything is working as espected.

- [x] Simple Command & global
  - [x] Execute a simple command with an absolute path like /bin/ls or any other command without options
  - [x] How many global variables? why? Give a concrete example of why it feels mandatory or logical.
  - [x] Test an empty command
  - [x] Test only spaces or tabs.
- [x] Arguments & history
  - [x] Execute a simple command with an absolute path like /bin/ls or any other command with arguments   but without quotes and double quotes.
  - [x] Repeat multiple times with different commands and arguments
- [x] Echo
  - [x] Execute the echo command with or without arguments or -n
  - [x] Repeat multiple times with different arguments
- [x] Exit
  - [x] Execute exit command with or without arguments
  - [x] Repeat multiple times with different arguments
- [x] Return value of a process
  - [x] Execute a simple command with an absolute path like /bin/ls or any other command with arguments but without quotes and double quotes then execute echo $?
  - [x] Check the printed value. You can repeat the same in bash and compare it
  - [x] Repeat multiple times with different commands and arguments, use some failing commands like '/bin ls filethatdoesntexist'
  - [x] anything like expr $? + $?
- [ ] Signals
  - [x] Try ctrl-C in an empty prompt should show a new line with a new prompt
  - [x] Try ctrl-\ in an empty prompt should not do anything
  - [x] Try ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
  - [x] Try ctrl-C in a prompt after you wrote some stuff should show a new line with a new prompt
  - [x] Try ctrl-D in a prompt after you wrote some stuff should not do anything
  - [x] Try ctrl-\ in a prompt after you wrote some stuff should quit minishell --> RELAUNCH!
  - [x] Try ctrl-C after running a blocking command like cat or grep without arguments
  - [x] Try ctrl-\ after running a blocking command like cat or grep without arguments
  - [x] Try ctrl-D after running a blocking command like cat or grep without arguments
  - [x] Repeat multiple times with different commands
- [x] Double Quotes
  - [x] Execute a simple command with arguments but this time double quotes (you should include whitespaces)
  - [x] a command like : echo "cat lol.c | cat > lol.c"
  - [x] anything except $.
- [x] Simple Quotes
  - [x] Execute commands with simple quotes as an argument
  - [x] Try empty arguments
  - [x] Try environment variables, whitespaces, pipes, redirection in the simple quotes
  - [x] echo '$USER' must print $USER
  - [x] Nothing should be interprated
- [x] Env
  - [x] Check if env shows you the current environment variables
- [x] Export
  - [x] Export environment variables, create new ones, and replace old ones
  - [x] Check them with env
- [x] Unset
  - [x] Export environment variables, create new ones, and replace old ones
  - [x] Use unset to remove some of them
  - [x] Check the result with env
- [x] Cd
  - [x] Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
  - [x] Repeat multiple times with working and not working cd
  - [x] try '.' '..' as arguments too
- [x] Pwd
  - [x] Use the command pwd
  - [x] Repeat multiple times in multiple directories
- [x] Relative Path
  - [x] Execute commands but this time use a relative path
  - [x] Repeat multiple times in multiple directories with a complex relative path (lots of ..)
- [x] Environment Path
  - [x] Execute commands but this time without any path. (ls, wc, awk etc...)
  - [x] Unset the $PATH and check if it is not working anymore
  - [x] Set the $PATH to a multiple directory value (directory1:directory2) and check that directories are checked in order from left to right
- [x] Redirection
  - [x] Execute commands with redirections < and/or >
  - [x] Repeat multiple times with different commands and arguments and sometimes change > with >>
  - [x] Check if multiple of the same redirections fail
  - [x] Test << redirection (it doesn't need to update history).
- [x] Pipes
  - [x] Execute commands with pipes like 'cat file | grep bla | more'
  - [x] Repeat multiple times with different commands and arguments
  - [x] Try some failing commands like 'ls filethatdoesntexist | grep bla | more'
  - [x] Try to mix pipes and redirections.
- [x] Go Crazy and history
  - [x] type a command line then use ctrl-C then press enter the buffer should be clean and nothing try to execute.
  - [x] Can we navigate through history with up and down and retry some command
  - [x] Execute commands that should not work like 'dsbksdgbksdghsd' and check if the shell doesn't crash and prints an error.
  - [x] Try to execute a long command with a ton of arguments
  - [x] Have fun with that beautiful minishell and enjoy it
- [x] Environment Variables
  - [x] Execute echo with some $ variables as argumentss
  - [x] Check that $ is interprated as an environment variable
  - [x] Check that double quotes interpolate $
  - [x] Check that $USER exist or set it.
  - [x] echo "$USER" should print the value of $USER

No checklist for bonus, because we are not doing it :P

## MacOS

readline needs to be installed via homebrew. If you are using 42 school computer and don't have homebrew run:

```sh
curl -s https://brew.42.fr/ | bash
```

To install readline run:

```sh
brew install readline
```

## Resources

* Lexing/Parsing: https://craftinginterpreters.com/contents.html
* AST: https://astexplorer.net/
* dup() and dup2(): https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
* envp: https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
* bsdutils: https://github.com/dcantrell/bsdutils
* coreutils: https://github.com/coreutils/coreutils
* Bash parser: https://vorpaljs.github.io/bash-parser-playground/
* Heredoc: https://www.oilshell.org/blog/2016/10/18.html