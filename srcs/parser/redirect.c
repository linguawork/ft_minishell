/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 06:32:21 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/14 12:43:25 by meunostu         ###   ########.fr       */
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

void	append_to_redir_file(t_main *main, t_parser *parser, char *buf)
{
	int	c;
	int	i_old;
	char *str_old;

	i_old = parser->index;
	str_old = parser->string;
	parser->index = -1;
	parser->string = buf;
	while (get_next_char(parser, &c) && c != '\0')
	{
		if (c == '$')
			pars_env_and_append_line(parser, main);
		else
			add_char(&parser->line, c);
	}
	parser->index = i_old;
	parser->string = str_old;
	parser->cur_c = (int)str_old[i_old];
}

static char	*get_multi_text(t_main *main, t_parser *parser)
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
        {
            append_to_redir_file(main, parser, buf);
            parser->line = ft_strjoin(parser->line, "\n");
        }
		mem_free(&buf);
		buf = readline("> ");
		if (ft_strnstr(del, buf, ft_strlen(del)))
			find_key = 1;
//		else if (parser->line)
//			parser->line = ft_strjoin(parser->line, "\n");
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
	get_next_char(parser, &c);
	if (c != ' ' && c != '>' && c != '<')
		add_char(&parser->line, c);
	if (redir_type == INPUT_MULTILINE)
		redir_file = get_multi_text(main, parser);
	else
		redir_file = get_redir_file(parser);
	parser->line = NULL;
	redir->redir_type = redir_type;
	redir->redir_file = redir_file;
}
