# Minishell

## Todo

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

## Resources

Lexing/Parsing: https://craftinginterpreters.com/contents.html
AST: https://astexplorer.net/
dup() and dup2(): https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
