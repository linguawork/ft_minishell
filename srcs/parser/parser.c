/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/18 17:46:45 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_job_next(t_main *main)
{
	t_job	*job;
	t_pipe	*pipe;
	t_redir	*redir;

	job = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));

	redir->redir_to = 0;
	main->job = job;
	main->job_next->pipe = pipe;
	main->job_next->pipe->redir = redir;
	main->job_next->pipe->redir->command = NULL;
	main->job_next->pipe->redir->flags = NULL;
	main->job_next->pipe->redir->args = NULL;
}

t_pipe *get_pipe_next_addr(t_main *main)
{
	if (!main->job->pipe_next->redir->command)
		return (main->job->pipe_next);
	else
	{
		init_struct_job_next(main);
		return (main->job_next->pipe);
	}
}

void	pars_env_variable(t_parser *parser)
{
	int		c;

	parser->pars_var = 1;
	add_char(&parser->variable, parser->cur_c);
	while (get_next_char(parser, &c) && c != ' ' && c != '\n')
	{
		if (!ft_strchr(NO_VALID_ENV_VAR, c))
			add_char(&parser->variable, c);
		else if (c == '$')
			c = '$';
		//TODO Double dollar
	}
}

char	*get_env_value(char **my_env, char	*name_variable)
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

void	add_value_in_line(t_parser *parser)
{
	if (parser->variable_value)
		parser->line = ft_strjoin(parser->line, parser->variable_value);
	mem_free(&parser->variable_value);
	mem_free(&parser->variable);
}

void	pars_env_and_append_line(t_parser *parser, t_main *main)
{
	int		c;

	get_next_char(parser, &c);
	if (c == '?')
		parser->line = ft_strjoin(parser->line, ft_itoa(main->exit));
	else if (c == '=')
		parser->line = ft_strjoin(parser->line, "$=");
	else
	{
		pars_env_variable(parser);
		parser->variable_value = get_env_value(main->my_env, parser->variable);
		add_value_in_line(parser);
	}
}

char 	**ft_arrdup(char **src, int len)
{
	int i;
	char **dst;

	dst = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (src && *src)
		dst[i++] = *src++;
	return (dst);
}

void	append_arg_to_main(t_main *main, t_parser *parser)
{
	char **src;
	char **tmp;

	src = main->job->pipe->redir->args;
	tmp = ft_arrdup(src, parser->args_len);
	tmp[parser->args_len++] = parser->line;
	tmp[parser->args_len] = NULL;
	main->job->pipe->redir->args = tmp;
	parser->line = NULL;
	free(src);
}

void	append_command_to_main(t_main *main, t_parser *parser)
{
	main->job->pipe->redir->command = parser->line;
	parser->line = NULL;
	parser->pars_command = 1;
}

void	print_params(t_main *main)
{
	int i;

	i = 0;
	printf("command: %s", main->job->pipe->redir->command);
	while (main->job->pipe->redir->args && main->job->pipe->redir->args[++i])
		printf("\nargv[%d]: %s", i, main->job->pipe->redir->args[i]);
}

void	check_simbols_and_append_line(t_main *main, t_parser *parser)
{
	int c;

	c = parser->cur_c;
	if ((!parser->pars_command && !ft_strchr(NO_VALID_COMMAND_SIMBOLS, c)) ||
		(parser->pars_command && !ft_strchr(NO_VALID_SIMBOLS, c)))
			add_char(&parser->line, c);
	else
	{
		if (!parser->pars_command)
		{
			parser->pars_command = 1;
			append_command_to_main(main, parser);
			add_char(&parser->line, c);
		}
		else
		{
			append_arg_to_main(main, parser);
			add_char(&parser->line, c);
		}
	}
}

void	pars_double_quote(t_parser *parser)
{
	int		c;

	while (get_next_char(parser, &c) && c != '"' && c != '\n')
		add_char(&parser->line, c);
}

void	pars_quote(t_parser *parser)
{
	int		c;

	while (get_next_char(parser, &c) && c != '\'' && c != '\n')
		add_char(&parser->line, c);
}

void	parser_go(t_main *main, t_parser *parser)
{
	int		c;

	while (parser->cur_c != '\n' && get_next_char(parser, &c) && c != '\n')
	{
		if (c == '"')
			pars_double_quote(parser);
		else if (c == '\'')
			pars_quote(parser);
		else if (c == '$')
			pars_env_and_append_line(parser, main);
		else if (c == ' ')
		{
			if (!parser->pars_command)
				append_command_to_main(main, parser);
			else
				append_arg_to_main(main, parser);
		}
		else
			check_simbols_and_append_line(main, parser);
	}
	if (!parser->pars_command)
        append_command_to_main(main, parser);
	else
	    append_arg_to_main(main, parser);
// 	print_params(main);
}

void	init_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->pars_command = 0;
	parser->pars_args = 0;
	parser->pars_flags = 0;
	parser->pars_var = 0;
	parser->args_len = 0;
	parser->variable = NULL;
	parser->variable_value = NULL;
}

void	end_session_pars(t_parser *parser)
{
	parser->line = NULL;
}

void	parser(t_main *main)
{
	t_parser	parser;

	init_parser(&parser);
	parser_go(main, &parser);
	end_session_pars(&parser);
//	TODO add static to functions
}
