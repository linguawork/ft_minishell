/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:22 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 15:03:17 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_file_exists(t_main *main, t_redir *redir, int file)
{
	file = find_file_in_folder(redir);
	if (file == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->redir_file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		main->exit = 258;
		return (1);
	}
	return (0);
}

void	last_node_fd(t_main *main, t_redir	*redir, char *cmd)
{
	int	fd;

	fd = open(redir->redir_file, O_RDONLY, S_IRWXU);
	dup2(fd, STDIN_FILENO);
	close(fd);
	redir->command = cmd;
	process_builtins_and_divide_externals(main);
	redir->command = NULL;
	cmd = NULL;
}

void	first_if(t_redir *redir, int file, t_main *main)
{
	if (redir->command && redir->redir_type == INPUT && redir->redir_file)
	{
		main->redir_flag = check_if_file_exists(main, redir, file);
	}
}

void	second_if(char *cmd, t_redir *redir, int file, t_main *main)
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
		last_node_fd(main, redir, cmd);
		dup2(saved_stdin, 0);
		close(saved_stdin);
		return ;
	}	
}

int	redir_one_left(t_main *main)
{
	t_redir	*redir;
	char	*cmd;
	int		file;

	file = 0;
	redir = main->job->pipe->redir;
	if (redir && redir->redir_next == NULL)
	{
		check_valid_redir(main);
		one_node_to_left(main, redir, file);
	}
	while (redir->redir_next != NULL)
	{
		cmd = redir->command;
		first_if(redir, file, main);
		if (main->redir_flag == 1)
			break ;
		redir = redir->redir_next;
		second_if(cmd, redir, file, main);
		if (main->redir_flag == 1)
			break ;
        main->redir_flag = 0;
		break ;
	}
	return (0);
}
