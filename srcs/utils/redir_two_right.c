/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_two_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:57 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 22:56:25 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_right_cycle_first_node(t_redir *redir, int fd)
{
	if (redir->command && redir->redir_type == APPEND_OUTPUT && \
	redir->redir_file)
	{
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
	}
}

void	first_node_double_right(t_redir *redir, int fd, t_main *main)
{
	int	saved_stdout;

	if (redir->command && redir->redir_type == APPEND_OUTPUT && \
	redir->redir_file)
	{
		saved_stdout = dup(1);
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		process_builtins_and_divide_externals(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	double_right_cycle_last_node(t_redir *redir, int fd, t_main *main, \
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
		process_builtins_and_divide_externals(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	redir_two_right(t_main *main)
{
	int		fd;
	t_redir	*redir;
	int		len;

	fd = 0;
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
		double_right_cycle_last_node(redir, fd, main, len);
		break ;
	}
}
