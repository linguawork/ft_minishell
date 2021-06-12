/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/12 17:32:59 by meunostu         ###   ########.fr       */
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
	add_char(&parser->line, parser->cur_c);
	if (!get_next_char(parser, &c) || c == ' ' || c == '\n')
    {
        main->job->pipe->redir->args = malloc(sizeof(char *) * 1);
        *main->job->pipe->redir->args = parser->line;
        return ;
    }
	add_char(&parser->line, c);
	while (get_next_char(parser, &c) == 1 && c != ' ' && c != '\n')
		add_char(&parser->line, c);
	main->job->pipe->redir->flags = parser->line;
	parser->line = NULL;
}

void	parser_args_for_split(t_main *main, t_parser *parser)
{
	int		c;

	if (parser->cur_c != ' ' && parser->cur_c != '-')
		add_char(&parser->line, parser->cur_c);
	while (get_next_char(parser, &c) && c != '\n')
		add_char(&parser->line, c);
	main->job->pipe->redir->args = ft_split(parser->line, ' ');
}

void	parser_command(t_main *main, t_parser *parser)
{
	int		c;

	parser->pars_command = 1;
	while (get_next_char(parser, &c) && c != ' ' && c != '\n')
	{
		if (c == '$')
			pars_env_variables(main, parser);
		else
			pars_contract(main, parser);
	}
	main->job->pipe->redir->command = parser->line;
	parser->line = NULL;
}

void	parser_start(t_main *main, t_parser *parser)
{
	int c;
	parser_command(main, parser);
	if (parser->cur_c == '\n')
		return ;
	if (get_next_char(parser, &c) && c == '-')
		parser_flags(main, parser);
	if (parser->cur_c == '\n')
		return ;
	parser_args_for_split(main, parser);

//	printf("command: %s\n", main->job->pipe->redir->command);
//	printf("flags: %s\n", main->job->pipe->redir->flags);
//	while (main->job->pipe->redir->args)
//		printf("\n%s", *main->job->pipe->redir->args++);

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

    main->job->pipe->redir->command = NULL;
    main->job->pipe->redir->flags = NULL;
    main->job->pipe->redir->args = NULL;
	init_parser(&parser);
	parser_start(main, &parser);
	parser.line = NULL;
//	get_next_line(0, &parser.line);
////	printf("%s\n", parser.line);
//	if (ft_strnstr(parser.line, "exit", 4))
//		main->exit = 1;
//	main_parser(main, &parser);
//	mem_free(&parser->line);
}
