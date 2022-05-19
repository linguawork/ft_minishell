/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:23 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 20:39:48 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_redir_type(t_main *main, int i)
{
	t_job	*job;

	job = main->job;
	if (i == 0 && job->pipe->redir->redir_type != ERROR)
		main->sub = 1;
	if (i == 1 && job->pipe_next->redir->redir_type != ERROR)
		main->sub = 1;
	if (i > 1)
		job = job->job_next;
	if (i == 2 && job->pipe->redir->redir_type != ERROR)
		main->sub = 1;
	if (i == 3 && job->pipe_next->redir->redir_type != ERROR)
		main->sub = 1;
	return (0);
}

void	process_redirs_in_pipes(t_main *main, int *prev_pipe_fds, \
int *next_pipe_fds)
{
	int	fork_res;

	fork_res = fork();
	if (fork_res == 0)
	{
		stdin_and_out_to_pipes(prev_pipe_fds, next_pipe_fds);
		signal(SIGQUIT, SIG_DFL);
		process_redirects_in_pipes2(main);
	}
}

void	proc_redirs_in_p(t_main *main, int *prev_pipe_fds, int *next_pipe_fds)
{
	process_redirs_in_pipes(main, prev_pipe_fds, next_pipe_fds);
	main->sub = 0;
}

void	proc_pipes(t_main *main, int *prev_pipe_fds, int *next_pipe_fds, \
char **cmd)
{
	if (main->flag2 != 1)
		main->fork_res = fork();
	if (main->fork_res == 0)
		forking_in_pipes(main, prev_pipe_fds, next_pipe_fds, cmd);
}

int	execute_pipes_and_redirs(t_main *main)
{
	char	***commands;
	int		prev_pipe_fds[2];
	int		next_pipe_fds[2];
	char	**cmd;
	int		i;

	main->fork_res = -1;
	execute_pipes_beginning_part(main, next_pipe_fds);
	commands = pipe_cmd_args_recorder(main);
	i = -1;
	while (++i < main->job->num_commands)
	{
		execute_pipes_cycle_part1(main, i, prev_pipe_fds, next_pipe_fds);
		cmd = &*commands[i];
		process_folder_in_pipes(main, cmd);
		check_for_redir_type(main, i);
		if (main->sub == 1 && main->flag2 != 1)
			proc_redirs_in_p(main, prev_pipe_fds, next_pipe_fds);
		else
			proc_pipes(main, prev_pipe_fds, next_pipe_fds, cmd);
		close_free(commands, i, prev_pipe_fds);
	}
	execute_pipes_end_part(main, i, commands);
	return (0);
}
