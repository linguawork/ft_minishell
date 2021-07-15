#include "minishell.h"

int echo(t_main *main)
{
    char *command;
    char **args;
//	char **dup_args;

    command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
//    dup_args = args;
    main->exit = 0;
    if (command)
    {
        if (!args)
            ft_putchar_fd('\n', 1);
        if (args)
        {
            if (ft_strcmp(*args, "-n") == 0)
            {
                while (*args != NULL && (ft_strcmp(*args, "-n") == 0))
                    args++;
                if (*args == NULL)
                    return (0);
                write(1, *args, ft_strlen(*args));
                while (*++args != NULL)
                {
                    ft_putchar_fd(' ', 1);
                    write(1, *args, ft_strlen(*args));
                }
            }
            else
            {
                while (*args != NULL)
                {
                    ft_putstr_fd(*args, 1);
                    ft_putchar_fd(' ', 1);
                    args++;
                }
                ft_putchar_fd('\n', 1);
            }
        }
    }// here we need to free leaks after working
    return(0);
}