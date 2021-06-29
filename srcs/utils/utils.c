/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/29 08:39:56 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_free(t_pipe *pipe)
{
	mem_free(&pipe->redir->command);
	arr_free(pipe->redir->args);
	mem_free(pipe->redir->args);
	pipe->redir->args = NULL;
}

static void	all_mem_free(t_job *job)
{
	pipe_free(job->pipe);
	if (job->job_next)
		pipe_free(job->pipe_next);
	while (job->job_next)
	{
		job = job->job_next;
		pipe_free(job->pipe);
		if (job->job_next)
			pipe_free(job->pipe_next);
	}
}

void	exit_with_error(t_main *main, char *massage)
{
	all_mem_free(main->job);
	printf("Error: %s\n", massage);
	exit(-1);
}

void	arr_free(char **arr)
{
    int i;

    i = 0;
	while (arr && arr[i])
	{
		mem_free(arr + i);
		arr[i] = NULL;
		i++;
	}
    arr = NULL;
}
