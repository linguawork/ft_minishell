/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:16:42 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 14:17:09 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_node_one_right_part_two_in_rp(t_redir *redir, int fd, \
t_main *main)
{
	int	saved_stdout;

	if ((redir->command && redir->redir_type == OUTPUT && redir->redir_file) \
	|| (redir->command && redir->redir_type == OUTPUT && redir->redir_file && \
	redir->args))
	{
		saved_stdout = dup(1);
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		process_builtins_and_divide_externals_in_rp(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	cycle_to_last_node_in_rp(t_redir *redir, int fd, t_main *main, int len)
{
	int	saved_stdout;

	if (!redir->command && redir->redir_type == OUTPUT && redir->redir_file)
	{
		while (len - 1)
		{
			fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit(1);
			len--;
			redir = redir->redir_next;
		}
		saved_stdout = dup(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		process_builtins_and_divide_externals_in_rp(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	redir_one_right_in_pipes(t_main *main)
{
	int		fd;
	t_pipe	*pipe;
	t_redir	*redir;
	int		len;

	fd = 0;
	pipe = get_current_pipe(main->job);
	redir = pipe->redir;
	if (redir && redir->redir_next == NULL)
	{
		first_node_one_right_part_one(redir, fd);
		check_valid_redir(main);
		first_node_one_right_part_two_in_rp(redir, fd, main);
	}
	len = count_redirects(main);
	while (redir->redir_next != NULL)
	{
		cycle_first_node(redir, fd);
		redir = redir->redir_next;
		cycle_to_last_node_in_rp(redir, fd, main, len);
		break ;
	}
}

void	double_right_cycle_last_node_in_rp(t_redir *redir, int fd, t_main *main, \
int len)
{
	int	saved_stdout;

	if (!redir->command && redir->redir_type == APPEND_OUTPUT && \
	redir->redir_file)
	{
		while (len - 1)
		{
			fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				exit(1);
			len--;
			redir = redir->redir_next;
		}
		saved_stdout = dup(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		process_builtins_and_divide_externals_in_rp(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	redir_two_right_in_pipes(t_main *main)
{
	int		fd;
	t_redir	*redir;
	int		len;
	t_pipe	*pipe;

	fd = 0;
	pipe = get_current_pipe(main->job);
	redir = main->job->pipe->redir;
	if (redir && redir->redir_next == NULL)
	{
		check_valid_redir(main);
		first_node_double_right(redir, fd, main);
	}
	len = count_redirects(main);
	while (redir->redir_next != NULL)
	{
		double_right_cycle_first_node(redir, fd);
		redir = redir->redir_next;
		double_right_cycle_last_node_in_rp(redir, fd, main, len);
		break ;
	}
}
