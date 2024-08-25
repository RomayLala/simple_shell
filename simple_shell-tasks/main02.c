#include "shell.h"

/**
 * main - Entry point for the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * 
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;

    (void)argv; /* Suppress unused parameter warning */

    if (argc > 1)
    {
        /* Non-interactive mode */
        while ((nread = getline(&input, &len, stdin)) != -1)
        {
            input[nread - 1] = '\0'; /* Remove newline character */
            handle_input(input);
        }
        free(input);
        return (0);
    }

    /* Interactive mode */
    signal(SIGCHLD, sigchld_handler);
    while (1)
    {
        prompt();
        input = read_input();
        if (input == NULL)
            break;
        handle_input(input);
        free(input);
    }

    return (0);
}
