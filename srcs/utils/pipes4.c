/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:39 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 23:37:29 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_builtins_in_pipes2(t_main *main, char **cmd, int i)
{
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
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

void	process_builtins_in_pipes(t_main *main, char **cmd)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
	{
		main->job->pipe->redir->command = cmd[0];
		main->job->pipe->redir->args = &cmd[i];
		echo(main);
		exit(EXIT_SUCCESS);
	}
	process_builtins_in_pipes3(main, cmd, i);
	process_builtins_in_pipes2(main, cmd, i);
}

void	no_forking_in_pipes(t_main *main, char **binar, int i, char **cmd)
{
	char	*exe;
	char	*exe2;

	exe = ft_strjoin(binar[i], "/");
	exe2 = ft_strjoin(exe, cmd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(exe2, cmd, NULL);
	exec_mistakes(main);
	exit(126);
	arrays_free(binar);
	free(exe);
	free(exe2);
}

int	searching_cmd_cycle_in_pipes(t_main *main, char **binar, int i, char **cmd)
{
	DIR				*folder;
	struct dirent	*entry;

	while (binar[i++] != NULL)
	{
		folder = opendir(binar[i]);
		if (folder == NULL)
			i++;
		else
		{
			entry = readdir(folder);
			while (entry)
			{
				if (ft_strcmp(entry->d_name, cmd[0]) == 0)
				{
					no_forking_in_pipes(main, binar, i, cmd);
					closedir(folder);
					return (1);
				}
				entry = readdir(folder);
			}
			closedir(folder);
		}
	}
	return (0);
}

int	process_exe_in_pipes(t_main *main, char **cmd)
{
	char	**binar;
	char	*path;
	int		i;

	i = 0;
	path = ft_getenv(main, "PATH");
	if (!path)
	{
		main->exit = 1;
		return (path_mistakes(main));
	}
	binar = ft_split(path, ':');
	searching_cmd_cycle_in_pipes(main, binar, i, cmd);
	arrays_free(binar);
	command_not_found_in_pipes(cmd);
	return (0);
}
