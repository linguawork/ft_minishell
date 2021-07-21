/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/09 12:56:13 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_redir(t_redir *redir)
{
	mem_free(&redir->command);
/*
**	while (redir->args && *redir->args)
**		mem_free(redir->args++);
*/
	arrays_free(redir->args);/* just free to avoid double freeing*/
	redir->args = NULL;
	mem_free(&redir->redir_file);
	if (redir->redir_next)
	{
		redir->redir_next->error = 1;
		free_data_redir(redir->redir_next);
		redir->redir_next->error = 1;
		redir->redir_next = NULL;
	}
//	if (redir->error != 0)
//		redir_free(&redir);
}

void	free_data_job(t_job **job_addr)
{
    t_job *job;

    job = *job_addr;
	free_data_redir(job->pipe->redir);
	if (job->pipe_next)
		free_data_redir(job->pipe_next->redir);
	if (job->job_next)
		free_data_job(&job->job_next);
//	pipe_free(&job->pipe);
//	pipe_free(&job->pipe_next);
//	job_free(&job);
    free(job->pipe);
    free(job->pipe_next);
    free(job);
    *job_addr = NULL;

}

void    free_data_pipe_next(t_job *job)
{
	free_data_redir(job->pipe->redir);
    free(job->pipe);
    if (job->pipe_next)
    {
        free_data_redir(job->pipe_next->redir);
        free(job->pipe_next);
    }
}

void    free_pipe(t_pipe *pipe)
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
    t_job   *job_tmp;
    void    *asd;

    job_tmp = main->job;
    while (job_tmp) {

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



//	free_data_redir(main->job->pipe->redir);
////    pipe_free(&main->job->pipe);
//	if (main->job->pipe_next)
//	{
////        free_data_pipe_next(main->job);
//		main->job->pipe_next->redir->error = 1;
//		free_data_redir(main->job->pipe_next->redir);
//        pipe_free(&main->job->pipe_next);
////        free(main->job->pipe_next);
////        main->job->pipe_next = NULL;
//	}
//	if (main->job->job_next)
//    {
//	    free_data_job(&main->job->job_next);
//    }
}

void	exit_with_error(t_main *main, char *massage)
{
	all_mem_free(main);
	printf("Error: %s\n", massage);
	exit(-1);
}

char 	**ft_arrdup(char **src, int len)
{
	int i;
	char **dst;

	dst = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (src && *src)
		dst[i++] = *src++;
	return (dst);
}
