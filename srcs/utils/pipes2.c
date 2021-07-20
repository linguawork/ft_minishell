/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:39 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:44 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int process_exe_in_pipes(t_main *main, char **cmd)
{
//    char *command;
//    char **envir;
    char **binar;
    char *path;
    int i;
    char *exe;
    char *exe2;
//    int fork_res;
//    int status;
    DIR *folder;
    struct dirent *entry;
//    status = 0;

//    command = cmd[0];
//    envir = main->my_env;
    i = 0;
    path = ft_getenv(main, "PATH");
    if(!path)
        return 0;
    binar = ft_split(path, ':');
    while (binar[i] != NULL)
    {
        folder = opendir(binar[i]);
        if(folder == NULL)
            i++;
        else
        {
            while((entry = readdir(folder)))
            {
                if (ft_strcmp(entry->d_name, cmd[0]) == 0)
                {
                    exe = ft_strjoin(binar[i], "/");
                    exe2 = ft_strjoin(exe, cmd[0]);
//                    fork_res = fork();
//                    if (fork_res == 0)
                        execve(exe2, cmd, NULL);
//                        signal(SIGQUIT, SIG_IGN);
//                    if (fork_res > 0)
//                    {
//                        waitpid(fork_res, &status, 0);
//                        main->exit = WEXITSTATUS(status);
//                    }
//                    ft_putstr_fd("status number is ", 1);
//                    ft_putnbr_fd (WEXITSTATUS(status), 1); // запись кода выхода 1
//                    write(1, "\n", 1);
//                    ft_putstr_fd("main_>exit is ", 1);
//                    ft_putnbr_fd (main->exit, 1);
//                    write(1, "\n", 1);
//                    ft_putstr_fd("parent id is ", 1); // если использовать printf то печатает после завершения программы
//                    ft_putnbr_fd (fork_res, 1);// ID родителя
//                    write(1, "\n", 1);
                    closedir(folder);
                    arrays_free(binar);
                    free(exe);
                    free(exe2);
                    return(1);// можно просто брейкать
                }
            }
            closedir(folder);
        }
        i++;
    }
    ft_putstr_fd("minishell: ", 1);
    ft_putstr_fd(cmd[0], 1);
    ft_putstr_fd(": Command not found\n", 1);
    main->exit = 127;
    return(0);
}