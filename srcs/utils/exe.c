/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:52 by areggie           #+#    #+#             */
/*   Updated: 2021/07/22 22:12:06 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_cmd_from_absolute_path(t_main *main)
{
	char	*cmd;
	char	**parts;
	int		len;

	parts = ft_split(main->job->pipe->redir->command, '/');
	len = how_many_lines(parts);
	cmd = parts[len-1];
	return(cmd);
}

char	**cycle(int length, char *cmd, char **e, char **a)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	length = how_many_lines((char **) a);
	e = (char **) malloc(sizeof(char *) * (length + 1 + 1));
	e[0] = cmd;
	while (a[j] != NULL)
	{
		e[i] = a[j];
		j++;
		i++;
	}
	e[i] = NULL;
	return (e);
}

char** cmd_args_to_argv_recorder2(t_main *main)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;

	e = NULL;
	length = 0; 
	cmd = return_cmd_from_absolute_path(main);
	a = main->job->pipe->redir->args;
	int i = 1;
	if (a == NULL)
	{
		e = (char **) malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i] = NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return (e);
}

char**	cmd_args_to_argv_recorder_p(t_job *job)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;

	e = NULL;
	length = 0;
	cmd = job->pipe->redir->command;
	a = job->pipe->redir->args;
	int i = 1;
	if (a == NULL)
	{
		e = (char **)malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i]=NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return(e);
}

char** cmd_args_to_argv_recorder(t_main *main)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;

	e = NULL;
	length = 0;
	cmd = main->job->pipe->redir->command;
	a = main->job->pipe->redir->args;
	int i = 1;
	if (a == NULL)
	{
		e = (char **) malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i] = NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return (e);
}

int path_mistakes(t_main *main, char *p)
{
    char *error_mes;

    error_mes = strerror(errno);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(main->job->pipe->redir->command, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(p, 2);
    ft_putchar_fd(' ', 2);
    ft_putstr_fd(error_mes, 2);
    ft_putchar_fd('\n', 2);
    return (1);
}

int process_exe(t_main *main)
{
    char *command;
    char **envir;
    char **binar;
    char *path;
    char *exe;
    char *exe2;
    int i;
    int fork_res;
    int status;
    DIR *folder;
    struct dirent *entry;
    status = 0;

    command = main->job->pipe->redir->command;
    char **argv;
    envir = main->my_env;
    i = 0;
    path = ft_getenv(main, "PATH");
    if(!path)
    {
        main->exit = 1;
        return (path_mistakes(main, path));
    }
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
                if (ft_strcmp(entry->d_name, command) == 0)
                {
                    argv = cmd_args_to_argv_recorder(main);
                    exe = ft_strjoin(binar[i], "/");
                    exe2 = ft_strjoin(exe, command);
                    signal(SIGINT, SIG_IGN);
                    fork_res = fork();
                    if (fork_res == 0)
                    {
                        signal(SIGINT, SIG_DFL);
                        signal(SIGQUIT, SIG_DFL);
                        execve(exe2, argv, envir);
                    }
                    if (fork_res > 0)
                    {
                        waitpid(fork_res, &status, 0);
                        main->exit = WEXITSTATUS(status);
                        free(exe);
                        free(exe2);
                        free(argv);
                    }
                    closedir(folder);
                    arrays_free(binar);
                    signal(SIGINT, &ctrl_c);
                    return(1);
                }
            }
            closedir(folder);
        }
        i++;
    }
    arrays_free(binar);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": Command not found\n", 2);
    main->exit = 127;
    return(0);
}