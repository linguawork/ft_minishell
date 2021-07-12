/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 06:32:21 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 07:12:28 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_redir_file(t_parser *parser)
{
	int	c;

	while (get_next_char(parser, &c) && (ft_strchr(VALID_SYMBOLS_FILES, c)
			|| ft_isalnum(c)) && c != '\0')
	{
		if (c == '>' || c == '<')
		{
			parser->index--;
			break ;
		}
		add_char(&parser->line, c);
	}
	return (parser->line);
}

static char	*get_multi_text(t_parser *parser)
{
	int		c;
	int		find_key;
	char	*del;
	char	*buf;

	del = NULL;
	buf = NULL;
	while (get_next_char(parser, &c) && c != ' ')
		add_char(&parser->line, c);
	del = parser->line;
	parser->line = NULL;
	find_key = 0;
	while (!find_key)
	{
		if (buf)
			parser->line = ft_strjoin(parser->line, buf);
		mem_free(&buf);
		buf = readline("> ");
		if (ft_strnstr(del, buf, ft_strlen(del)))
			find_key = 1;
		else if (parser->line)
			parser->line = ft_strjoin(parser->line, "\n");
	}
	return (parser->line);
}

static t_options	get_redir_type(t_parser *parser)
{
	int			c;
	int			prev_c;
	t_options	redir_type;

	if (parser->cur_c == '>')
		redir_type = OUTPUT;
	else if (parser->cur_c == '<')
		redir_type = INPUT;
	prev_c = parser->cur_c;
	if (!get_next_char(parser, &c))
		return (ERROR);
	if (prev_c == '>' && c == '>')
		redir_type = APPEND_OUTPUT;
	else if (prev_c == '<' && c == '<')
		redir_type = INPUT_MULTILINE;
	else if (c != ' ')
		add_char(&parser->line, c);
	return (redir_type);
}

void	redirect(t_main *main, t_job *job, t_parser *parser)
{
	int			c;
	t_options	redir_type;
	char		*redir_file;
	t_pipe		*pipe;
	t_redir		*redir;

	write_pars_line(main, job, parser);
	pipe = get_current_pipe(job);
	redir = get_curren_redir(pipe->redir);
	redir_type = get_redir_type(parser);
	if (redir_type == ERROR || !get_next_char(parser, &c))
	{
		all_mem_free(main);
		print_error_syntax_message("newline", 7);
        main->exit = 258;
		return ;
	}
	if (c != ' ' && c != '>' && c != '<')
		add_char(&parser->line, c);
	if (redir_type == INPUT_MULTILINE)
		redir_file = get_multi_text(parser);
	else
		redir_file = get_redir_file(parser);
	parser->line = NULL;
	redir->redir_type = redir_type;
	redir->redir_file = redir_file;
}

void	pars_double_quote(t_parser *parser, t_main *main, t_job *job)
{
	int		c;

	parser->double_quote = 1;
	while (parser->cur_c != '\0' && get_next_char(parser, &c) && c != '"'
		&& c != '\0')
	{
		if (c == '$')
		{
			pars_env_and_append_line(parser, main);
			if (parser->cur_c == '"')
				set_error_and_free_pipe(job, -1);
		}
		else
			add_char(&parser->line, c);
	}
	if (c != '"')
		exit_with_error(main, "No two quote");
	parser->double_quote = 0;
}
