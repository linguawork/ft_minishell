/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_left2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:02:48 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 15:03:11 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_file_in_folder(t_redir *redir)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*command;
	char			buffer[1024];

	command = redir->redir_file;
	folder = opendir(getcwd(buffer, 1024));
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, command) == 0)
		{
			closedir(folder);
			return (1);
		}
		entry = readdir(folder);
	}
	closedir(folder);
	return (0);
}

void	one_node_to_left(t_main *main, t_redir	*redir, int file)
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
			process_builtins_and_divide_externals(main);
			dup2(saved_stdin, 0);
			close(saved_stdin);
		}
	}
}
