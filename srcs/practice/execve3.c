#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

// The code to compile  gcc -g -lreadline execve3.c
// run commands 1)pwd, 2) ls -lha

//char **get_input(char *);
char **get_input(char *input)
{
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) // защита маллока
    {
        perror("malloc failed");
        exit(1);
    }
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int main()
{
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

   while (1) {
        input = readline("unixsh> ");
        command = get_input(input);


        if (!command[0])       /* Handle empty commands */
            {
                free(input);
                free(command);
                continue;
            }

        child_pid = fork();
       if (child_pid < 0) // if child did not succeed
           {
               perror("Fork failed");
               exit(1);
           }
       if (execvp(command[0], command) < 0) // if execvp fails
           {
               perror(command[0]);
               exit(1);
           }
        if (child_pid == 0)/* Never returns if the call is successful */
            {
                execvp(command[0], command);
                printf("This won't be printed if execvp is successul\n");
            }
        else
            {
                waitpid(child_pid, &stat_loc, WUNTRACED);
            }

        free(input);
        free(command);
    }

    return 0;
}

