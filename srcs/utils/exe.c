/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:52 by areggie           #+#    #+#             */
/*   Updated: 2021/07/23 20:32:17 by areggie          ###   ########.fr       */
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

void command_not_found(t_main *main, char *command)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": Command not found\n", 2);
    main->exit = 127;
}

void free_exes(   char *exe, char *exe2, char **argv)
{
    free(exe);
    free(exe2);
    free(argv);
}

void forking(t_main *main, char **binar, int i, char *command)
{
    char *exe;
    char *exe2;
    int fork_res;
    char **argv;

    argv = cmd_args_to_argv_recorder(main);
    exe = ft_strjoin(binar[i], "/");
    exe2 = ft_strjoin(exe, command);
    signal(SIGINT, SIG_IGN);
    fork_res = fork();
    if (fork_res == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execve(exe2, argv, NULL);
    }
    if (fork_res > 0)
    {
        waitpid(fork_res, &main->exit, 0);
        exit_code(main);
        free_exes(exe, exe2, argv);
    }
}

void forking2(t_main *main, char **binar, int i, char *command)
{
    DIR *folder;

    folder = opendir(binar[i]);
    forking(main, binar, i, command);
    closedir(folder);
    signal(SIGINT, &ctrl_c);
}

int searching_cmd_cycle(t_main *main, char **binar, int i, char *command)
{
    DIR *folder;
    struct dirent *entry;

    while (binar[i++] != NULL)
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
                    forking2(main, binar, i, command);
                    closedir(folder);
                    return(1);
                }
            }
            closedir(folder);
        }
    }
    return(0);
}


int process_exe(t_main *main)
{
    char *command;
    char **binar;
    char *path;
    int i;
    int flag;

    command = main->job->pipe->redir->command;
    i = 0;
    path = ft_getenv(main, "PATH");
    if(!path)
    {
        main->exit = 1;
        return (path_mistakes(main, path));
    }
    binar = ft_split(path, ':');
    flag = searching_cmd_cycle(main, binar, i, command);
    arrays_free(binar);
    if (flag == 0)
        command_not_found(main, command);
    return(0);
}