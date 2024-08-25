This project implements a simple UNIX command interpreter (shell) written in C. The shell provides a command line interface where users can enter commands to be executed. The shell supports both interactive and non-interactive modes.
The shell reads input from the user or a file, executes the command using `execve`, and displays the result.
It handles command lines with arguments and supports both interactive and non-interactive modes.
The shell handles command execution with PATH resolution, input/output in both interactive and non-interactive modes, and adheres to the constraints provided.
