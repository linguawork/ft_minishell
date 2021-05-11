/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/11 09:34:05 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pars_space(t_main *main, char *line)
{
	int	i;

	i = 0;
	if (*line + 1 == '$')
		exit_game_with_error(main, "Double dollar");
	(*line)++;
	while (line[i] || !ft_strchr(NO_VALID_ENV_VAR, line[i]))
	{
		if (line[i] == '\\') //TODO fix if '\'
			i++;
		i++;
	}
	line[i] = '\0';
	return (ft_strdup(line));
}

char	*pars_double_quote(t_main *main, char *line)
{
	int	i;

	i = 0;
	if (*line + 1 == '$')
		exit_game_with_error(main, "Double dollar");
	(*line)++;
	while (line[i] || !ft_strchr(NO_VALID_ENV_VAR, line[i]))
	{
		if (line[i] == '\\') //TODO fix if '\'
			i++;
		i++;
	}
	line[i] = '\0';
	return (ft_strdup(line));
}

char	*pars_quote(t_main *main, char *line)
{
	int	i;

	i = 0;
	if (*line + 1 == '$')
		exit_game_with_error(main, "Double dollar");
	(*line)++;
	while (line[i] || !ft_strchr(NO_VALID_ENV_VAR, line[i]))
	{
		if (line[i] == '\\') //TODO fix if '\'
			i++;
		i++;
	}
	line[i] = '\0';
	return (ft_strdup(line));
}

char	*pars_env_variables(t_main *main, char **line)
{
	int	i;

	i = 0;
	if (**line + 1 == '$')
		exit_game_with_error(main, "Double dollar"); //TODO Double dollar
	(*line)++;
	while (line[0][i] && !ft_strchr(NO_VALID_ENV_VAR, line[0][i]))
	{
		if (line[0][i] == '\\') //TODO fix if '\'
			i++;
		i++;
	}
	(*line) += i;
	return (ft_substr(*line - i, 0, i));
}

void	main_parser(t_main *main, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			pars_space(main, line + i);
		if (line[i] == '"')
			pars_double_quote(main, line + i);
		if (line[i] ==  '\'')
			pars_quote(main, line + i);
		if (line[i] == '$')
			pars_env_variables(main, &line + i);
	}
}

void	parser(t_main *main)
{
	t_parser	parser;

	get_next_line(0, &parser.line);
	printf("%s\n", parser.line);
	main_parser(main, parser.line);
	if (ft_strnstr(parser.line, "exit", 4))
		main->exit = 1;
	mem_free(&parser.line);
}
