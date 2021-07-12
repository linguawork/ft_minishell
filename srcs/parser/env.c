/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 07:05:42 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 07:10:35 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*pars_env_variable(t_parser *parser)
{
	int		c;

	parser->pars_var = 1;
	if (ft_isalnum(parser->cur_c) || parser->cur_c == '_')
		add_char(&parser->variable, parser->cur_c);
	else
		return (parser->variable);
	while (get_next_char(parser, &c) && (ft_isalnum(c) || c == '_')
		&& c != ' ')
		add_char(&parser->variable, c);
	parser->index--;
	return (parser->variable);
}

static char	*get_env_value(char **my_env, char	*name_variable)
{
	int		i;
	char	*env;
	char	*env_value;

	i = 0;
	env_value = NULL;
	while (my_env[i])
	{
		if (ft_strnstr(my_env[i], name_variable, ft_strlen(name_variable)))
		{
			env = my_env[i];
			while (*env && *env != '=')
				env++;
			env++;
			env_value = ft_strdup(env);
			break ;
		}
		i++;
	}
	return (env_value);
}

static void	add_value_in_line(t_parser *parser)
{
	if (parser->variable_value)
		parser->line = ft_strjoin(parser->line, parser->variable_value);
	mem_free(&parser->variable_value);
	mem_free(&parser->variable);
}

static void	env_digit(t_parser *parser)
{
	int	c;

	if (parser->cur_c == '0')
		parser->line = ft_strjoin(parser->line, "minishell");
	else
	{
		while (get_next_char(parser, &c) && strchr(SPEC_SYMBOLS, c))
			add_char(&parser->line, c);
		parser->index--;
	}
}

void	pars_env_and_append_line(t_parser *parser, t_main *main)
{
	int		c;

	get_next_char(parser, &c);
	if (c == '?')
		parser->line = ft_strjoin(parser->line, ft_itoa(main->exit));
	else if (c == '\0' || c == ' ')
		parser->line = ft_strjoin(parser->line, "$");
	else if (c == '=' || c == '$')
		parser->line = ft_strjoin(parser->line, "$=");
	else if (ft_isdigit(c))
		env_digit(parser);
	else if (ft_strchr(SPECIFICATORS, c))
	{
		parser->index--;
		return ;
	}
	else
	{
		pars_env_variable(parser);
		parser->variable_value = get_env_value(main->my_env, parser->variable);
		add_value_in_line(parser);
	}
}
