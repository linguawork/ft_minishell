/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:38 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 22:25:23 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_node_one_right_part_one(t_redir *redir, int fd)
{
	if (!redir->command && redir->redir_type == OUTPUT && redir->redir_file)
	{
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
	}
}

void	first_node_one_right_part_two(t_redir *redir, int fd, t_main *main)
{
	int	saved_stdout;

	if (redir->command && redir->redir_type == OUTPUT && redir->redir_file)
	{
		saved_stdout = dup(1);
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		process_builtins_and_divide_externals(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	cycle_first_node(t_redir *redir, int fd)
{
	if (redir->command && redir->redir_type == OUTPUT && redir->redir_file)
	{
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
	}
}

void	cycle_to_last_node(t_redir *redir, int fd, t_main *main, int len)
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
		process_builtins_and_divide_externals(main);
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
}

void	redir_one_right(t_main *main)
{
	int		fd;
	t_redir	*redir;
	int		len;

	fd = 0;
	redir = main->job->pipe->redir;
	if (redir && redir->redir_next == NULL)
	{
		first_node_one_right_part_one(redir, fd);
		check_valid_redir(main);
		first_node_one_right_part_two(redir, fd, main);
	}
	len = count_redirects(main);
	while (redir->redir_next != NULL)
	{
		cycle_first_node(redir, fd);
		redir = redir->redir_next;
		cycle_to_last_node(redir, fd, main, len);
		break ;
	}
}
