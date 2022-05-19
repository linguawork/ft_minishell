/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 13:25:01 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 13:25:05 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pipe_next_cmd_array_with_no_args(char **cmd_array, char *cmd)
{
	cmd_array = (char **) malloc(sizeof(char *) * (1 + 1));
	cmd_array[0] = cmd;
	return (cmd_array);
}

char	**pipe_next_cmd_array_with_args(t_job *job, char **cmd_array, char *cmd)
{
	int		len;
	char	**args;
	int		i;
	int		j;

	i = 1;
	j = 0;
	args = job->pipe_next->redir->args;
	len = how_many_lines((char **) args);
	cmd_array = (char **) malloc(sizeof(char *) * (len + 1 + 1));
	cmd_array[0] = cmd;
	while (args[j] != NULL)
	{
		cmd_array[i] = args[j];
		j++;
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

char	**pipe_next_cmd_recorder(t_job *job)
{
	char	**cmd_array;
	char	**args;
	char	*cmd;

	cmd_array = NULL;
	cmd = job->pipe_next->redir->command;
	args = job->pipe_next->redir->args;
	if (args == NULL)
		cmd_array = pipe_next_cmd_array_with_no_args(cmd_array, cmd);
	else
		cmd_array = pipe_next_cmd_array_with_args(job, cmd_array, cmd);
	return (cmd_array);
}

char	***one_pipe_cmd(t_job *job, char ***cmds, int i)
{
	cmds[i] = cmd_args_to_argv_recorder_p(job);
	cmds[++i] = pipe_next_cmd_recorder(job);
	cmds[++i] = NULL;
	return (cmds);
}

char	***many_pipes_cmd(t_job *job, char ***cmds, int i)
{	
	cmds[i] = cmd_args_to_argv_recorder_p(job);
	cmds[++i] = pipe_next_cmd_recorder(job);
	while (job->job_next)
	{
		job = job->job_next;
		cmds[++i] = cmd_args_to_argv_recorder_p(job);
		if (job->pipe_next != NULL)
			cmds[++i] = pipe_next_cmd_recorder(job);
	}
	cmds[++i] = NULL;
	return (cmds);
}
