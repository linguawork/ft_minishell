/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/23 10:43:28 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pars_double_quote(t_parser *parser, t_main *main)
{
	int		c;

	parser->double_quote = 1;
	while (parser->cur_c != '\0' && get_next_char(parser, &c) && c != '"'
		   && c != '\0')
	{
		if (c == '$')
			pars_env_and_append_line(parser, main);
		else
			add_char(&parser->line, c);
	}
	if (c != '"')
		exit_with_error(main, "No two quote");
	parser->double_quote = 0;
}

static t_job	*distribution_parser(t_main *main, t_job *job, t_parser *parser)
{
	int	c;

	c = parser->cur_c;
	if (!ft_isprint(c) || c == ';')
		return (job);
	else if (c == '"')
		pars_double_quote(parser, main);
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

static int	check_error_syntax(t_parser *parser)
{
	char	*str;
	char	c;
	int		ret;

	ret = 0;
	str = parser->string;
	c = *str;
	if (c == '\0')
		ret = 3;
	else if (ft_strchr(SPECIFICATORS, *str)
		&& (*++str == '\0' || (ft_strchr(SPECIFICATORS, *str) && *str != c)))
		ret = 1;
	else if (ft_strchr(SPECIFICATORS, *str) && *str == c && ft_strchr
		(SPECIFICATORS, *++str))
		ret = 2;
	if (ret == 1 || ret == 2)
		print_error_syntax_message(parser->string, ret);
	return (ret);
}

static void	parser_go(t_main *main, t_parser *parser)
{
	int		c;
	t_job	*job;
	int		error;

	job = main->job;
	error = check_error_syntax(parser);
	while (!error && get_next_char(parser, &c) && c != '\0')
		job = distribution_parser(main, job, parser);
	write_pars_line(main, job, parser);
}

void	parser(t_main *main, char *string)
{
	t_parser	parser;

	init_parser(&parser);
	parser.string = string;
	parser_go(main, &parser);
	parser.line = NULL;
}
