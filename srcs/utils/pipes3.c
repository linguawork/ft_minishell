/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 13:26:08 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 14:39:29 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***pipe_cmd_args_recorder(t_main *main)
{
	int		i;
	int		c_num;
	char	***cmds;
	int		p_num;
	t_job	*job;

	job = main->job;
	c_num = main->job->num_commands;
	p_num = main->job->num_pipes;
	cmds = (char ***) malloc(sizeof(char *) * (c_num + 1));
	i = 0;
	if (p_num == 1)
		cmds = one_pipe_cmd(job, cmds, i);
	if (p_num > 1)
		cmds = many_pipes_cmd(job, cmds, i);
	return (cmds);
}

void	stdin_and_out_to_pipes(int prev_fds[], int next_fds[])
{
	if (prev_fds[0] >= 0)
	{
		dup2(prev_fds[0], 0);
		close(prev_fds[0]);
		close(prev_fds[1]);
	}
	if (next_fds[1] >= 0)
	{
		dup2(next_fds[1], 1);
		close(next_fds[1]);
		close(next_fds[0]);
	}
}

void	next_pipe_init(int *next_pipe_fds)
{
	next_pipe_fds[0] = -1;
	next_pipe_fds[1] = -1;
}

void	process_multiline_in_pipes(t_main *main)
{
	if ((main->job->num_commands == main->job->num_pipes) || \
	(main->job->num_commands < main->job->num_pipes))
	{
		ft_putstr_fd("Error: no need to process multiline!\n", 2);
		return ;
	}
}

void	execute_pipes_cycle_part1(t_main *main, int i, int *prev_pipe_fds, \
int *next_pipe_fds)
{
	signal(SIGINT, SIG_IGN);
	prev_pipe_fds[0] = next_pipe_fds[0];
	prev_pipe_fds[1] = next_pipe_fds[1];
	if (i != main->job->num_commands - 1)
		pipe(next_pipe_fds);
	else
		next_pipe_init(next_pipe_fds);
}
