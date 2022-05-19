/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 23:43:53 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 23:44:25 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_redir(t_redir *redir)
{
	mem_free(&redir->command);
	arrays_free(redir->args);
	redir->args = NULL;
	mem_free(&redir->redir_file);
	if (redir->redir_next)
	{
		redir->redir_next->error = 1;
		free_data_redir(redir->redir_next);
		free(redir->redir_next);
		redir->redir_next->error = 1;
		redir->redir_next = NULL;
	}
}

void	free_data_job(t_job **job_addr)
{
	t_job	*job;

	job = *job_addr;
	free_data_redir(job->pipe->redir);
	if (job->pipe_next)
		free_data_redir(job->pipe_next->redir);
	if (job->job_next)
		free_data_job(&job->job_next);
	free(job->pipe);
	free(job->pipe_next);
	free(job);
	*job_addr = NULL;
}

void	free_data_pipe_next(t_job *job)
{
	free_data_redir(job->pipe->redir);
	free(job->pipe);
	if (job->pipe_next)
	{
		free_data_redir(job->pipe_next->redir);
		free(job->pipe_next);
	}
}

void	free_pipe(t_pipe *pipe)
{
	if (pipe)
	{
		free_data_redir(pipe->redir);
		free(pipe->redir);
		free(pipe);
	}
}

void	all_mem_free(t_main *main)
{
	t_job	*job_tmp;
	void	*asd;

	job_tmp = main->job;
	while (job_tmp)
	{
		free_pipe(job_tmp->pipe_next);
		if (job_tmp != main->job)
		{
			free_pipe(job_tmp->pipe);
			asd = job_tmp->job_next;
			free(job_tmp);
			job_tmp = asd;
		}
		else
		{
			free_data_redir(job_tmp->pipe->redir);
			job_tmp = job_tmp->job_next;
		}
	}
	main->job->job_next = NULL;
	main->job->pipe_next = NULL;
}
