# basicshell
Hello!

This is a simple imitation of a command line interpreter. It reads commands from the terminal and executes them. 

The file shell.c is ready to be compiled and executed. Once running, the shell will ask for commands. Please be aware that the character limit for a single line is set to 50.

The shell supports type 1 (built-in) commands such as
“hello” - prints a friendly greeting
“author” - prints information about the program’s author (me!)
“help” - prints all built-in commands
“bye” - exits the program

Type 2 (internal) commands are also supported as long as they exist within the OS at path “/bin/“. This includes date, echo (including arguments) and dir. Any command that is not built in will be redirected to the OS and try to be executed. 

Thank you for downloading and reading! Contact me for comments and suggestions.
