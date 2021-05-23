/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/23 09:23:35 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*pars_env_variables(t_main *main,  t_parser *parser)
{
	int		i;
	char	*line;

	line = parser->line;
	if (*line + 1 == '$')
		exit_with_error(main, "Double dollar"); //TODO Double dollar
	line++;
	i = 0;
	while (line[i] && !ft_strchr(NO_VALID_ENV_VAR, line[i]))
	{
//		if (line[i] == '\\') //TODO fix if '\'
//			i++;
		i++;
	}
	line += i;
	return (ft_substr(line - i, 0, i));
}

void	pars_contract(t_main *main, t_parser *parser)
{
	if (ft_strchr(NO_VALID_ENV_VAR, parser->cur_c))
		exit_with_error(main, ERROR_COMMAND);
	add_char(&parser->line, parser->cur_c);
}

void	pars(t_main *main, t_parser *parser)
{
	int 	i;
	char	*str;

	str = parser->line;
	i = 0;
	while (str[i])
	{
//		if (str[i] == ' ')
//			pars_space(main, parser->line);
//		if (str[i] == '"')
//			pars_double_quote(main, parser->line);
//		if (str[i] ==  '\'')
//			pars_quote(main, parser->line);
//		if (str[i] == '$')
			pars_env_variables(main, parser);
//		else
//			pars_contract(main, parser);
		i++;
	}
}

void	parser_flags(t_main *main, t_parser *parser)
{
	int		c;

	parser->pars_flags = 1;
	add_char(&parser->line, '-');
	if (get_next_char(&c) == 1 && c == ' ' && c != '\n')
	{
		parser->cur_c = c;
		return ;
	}
	add_char(&parser->line, c);
	while (get_next_char(&c) == 1 && c != ' ' && c != '\n')
		add_char(&parser->line, c);
	main->job->pipe->redir->flags = parser->line;
//	printf("%s\n", parser->line);
	parser->line = NULL;
}

void	parser_args_for_split(t_main *main, t_parser *parser)
{
	int		c;
	int readed;

	if (parser->cur_c != ' ' && parser->cur_c != '-')
		add_char(&parser->line, parser->cur_c);
	readed = get_next_char(&c);
	while (readed == 1 && c != '\n')
	{
		add_char(&parser->line, c);
		readed = get_next_char(&c);
		parser->cur_c = c;
	}
	main->job->pipe->redir->args = ft_split(parser->line, ' ');
//	while (main->job->pipe->redir->args)
//		printf("\n%s", *(main->job->pipe->redir->args)++);
}

void	parser_command(t_main *main, t_parser *parser)
{
	int		c;

	parser->pars_command = 1;
	while (get_next_char(&c) && c != ' ' && c != '\n')
	{
		parser->cur_c = c;
		if (c == '$')
			pars_env_variables(main, parser);
		else
			pars_contract(main, parser);
	}
	parser->cur_c = c;
	main->job->pipe->redir->command = parser->line;
//	printf("%s\n", parser->line);
	parser->line = NULL;
}

void	parser_start(t_main *main, t_parser *parser)
{
	int c;
	parser_command(main, parser);
	if (get_next_char(&c) && c == '-' && parser->cur_c == ' ')
		parser_flags(main, parser);
	parser->cur_c = c;
	parser_args_for_split(main, parser);

}

void	init_parser(t_parser *parser)
{
	parser->pars_command = 0;
	parser->pars_var = 0;
	parser->pars_args = 0;
	parser->line = NULL;
}

void	parser(t_main *main)
{
	t_parser	parser;

	init_parser(&parser);
	parser_start(main, &parser);
//	get_next_line(0, &parser.line);
////	printf("%s\n", parser.line);
//	if (ft_strnstr(parser.line, "exit", 4))
//		main->exit = 1;
//	main_parser(main, &parser);
//	mem_free(&parser->line);
}
