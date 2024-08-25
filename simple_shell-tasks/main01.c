#include "shell.h"

int main01(void)
{
    char *input;
    int status = 1;

    while (status)
    {
        display_prompt();
        input = read_input();
        if (input == NULL)
        {
            break;
        }
        status = execute_single_command(input); /* Call the renamed function */
        free(input);
    }
    return 0;
}
