/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:06 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 21:25:20 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_ready_exe(t_main *main)
{
	char	*command;
	char	**args;
	char	**envir;
	int		fork_res;
	char	**argv;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	envir = main->my_env;
	argv = cmd_args_to_argv_recorder2(main);
	fork_res = fork();
	if (fork_res == 0)
	{
		execve(command, argv, envir);
		exec_mistakes(main);
		exit(126);
	}
	if (fork_res > 0)
	{
		waitpid(fork_res, &main->exit, 0);
		exit_code(main);
	}
	if (main->exit == 0)
		return (1);
	return (0);
}

int	check_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else if (ENOENT == errno)
	{
		return (2);
	}
	else if (EACCES == errno)
		return (3);
	return (0);
}

void	process_folder2(t_main *main, int status_num, char *command, int d)
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

void	process_folder3(t_main *main, int status_num, char *command, int d)
{
	char		*message;

	if (status_num < 0 && d == 3)
	{
		message = strerror(errno);
		main->flag2 = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(message, 2);
		ft_putchar_fd('\n', 2);
		main->exit = 126;
	}
}

void	process_folder_or_ready_exe(t_main *main)
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
			main->flag2 = process_ready_exe(main);
	}
}
