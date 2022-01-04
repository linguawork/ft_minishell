/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:52 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 21:36:04 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exes(char *exe, char *exe2, char **argv)
{
	free(exe);
	free(exe2);
	free(argv);
}

void	forking(t_main *main, char **binar, int i, char *command)
{
	char	*exe;
	char	*exe2;
	int		fork_res;
	char	**argv;

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
		exec_mistakes(main);
		exit(126);
	}
	if (fork_res > 0)
	{
		waitpid(fork_res, &main->exit, 0);
		exit_code(main);
		free_exes(exe, exe2, argv);
	}
}

void	forking2(t_main *main, char **binar, int i, char *command)
{
	DIR	*folder;

	folder = opendir(binar[i]);
	forking(main, binar, i, command);
	closedir(folder);
	signal(SIGINT, &ctrl_c);
}

int	searching_cmd_cycle(t_main *main, char **binar, int i, char *command)
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
				if (ft_strcmp(entry->d_name, command) == 0)
				{
					forking2(main, binar, i, command);
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

int	process_exe(t_main *main)
{
	char	*command;
	char	**binar;
	char	*path;
	int		i;
	int		flag;

	command = main->job->pipe->redir->command;
	i = 0;
	path = ft_getenv(main, "PATH");
	if (!path)
	{
		main->exit = 1;
		return (path_mistakes(main));
	}
	binar = ft_split(path, ':');
	flag = searching_cmd_cycle(main, binar, i, command);
	arrays_free(binar);
	if (flag == 0 && !(ft_strchr(command, '/')))
		command_not_found_in_exe(main, &command);
	return (0);
}
