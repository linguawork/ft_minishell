#include "minishell.h"

void process_builtins_in_pipes(t_main *main, char **cmd)
{
    int i;
    i = 1;
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
//        ft_putstr_fd(cmd[i], 2);
//        ft_putchar_fd('\n', 2);
        echo(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "cd", 2) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        cd(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        pwd(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        export(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        unset(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "env", 3) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        env(main);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strncmp(cmd[0], "exit", 4) == 0)
    {
        main->job->pipe->redir->command = cmd[0];
        main->job->pipe->redir->args = &cmd[i];
        exit_command(main);
        exit(EXIT_SUCCESS);
    }
}