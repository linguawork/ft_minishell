/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:01:28 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 19:11:07 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	searching_cmd_cycle_in_rp(t_main *main, char **binar, int i, char *command)
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
					no_forking2_in_rp(main, binar, i, command);
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

int	process_exe_in_rp(t_main *main)
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
	flag = searching_cmd_cycle_in_rp(main, binar, i, command);
	arrays_free(binar);
	if (flag == 0)
		command_not_found_in_exe(main, &command);
	return (0);
}

int	process_ready_exe_in_rp(t_main *main)
{
	char	*command;
	char	**args;
	char	**envir;
	char	**argv;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	envir = main->my_env;
	argv = cmd_args_to_argv_recorder2(main);
	execve(command, argv, envir);
	return (0);
}

void	process_folder_or_ready_exe_in_rp(t_main *main)
{
	char		*command;
	struct stat	sb;
	int			status_num;
	int			d;

	command = main->job->pipe->redir->command;
	status_num = stat(command, &sb);
	d = check_dir(command);
	if (ft_strchr(command, '/'))
	{
		process_folder2(main, status_num, command, d);
		process_folder3(main, status_num, command, d);
		if ((sb.st_mode & S_IFMT) == S_IFREG)
			main->flag2 = process_ready_exe_in_rp(main);
	}
}

void	process_builtins_and_divide_externals_in_rp(t_main *main)
{
	int	flag;

	flag = process_buildins(main);
	process_folder_or_ready_exe_in_rp(main);
	if (main->flag2 != 1 && flag == 0)
		process_exe_in_rp(main);
	main->flag2 = 0;
}
