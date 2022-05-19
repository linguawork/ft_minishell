/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:49 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 19:46:08 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_builtins_in_pipes3(t_main *main, char **cmd, int i)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
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
}

void	process_folder_in_pipes2(t_main *main, int status_num, char *command, \
int d)
{
	struct stat	sb;

	if (d == 2 && status_num == -1)
	{
		main->flag2 = 1;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(command, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		main->exit = 127;
	}
	else if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		main->flag2 = 1;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(command, 1);
		ft_putstr_fd(": is a directory\n", 1);
		main->exit = 126;
	}
}

void	process_folder_in_pipes(t_main *main, char **cmd)
{
	char		*command;
	struct stat	sb;
	int			status_num;
	int			d;
	char		*message;

	command = cmd[0];
	status_num = stat(command, &sb);
	d = check_dir(command);
	if (ft_strchr(command, '/'))
	{
		process_folder_in_pipes2(main, status_num, command, d);
		if (status_num < 0 && d == 3)
		{
			main->flag2 = 1;
			message = strerror(errno);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putchar_fd(' ', 2);
			ft_putstr_fd(message, 2);
			ft_putchar_fd('\n', 2);
			main->exit = 126;
		}
	}
}

void	command_not_found_in_pipes( char **command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*command, 2);
	ft_putstr_fd(": Command not found\n", 2);
	exit(127);
}
