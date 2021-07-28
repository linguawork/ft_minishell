/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:31 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 20:41:41 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forking_in_pipes(t_main *main, int *prev_pipe_fds, int *next_pipe_fds, \
char **cmd)
{
	stdin_and_out_to_pipes(prev_pipe_fds, next_pipe_fds);
	process_builtins_in_pipes(main, cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(cmd[0], '/'))
	{
		execve(cmd[0], cmd, NULL);
		exec_mistakes(main);
		exit(126);
	}
	else
		process_exe_in_pipes(main, cmd);
}

void	execute_pipes_end_part(t_main *main, int i, char ***commands)
{
	free(commands);
	waitpid(main->fork_res, &main->exit, 0);
	exit_code(main);
	i = 1;
	while (i < main->job->num_commands)
	{
		wait(NULL);
		i++;
	}
	main->fork_res = -1;
}

void	execute_pipes_beginning_part(t_main *main, int *next_pipe_fds)
{
	process_multiline_in_pipes(main);
	next_pipe_init(next_pipe_fds);
}

void	close_free(char ***commands, int i, int *prev_pipe_fds)
{
	close(prev_pipe_fds[0]);
	close(prev_pipe_fds[1]);
	free(commands[i]);
}

int	execute_pipes(t_main *main)
{
	char	***commands;
	int		prev_pipe_fds[2];
	int		next_pipe_fds[2];
	char	**cmd;
	int		i;

	main->fork_res = -1;
	execute_pipes_beginning_part(main, next_pipe_fds);
	commands = pipe_cmd_args_recorder(main);
	i = 0;
	while (i < main->job->num_commands)
	{
		execute_pipes_cycle_part1(main, i, prev_pipe_fds, next_pipe_fds);
		cmd = &*commands[i];
		process_folder_in_pipes(main, cmd);
		if (main->flag2 != 1)
			main->fork_res = fork();
		if (main->fork_res == 0)
			forking_in_pipes(main, prev_pipe_fds, next_pipe_fds, cmd);
		close_free(commands, i, prev_pipe_fds);
		i++;
	}
	execute_pipes_end_part(main, i, commands);
	return (0);
}
