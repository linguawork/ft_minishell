/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_two_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:49 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 19:09:34 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_node_double_left(t_redir *redir, char *file, t_main *main)
{
	int		fd;

	if (redir->command && redir->redir_type == INPUT_MULTILINE && \
		redir->redir_file)
	{
		redir->args = (char **)malloc(sizeof(char *) * 2);
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd == -1)
			exit(1);
		ft_putstr_fd(redir->redir_file, fd);
		redir->args[0] = file;
		redir->args[1] = NULL;
		process_builtins_and_divide_externals(main);
		free(redir->args);
	}
}

void	last_node_double_left(t_redir *redir, char *file, \
t_main *main, char *cmd)
{
	int	fd;

	if (!redir->command && redir->redir_type == INPUT_MULTILINE && \
		redir->redir_file && redir->redir_next == NULL)
	{
		if (cmd == NULL)
			return ;
		main->job->pipe->redir->args = (char **)malloc(sizeof(char *) * 2);
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd == -1)
			exit(1);
		ft_putstr_fd(redir->redir_file, fd);
		main->job->pipe->redir->args[0] = file;
		main->job->pipe->redir->args[1] = NULL;
		process_builtins_and_divide_externals(main);
	}
}

int	redir_two_left(t_main *main)
{
	t_redir	*redir;
	char	*cmd;
	char	*file;

	check_valid_redir(main);
	file = ft_strdup("tmp");
	redir = main->job->pipe->redir;
	cmd = redir->command;
	if (redir && redir->redir_next == NULL)
		first_node_double_left(redir, file, main);
	while (redir && redir->redir_next != NULL)
		redir = redir->redir_next;
	last_node_double_left(redir, file, main, cmd);
	cmd =NULL;
	redir->args = NULL;
	unlink(file);
	return (0);
}
