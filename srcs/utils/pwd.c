#include "minishell.h"

int pwd(t_main *main)
{
    char *command;
    char buffer[1024];

    //$? = 0; это у нас инициализовано в init_shell там main->exit = 0
    command = main->job->pipe->redir->command;
    if (getcwd(buffer, 1024) == NULL)
    {
        main->exit = 1;
        printf("Could not get current working directory\n");
    }
    printf("%s\n", buffer);
    return(0);
}