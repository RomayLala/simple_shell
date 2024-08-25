#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

extern char **environ;

/* Function prototypes from Task 1 */
void execute_command(char **argv); /* Takes an array of strings (char**) */
char *read_line(void);
char **split_line(char *line);
void shell_loop(void);

/* Function prototypes from Task 2 */
void display_prompt(void);
char *read_input(void);
int execute_single_command(char *input); /* Renamed to avoid conflict */
void print_error(char *msg);

/* Function prototypes from Task 3 */
void prompt(void);
void handle_input(char *input);
void sigchld_handler(int sig);
int tokenize_input(char *input, char **argv);

/* Function prototypes from Task 4 */
char *find_executable(char *command);
void handle_error(char *msg);

#endif /* SHELL_H */
