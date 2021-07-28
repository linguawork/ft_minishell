/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:59:55 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 14:20:17 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_node_double_left_in_rp(t_redir *redir, char *file, t_main *main)
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
		process_builtins_and_divide_externals_in_rp(main);
		free(redir->args);
	}
}

void	last_node_double_left_in_rp(t_redir *redir, char *file, \
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
		process_builtins_and_divide_externals_in_rp(main);
	}
}

int	redir_two_left_in_pipes(t_main *main)
{
	t_redir	*redir;
	char	*cmd;
	char	*file;
	t_pipe	*pipe;

	pipe = get_current_pipe(main->job);
	check_valid_redir(main);
	file = "tmp";
	redir = main->job->pipe->redir;
	cmd = redir->command;
	if (redir && redir->redir_next == NULL)
		first_node_double_left_in_rp(redir, file, main);
	while (redir && redir->redir_next != NULL)
		redir = redir->redir_next;
	last_node_double_left_in_rp(redir, file, main, cmd);
	cmd =NULL;
	redir->args = NULL;
	unlink(file);
	return (0);
}

void	process_redirects_in_pipes2(t_main *main)
{
	if (main->job->pipe_next->redir->redir_type == OUTPUT)
		redir_one_right_in_pipes(main);
	if (main->job->pipe->redir->redir_type == APPEND_OUTPUT)
		redir_two_right_in_pipes(main);
	if (main->job->pipe->redir->redir_type == INPUT)
		redir_one_left_in_pipes(main);
	if (main->job->pipe->redir->redir_type == INPUT_MULTILINE)
		redir_two_left_in_pipes(main);
}
