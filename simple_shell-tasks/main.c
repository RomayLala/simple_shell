#include "shell.h"

/**
 * main - Entry point of the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
	(void)argv;  /* Mark argv as unused */

	if (argc == 1)
	{
		/* Interactive mode */
		shell_loop();  /* Call shell_loop with no arguments */
	}
	else
	{
		/* Non-interactive mode */
		char *line = NULL;
		size_t len = 0;
		ssize_t nread;

		while ((nread = getline(&line, &len, stdin)) != -1)
		{
			char **args = split_line(line);
			execute_command(args);
			free(args);
		}
		free(line);
	}
	return (0);
}
