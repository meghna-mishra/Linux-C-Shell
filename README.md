## Introduction:

This is Linux shell written in C.


## Running the shell:

1. Run 'make' command.
2. Run './a.out' command.
3. The shell displays a prompt and is ready to take input commands.
3. To quit, enter 'quit' or hit Ctrl D.

## Commands:
1. echo < arguments >
Prints the given arguments on the screen.

2. pwd
Displays the present working directory.

3. cd < argument >
Argument may be address of a directory including " . ", " .. ", " ~ ", " - ".
This command changes the directory based on argument provided. In addition, the "-" argument switches to the previous working directory and prints it's path. Note that in this shell, the path is printed relative to the shell's home being treated as " ~ ".

4. ls < options > < argument >
Options include zero or more of " - ", " -a ", " -al ", " -la ". Argument can be either nothing or address of a directory. This command lists the contents of a directory based on arguments provided.

5. pinfo < argument >
Argument can be process ID of a process, or nothing. It lists the details of a particular process. If no argument is given, process ID of current process is taken.

6. setenv < var > < value >
Creates an environment variable var if it doesn't exist yet, and assigns it the given value.

7. unsetenv < var >
Destroys the environment variable var.

8. kjob < jobnumber > < signalnumber >
Sends the given signal to the process with the given jobnumber.

9. jobs
Displays all the currently Running/Stopped/Sleeping/Defunct jobs with their current state.

10. fg < jobnumber >
Resumes a running or stopped background process given by the entered job number and brings it to the foreground.

11. bg < jobnumber >
Changes a stopped background job given by job number to running.

12. overkill
Kills all the background processes.

13. quit
Exits the shell.

## Additional features:
1. Ctrl-D
Exits the shell.

2. Ctrl-Z
Pushes the currently running foregorund job to background after stopping it.

3. Ctrl-C
Sends the SIGINT signal to interrupt the current foreground process.

4. Redirection and Piping
Both redirection and piping can be handled with use of the " < "," > "," >> " or " | " operators.

5. Exit Codes
Information about the previous command's exit code is displayed
alongside the prompt as :') if the command exited successfully, or as :'( if it encountered an error. Initially, it is :').

## Bonus command:
1. history < argument >
Argument can be nothing or a number less than or equal to 20. If number entered is n, this prints the last n commands including the history command itself. If no n is specified, it is assumed to be 10. This can hold accross all sessions even after shell has been stopped.


## Running processes:
1. All other commands are considered to be system commands (Eg: vi, emacs).
2. By default, the process is run on the foreground.
3. When command is followed by ' & ' symbol, it is run in the background. (Eg: emacs &). When this background process terminates, an appropriate message regarding it's exit is displayed.
4. When background processes run, the terminal is free to use.
