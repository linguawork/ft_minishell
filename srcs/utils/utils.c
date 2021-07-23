/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/23 12:33:35 by meunostu         ###   ########.fr       */
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
		redir->redir_next->error = 1;
		redir->redir_next = NULL;
	}
	if (redir->error != 0)
		redir_free(&redir);
}

void	free_data_job(t_job *job)
{
	free_data_redir(job->pipe->redir);
	if (job->pipe_next)
		free_data_redir(job->pipe_next->redir);
	if (job->job_next)
		free_data_job(job->job_next);
	pipe_free(&job->pipe);
	pipe_free(&job->pipe_next);
	job_free(&job);
}

void	all_mem_free(t_main *main)
{
	free_data_redir(main->job->pipe->redir);
	if (main->job->pipe_next)
	{
		main->job->pipe_next->redir->error = 1;
		free_data_redir(main->job->pipe_next->redir);
	}
	if (main->job->job_next)
		free_data_job(main->job->job_next);
}

void	exit_with_error(t_main *main, char *massage)
{
	all_mem_free(main);
	printf("Error: %s\n", massage);
	exit(-1);
}

char 	**ft_arrdup(char **src, int len)
{
	int		i;
	char	**dst;

	dst = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (src && *src)
		dst[i++] = *src++;
	return (dst);
}
