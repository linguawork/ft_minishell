/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/17 08:33:04 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe *pipe_next_address(t_main *main)
{
	struct t_job *job;
	struct t_pipe *pipe;
	struct t_redir *redir;

	if (!main->job->pipe_next->redir->command)
		return (main->job->pipe_next);
	else
	{
		job = (struct t_job *)malloc(sizeof(t_job));
		main->job->job_next = job;
		return (main->job->pipe);
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

void	pars_env_and_add_to_pars_line(t_parser *parser, t_main *main)
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

void	copy_matrix(char ***dst, char **src, int len)
{
	int i;

	i = -1;
	while (src && src[++i] && len--)
		*dst[i] = src[i];
}

void	append_arg(char ***dst, t_parser *parser)
{
	char **src;
	char **tmp;

	src = *dst;
	tmp = (char **)malloc(sizeof(char *) * (parser->args_i + 2));
	copy_matrix(&tmp, src, parser->args_i);
	tmp[parser->args_i++] = parser->line;
	tmp[parser->args_i] = NULL;
	*dst = tmp;
	parser->line = NULL;
}

void	parser_args(t_main *main, t_parser *parser)
{
	int		c;

	parser->pars_args = 1;
	while (get_next_char(parser, &c) && c != '\n')
	{
		if (c == '$')
			pars_env_and_add_to_pars_line(parser, main);
		else if (c == ' ')
			append_arg(&main->job->pipe->redir->args, parser);
		else
			add_char(&parser->line, c);
	}
	append_arg(&main->job->pipe->redir->args, parser);
}

void	pars_contract(t_main *main, t_parser *parser)
{
	if (ft_strchr(NO_VALID_COMMAND_SIMBOLS, parser->cur_c))
		exit_with_error(main, ERROR_COMMAND);
	add_char(&parser->line, parser->cur_c);

}

void	parser_command(t_main *main, t_parser *parser)
{
	int		c;

	parser->pars_command = 1;
	while (get_next_char(parser, &c) && c != ' ' && c != '\n')
	{
		if (c == '$')
			pars_env_and_add_to_pars_line(parser, main);
		else
			add_char(&parser->line, c);
	}
	main->job->pipe->redir->command = parser->line;
	parser->line = NULL;
}

void	print_params(t_main *main)
{
	int i;

	i = 0;
	printf("\ncommand: %s", main->job->pipe->redir->command);
	while (*main->job->pipe->redir->args)
		printf("\nargv[%d]: %s", i++, *main->job->pipe->redir->args++);
}

void	parser_start(t_main *main, t_parser *parser)
{
	parser_command(main, parser);
	if (parser->cur_c != '\n')
		parser_args(main, parser);
 	print_params(main);
}

void	init_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->pars_command = 0;
	parser->pars_args = 0;
	parser->pars_flags = 0;
	parser->pars_var = 0;
	parser->args_i = 0;
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
	parser_start(main, &parser);
	end_session_pars(&parser);
//	TODO add static to functions
}
