/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:40:47 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/17 21:57:12 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_main *main)
{
	t_job	*job;
	t_pipe	*pipe;
	t_redir	*redir;

	job = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));
	main->sub = 0;
	main->flag2 = 0;
	main->exit = 0;
	job->pipe_next = NULL;
	job->job_next = NULL;
	job->num_commands = 0;
	job->num_pipes = 0;
	job->num_redirects = 0;
	redir->redir_next = NULL;
	redir->redir_file = NULL;
	redir->redir_type = ERROR;
	main->job = job;
	main->job->pipe = pipe;
	main->job->pipe->redir = redir;
	main->job->pipe->redir->command = NULL;
	main->job->pipe->redir->args = NULL;
	main->job->pipe->redir->error = 0;
}

void	end_session(t_main *main)
{
	all_mem_free(main);
	main->job->num_commands = 0;
	main->job->num_pipes = 0;
	main->job->num_redirects = 0;
	main->job->job_next = NULL;
	main->job->pipe_next = NULL;
	main->job->pipe->redir->redir_next = NULL;
	main->job->pipe->redir->error = 0;
	main->job->pipe->redir->redir_type = ERROR;
}
