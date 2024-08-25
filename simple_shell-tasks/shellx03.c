#include "shell.h"

/**
 * shell_loop - Runs the shell loop for interactive mode.
 */
void shell_loop(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (errno == EINTR)
                continue;
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (strlen(line) > 0)
        {
            char **args = split_line(line); /* Use split_line to convert line to args */
            execute_command(args);
            free(args);
        }
    }

    free(line);
}

/**
 * execute_command - Executes a command.
 * @argv: Array of arguments.
 */
void execute_command(char **argv)
{
    char *path;
    pid_t pid;
    int status;

    path = find_executable(argv[0]);

    if (path == NULL)
    {
        handle_error(argv[0]);
        return;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        free(path);
        return;
    }

    if (pid == 0)
    {
        if (execve(path, argv, NULL) == -1)
        {
            handle_error(argv[0]);
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(path);
}

/**
 * split_line - Splits a line into an array of arguments.
 * @line: The line to split.
 * Return: Array of arguments.
 */
char **split_line(char *line)
{
    char **args = malloc(sizeof(char *) * 64);
    char *token;
    int i = 0;

    if (args == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    return (args);
}

/**
 * find_executable - Finds the full path of an executable.
 * @command: The command to find.
 * Return: The path of the executable or NULL if not found.
 */
char *find_executable(char *command)
{
    char *path_env = getenv("PATH");
    char *path = malloc(1024);
    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL)
    {
        snprintf(path, 1024, "%s/%s", dir, command);
        if (access(path, X_OK) == 0)
        {
            free(path_copy);
            return (path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    free(path);
    return (NULL);
}

/**
 * handle_error - Prints an error message with the program name.
 * @msg: The command that caused the error.
 */
void handle_error(char *msg)
{
    char *prog_name = getenv("_");
    if (prog_name == NULL)
        prog_name = "hsh";

    fprintf(stderr, "%s: 1: %s: not found\n", prog_name, msg);
}
