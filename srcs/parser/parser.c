/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/21 14:06:16 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_job_next(t_job *job)
{
	t_job	*job_next;
	t_pipe	*pipe;
	t_redir	*redir;

	job_next = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));

	redir->redir_to = 0;
	job->job_next = job_next;
	job->job_next->pipe = pipe;
	job->job_next->pipe->redir = redir;
	job->job_next->pipe->redir->command = NULL;
	job->job_next->pipe->redir->flags = NULL;
	job->job_next->pipe->redir->args = NULL;
}

void	init_struct_pipe_next(t_job *job, int job_next)
{
	t_pipe	*pipe;
	t_redir	*redir;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));

	if (job_next)
	{
		redir->redir_to = 0;
		job->job_next->pipe_next = pipe;
		job->job_next->pipe_next->redir = redir;
		job->job_next->pipe_next->redir->command = NULL;
		job->job_next->pipe_next->redir->flags = NULL;
		job->job_next->pipe_next->redir->args = NULL;
	}
	else
	{
		redir->redir_to = 0;
		job->pipe_next = pipe;
		job->pipe_next->redir = redir;
		job->pipe_next->redir->command = NULL;
		job->pipe_next->redir->flags = NULL;
		job->pipe_next->redir->args = NULL;
	}
}

void	zero_parser(t_parser *parser)
{
	parser->pipe_exist = 1;
	parser->pars_command = 0;
	parser->pars_args = 0;
	parser->args_len = 0;
}

t_job	*get_next_pipe_addr(t_job *job, t_parser *parser)
{
	zero_parser(parser);
	if (!job->pipe_next)
	{
		init_struct_pipe_next(job, 0);
		return (job);
	}
	else
	{
		parser->pipe_exist = 0;
		init_struct_job_next(job);
		return (job->job_next);
	}
}

char 	*pars_env_variable(t_parser *parser)
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
	return (parser->variable);
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

void	append_arg_to_main(t_job *job, t_parser *parser)
{
	char **src;
	char **tmp;

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
//	job->pipe->redir->args = tmp;
}

void	append_command_to_main(t_job *job, t_parser *parser)
{
	if (!job->pipe->redir->command)
		job->pipe->redir->command = parser->line;
	else
		job->pipe_next->redir->command = parser->line;
	if (parser->line)
		parser->pars_command = 1;
	parser->line = NULL;
}

void	print_params(t_main *main)
{
	int i;

	i = 0;
	printf("command: %s", main->job->pipe->redir->command);
	while (main->job->pipe->redir->args && main->job->pipe->redir->args[++i])
		printf("\nargv[%d]: %s", i, main->job->pipe->redir->args[i]);
}

void	check_simbols_and_append_line(t_job *job, t_parser *parser)
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
			append_command_to_main(job, parser);
			add_char(&parser->line, c);
		}
		else
		{
			append_arg_to_main(job, parser);
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
	t_job *job;

	job = main->job;
	while (parser->cur_c != '\n' && get_next_char(parser, &c) && c != '\n')
	{
		if (c == '"')
			pars_double_quote(parser);
		else if (c == '\'')
			pars_quote(parser);
		else if (c == '$')
			pars_env_and_append_line(parser, main);
		if (c == '|')
			job = get_next_pipe_addr(job, parser);
		else if (c == ' ')
		{
			if (!parser->pars_command)
				append_command_to_main(job, parser);
			else
				append_arg_to_main(job, parser);
		}
		else
			check_simbols_and_append_line(job, parser);
	}
	if (!parser->pars_command)
		append_command_to_main(job, parser);
	else
		append_arg_to_main(job, parser);
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
	parser->pipe_exist = 0;
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
