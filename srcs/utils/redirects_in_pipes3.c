/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:19:52 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 14:20:03 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_node_to_left_in_rp(t_main *main, t_redir	*redir, int file)
{
	int		saved_stdin;
	int		fd;

	if (redir->command && redir->redir_type == INPUT && redir->redir_file)
	{
		saved_stdin = dup(0);
		file = find_file_in_folder(redir);
		if (file == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->redir_file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			main->exit = 258;
		}
		else
		{
			fd = open(redir->redir_file, O_RDONLY, S_IRWXU);
			dup2(fd, STDIN_FILENO);
			close(fd);
			process_builtins_and_divide_externals_in_rp(main);
			dup2(saved_stdin, 0);
			close(saved_stdin);
		}
	}
}

void	last_node_fd_in_rp(t_main *main, t_redir	*redir, char *cmd)
{
	int	fd;

	fd = open(redir->redir_file, O_RDONLY, S_IRWXU);
	dup2(fd, STDIN_FILENO);
	close(fd);
	redir->command = cmd;
	process_builtins_and_divide_externals_in_rp(main);
	redir->command = NULL;
	cmd = NULL;
}

void	second_if_in_rp(char *cmd, t_redir *redir, int file, t_main *main)
{
	int		saved_stdin;

	if (!redir->command && redir->redir_type == INPUT && redir->redir_file)
	{
		while (redir->redir_next)
		{
			main->redir_flag = check_if_file_exists(main, redir, file);
			if (main->redir_flag == 1)
				return ;
			redir = redir->redir_next;
		}
		saved_stdin = dup(0);
		main->redir_flag = check_if_file_exists(main, redir, file);
		if (main->redir_flag == 1)
			return ;
		last_node_fd_in_rp(main, redir, cmd);
		dup2(saved_stdin, 0);
		close(saved_stdin);
		return ;
	}	
}

int	redir_one_left_in_pipes(t_main *main)
{
	t_redir	*redir;
	char	*cmd;
	int		file;
	t_pipe	*pipe;

	file = 0;
	pipe = get_current_pipe(main->job);
	redir = main->job->pipe->redir;
	check_valid_redir(main);
	if (redir && redir->redir_next == NULL)
		one_node_to_left_in_rp(main, redir, file);
	while (redir->redir_next != NULL)
	{
		cmd = redir->command;
		first_if(redir, file, main);
		if (main->redir_flag == 1)
			break ;
		redir = redir->redir_next;
		second_if_in_rp(cmd, redir, file, main);
		if (main->redir_flag == 1)
			break ;
		main->redir_flag = 0;
		break ;
	}
	return (0);
}
