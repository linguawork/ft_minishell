/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 06:26:36 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 07:05:07 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	zero_parser(t_parser *parser)
{
	parser->pipe_exist = 1;
	parser->pars_command = 0;
	parser->pars_args = 0;
	parser->args_len = 0;
}

t_job	*get_next_pipe_addr(t_job *job, t_main *main, t_parser *parser)
{
	write_pars_line(main, job, parser);
	zero_parser(parser);
	if (!job->pipe_next)
	{
		init_struct_pipe_next(job, 0);
		main->job->num_pipes++;
		return (job);
	}
	else
	{
		parser->pipe_exist = 0;
		init_struct_job_next(job);
		main->job->num_pipes++;
		return (job->job_next);
	}
}

t_pipe	*get_current_pipe(t_job *job)
{
	if (job->pipe_next)
		return (job->pipe_next);
	else
		return (job->pipe);
}

t_redir	*get_curren_redir(t_redir *redir)
{
	if (redir->redir_next)
		return (get_curren_redir(redir->redir_next));
	else if (redir->redir_type != ERROR)
	{
		init_struct_redir_next(redir);
		return (redir->redir_next);
	}
	else
		return (redir);
}

void	pars_quote(t_parser *parser, t_main *main)
{
	int		c;

	if (parser->double_quote == 1)
	{
		add_char(&parser->line, parser->cur_c);
		return ;
	}
	parser->quote = 1;
	while (get_next_char(parser, &c) && c != '\'' && c != '\0')
		add_char(&parser->line, c);
	if (c != '\'')
		exit_with_error(main, "No two quote");
	parser->quote = 0;
}
