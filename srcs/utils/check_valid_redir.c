/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:19:19 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 18:19:22 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_valid_redir_if1(t_redir *redir, t_main *main)
{
	int	fd;

	if ((!redir->command && redir->redir_type == OUTPUT && \
	redir->redir_file) || (!redir->command && \
	redir->redir_type == APPEND_OUTPUT && redir->redir_file))
	{
		fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			main->exit = 0;
	}
}

void	check_valid_redir_if2(t_redir *redir, t_main *main)
{
	int	file;

	if (!redir->command && redir->redir_type == INPUT && redir->redir_file)
	{
		file = exists(redir->redir_file);
		if (file == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->redir_file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			main->exit = 1;
		}
	}
}

void	check_valid_redir_if3(t_redir *redir, t_main *main)
{
	if ((redir->command && redir->redir_type == INPUT && \
	!redir->redir_file) || (redir->command && \
	redir->redir_type == INPUT_MULTILINE && !redir->redir_file))
	{
		ft_putstr_fd ("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'", 2);
		ft_putchar_fd ('\n', 2);
		main->exit = 258;
		strerror(main->exit);
	}
}

void	check_valid_redir_if4(t_redir *redir, t_main *main)
{
	if ((redir->command && redir->redir_type == APPEND_OUTPUT && \
	!redir->redir_file) || (redir->command && \
	redir->redir_type == OUTPUT && !redir->redir_file))
	{
		ft_putstr_fd ("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'", 2);
		ft_putchar_fd ('\n', 2);
		main->exit = 258;
		strerror(main->exit);
	}
}

char	*check_valid_redir(t_main *main)
{
	t_redir	*redir;

	redir = main->job->pipe->redir;
	check_valid_redir_if1(redir, main);
	check_valid_redir_if2(redir, main);
	check_valid_redir_if3(redir, main);
	check_valid_redir_if4(redir, main);
	return (NULL);
}
