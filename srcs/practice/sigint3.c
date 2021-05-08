#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

// https://indradhanush.github.io/code/shell-part-3/signal_handling_parent.c
// The code to compile  gcc -g -lreadline realize_cd.c
// run commands 1)pwd, 2) ls -lha 3) cd 4) signals

char **get_input(char *);
int cd(char *);

int main()
{
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

    signal(SIGINT, SIG_IGN); //macros that can be passed to the signal function:
    //Ignores the signal.


    // В отличие от signal(SIGINT, sigint_handler) сигнал не прервется при нажатии СTRL + C
    //Since we are ignoring SIGINT in the parent, the child also inherits the same property
    // for SIGINT from its parent and conveniently ignores the keyboard interrupt (Ctrl-C).

    while (1)
    {
        input = readline("unixsh> ");
        command = get_input(input);

        if (!command[0])
        {      /* Handle empty commands */
            free(input);
            free(command);
            continue;
        }

        if (strcmp(command[0], "cd") == 0)
        {
            if (cd(command[1]) < 0)
            {
                perror(command[1]);
            }
            /* Skip the fork */
            continue;
        }

        child_pid = fork();
        if (child_pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0)
        {
            signal(SIGINT, SIG_DFL); // это решает проблему непрерывания комбинацией CTRL + C после sleep 10
            // дочерний процесс здесь теперь можно прервать через CTRL +C
            //we will restore the default behaviour of SIGINT in the child process after fork.
            // Note that this must be done before the call to execvp since it will replace
            // the current program with the program passed in the command.

            /* Never returns if the call is successful */
            if (execvp(command[0], command) < 0)
            {
                perror(command[0]);
                exit(1);
            }
        } else
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        if (!input)
            free(input);
        if (!command)
            free(command);
    }

    return 0;
}

char **get_input(char *input)
{
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL)
    {
        perror("malloc failed");
        exit(1);
    }

    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL)
    {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int cd(char *path)
{
    return chdir(path);
}