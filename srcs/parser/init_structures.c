/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 06:12:30 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 06:22:05 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_job_next(t_job *job)
{
	t_job	*job_next;
	t_pipe	*pipe;
	t_redir	*redir;

	job_next = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));
	job->job_next = job_next;
	job->job_next->pipe = pipe;
	job->job_next->pipe->redir = redir;
	job->job_next->pipe->redir->command = NULL;
	job->job_next->pipe->redir->args = NULL;
	job->job_next->pipe->redir->redir_file = NULL;
	job->job_next->pipe->redir->redir_type = ERROR;
	job->job_next->pipe->redir->redir_next = NULL;
	job->job_next->pipe_next = NULL;
	job->job_next->job_next = NULL;
}

static void	init_pipe_in_job_next(t_job *job)
{
	job->job_next->pipe_next->redir->command = NULL;
	job->job_next->pipe_next->redir->args = NULL;
	job->job_next->pipe_next->redir->redir_file = NULL;
	job->job_next->pipe_next->redir->redir_type = ERROR;
	job->job_next->pipe_next->redir->redir_next = NULL;
}

void	init_struct_pipe_next(t_job *job, int job_next)
{
	t_pipe	*pipe;
	t_redir	*redir;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (job_next)
	{
		job->job_next->pipe_next = pipe;
		job->job_next->pipe_next->redir = redir;
		init_pipe_in_job_next(job);
	}
	else
	{
		job->pipe_next = pipe;
		job->pipe_next->redir = redir;
		job->pipe_next->redir->command = NULL;
		job->pipe_next->redir->args = NULL;
		job->pipe_next->redir->redir_file = NULL;
		job->pipe_next->redir->redir_type = ERROR;
		job->pipe_next->redir->redir_next = NULL;
	}
}

void	init_struct_redir_next(t_redir *redir)
{
	t_redir	*redir_next;

	redir_next = (t_redir *)malloc(sizeof(t_redir));
	redir->redir_next = redir_next;
	redir->redir_next->command = NULL;
	redir->redir_next->args = NULL;
	redir->redir_next->redir_file = NULL;
	redir->redir_next->redir_type = ERROR;
	redir->redir_next->redir_next = NULL;
}

void	init_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->pars_command = 0;
	parser->pars_args = 0;
	parser->pars_var = 0;
	parser->double_quote = 0;
	parser->args_len = 0;
	parser->pipe_exist = 0;
	parser->index = -1;
	parser->variable = NULL;
	parser->variable_value = NULL;
}
