#include "shell.h"

/**
 * prompt - Displays the shell prompt.
 */
void prompt(void)
{
    write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_input - Reads a line of input from stdin.
 * 
 * Return: The input line or NULL on failure.
 */
char *read_input(void)
{
    char *buffer = NULL;
    size_t size = 0;

    if (getline(&buffer, &size, stdin) == -1)
    {
        free(buffer);
        return (NULL);
    }

    return (buffer);
}

/**
 * handle_input - Processes the input line and executes the command.
 * @input: The input line.
 */
void handle_input(char *input)
{
    char *argv[BUFFER_SIZE / 2 + 1]; /* Use BUFFER_SIZE from shell.h */
    int argc;

    argc = tokenize_input(input, argv); /* Ensure tokenize_input is declared */
    if (argc == 0)
        return; /* Empty input */

    if (execvp(argv[0], argv) == -1)
    {
        print_error(argv[0]);
        _exit(EXIT_FAILURE);
    }
}

/**
 * tokenize_input - Tokenizes the input line into command and arguments.
 * @input: The input line.
 * @argv: Array to store command and arguments.
 * 
 * Return: Number of tokens.
 */
int tokenize_input(char *input, char **argv)
{
    int argc = 0;
    char *token;

    token = strtok(input, " \t\r\n");
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    argv[argc] = NULL;

    return (argc);
}

/**
 * sigchld_handler - Handles SIGCHLD signal.
 * @sig: Signal number.
 */
void sigchld_handler(int sig)
{
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

/**
 * print_error - Prints an error message.
 * @msg: The message to print.
 */
void print_error(char *msg)
{
    fprintf(stderr, "%s: %s: not found\n", "hsh", msg);
}
