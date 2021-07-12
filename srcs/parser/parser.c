/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 07:18:35 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_job	*distribution_parser(t_main *main, t_job *job, t_parser *parser)
{
	int	c;

	c = parser->cur_c;
	if (!ft_isprint(c) || c == ';')
		return (job);
	else if (c == '"')
		pars_double_quote(parser, main, job);
	else if (c == '\'')
		pars_quote(parser, main);
	else if (c == '$')
		pars_env_and_append_line(parser, main);
	else if (c == '|')
		job = get_next_pipe_addr(job, main, parser);
	else if (c == '>' || c == '<')
		redirect(main, job, parser);
	else if (c == ' ')
		write_pars_line(main, job, parser);
	else
		check_symbols_and_append_line(main, job, parser);
	return (job);
}

static void	check_error_syntax(t_parser *parser)
{
	char	*str;
	char	c;

	str = parser->string;
	c = *str;
	if (c == '\0')
		return ;
	else if (ft_strchr(SPECIFICATORS, *str)
		&& (*++str == '\0' || (ft_strchr(SPECIFICATORS, *str) && *str != c)))
	{
		print_error_syntax_message(parser->string, 1);
		*parser->string = '\0';
	}
	else if (ft_strchr(SPECIFICATORS, *str) && *str == c)
	{
		print_error_syntax_message(parser->string, 2);
		*parser->string = '\0';
	}
}

static void	parser_go(t_main *main, t_parser *parser)
{
	int		c;
	t_job	*job;

	job = main->job;
	check_error_syntax(parser);
	while (get_next_char(parser, &c) && c != '\0')
		job = distribution_parser(main, job, parser);
	write_pars_line(main, job, parser);
	/*
	 ** print_params(main);
	 */
}

void	parser(t_main *main, char *string)
{
	t_parser	parser;

	init_parser(&parser);
	parser.string = string;
	parser_go(main, &parser);
	parser.line = NULL;
}
