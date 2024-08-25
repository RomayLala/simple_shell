#include "shell.h"

/**
 * shell_loop - Main loop of the shell
 */
void shell_loop(void)
{
	char *line;
	char **args;

	while (1)
	{
		printf("($) ");
		line = read_line();
		args = split_line(line);
		execute_command(args);
		free(line);
		free(args);
	}
}

/**
 * read_line - Reads a line of input from stdin
 *
 * Return: The input line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The line to split
 *
 * Return: Array of tokens (arguments)
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("hsh");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("hsh");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_command - Executes a command using execve
 * @argv: Array of command arguments
 */
void execute_command(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("hsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
