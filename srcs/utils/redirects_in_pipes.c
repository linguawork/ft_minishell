/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:59:55 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 23:59:42 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_node_one_right_part_two_in_rp(t_redir *redir, int fd, t_main *main)
{
	int	saved_stdout;
	
	if ((redir->command && redir->redir_type == OUTPUT && redir->redir_file) || \
	(redir->command && redir->redir_type == OUTPUT && redir->redir_file && redir->args) )
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

void redir_one_right_in_pipes(t_main *main)
{
	int fd;
	t_pipe *pipe;
	t_redir *redir;
	int len;

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

void redir_two_right_in_pipes(t_main *main)
{
    int fd;
    t_redir *redir;
    int len;
    t_pipe *pipe;
	
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

int redir_one_left_in_pipes(t_main *main)
{
	t_redir *redir;
	char *cmd;
	int file;
	t_pipe *pipe;

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
	return(0);
}

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

int redir_two_left_in_pipes(t_main *main)
 {
    t_redir *redir;
    char *cmd;
    char *file;
    t_pipe *pipe;
    
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
    return 0;
}

void process_redirects_in_pipes2(t_main *main)
{
    if (main->job->pipe_next->redir->redir_type == OUTPUT )
        redir_one_right_in_pipes(main);
    if (main->job->pipe->redir->redir_type == APPEND_OUTPUT)
        redir_two_right_in_pipes(main);
    if (main->job->pipe->redir->redir_type == INPUT)
        redir_one_left_in_pipes(main);
    if (main->job->pipe->redir->redir_type == INPUT_MULTILINE)
        redir_two_left_in_pipes(main);
}
