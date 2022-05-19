/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 06:40:33 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/23 10:56:01 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_arg_to_main(t_job *job, t_parser *parser)
{
	char	**src;
	char	**tmp;

	if (parser->pipe_exist != 1)
		src = job->pipe->redir->args;
	else
		src = job->pipe_next->redir->args;
	tmp = ft_arrdup(src, parser->args_len);
	tmp[parser->args_len++] = parser->line;
	tmp[parser->args_len] = NULL;
	free(src);
	if (parser->pipe_exist != 1)
		job->pipe->redir->args = tmp;
	else
		job->pipe_next->redir->args = tmp;
	parser->line = NULL;
}

static void	append_command_to_main(t_main *main, t_job *job, t_parser *parser)
{
	if (!job->pipe->redir->command)
		job->pipe->redir->command = parser->line;
	else
		job->pipe_next->redir->command = parser->line;
	if (parser->line)
		parser->pars_command = 1;
	main->job->num_commands++;
	parser->line = NULL;
}

void	check_symbols_and_append_line(t_main *main, t_job *job, t_parser
*parser)
{
	int	c;

	c = parser->cur_c;
	if ((!parser->pars_command && !ft_strchr(NO_VALID_COMMAND_SYMBOLS, c))
		|| (parser->pars_command && !ft_strchr(NO_VALID_SYMBOLS, c)))
		add_char(&parser->line, c);
	else
	{
		if (!parser->pars_command)
		{
			parser->pars_command = 1;
			append_command_to_main(main, job, parser);
			add_char(&parser->line, c);
		}
		else
		{
			append_arg_to_main(job, parser);
			add_char(&parser->line, c);
		}
	}
}

void	write_pars_line(t_main *main, t_job *job, t_parser *parser)
{
	if (!parser->pars_command && parser->line && *parser->line)
		append_command_to_main(main, job, parser);
	else if (parser->line && *parser->line)
		append_arg_to_main(job, parser);
}

void	append_buf(t_main *main, t_parser *parser, char *buf)
{
	char	*tmp;

	append_to_redir_file(main, parser, buf);
	tmp = parser->line;
	parser->line = ft_strjoin(parser->line, "\n");
	mem_free(&tmp);
	mem_free(&buf);
}
