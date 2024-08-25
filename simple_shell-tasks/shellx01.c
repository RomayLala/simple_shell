#include "shell.h"

char *read_input(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        free(line);
        if (feof(stdin))
            exit(0); /* Exit on Ctrl+D */
        perror("read_input");
        return NULL;
    }
    return line;
}

int execute_single_command(char *input) 
{
    char *argv[2];
    pid_t pid;
    int status;

    argv[0] = strtok(input, "\n");
    argv[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        if (execve(argv[0], argv, environ) == -1)
        {
            perror(argv[0]);
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
    }
    return status; /* Return status instead of 1 */
}

