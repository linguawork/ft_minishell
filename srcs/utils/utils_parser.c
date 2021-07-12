/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 08:32:49 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/10 06:07:09 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_realloc(char **dst, int size)
{
	*dst = ft_calloc(size, 1);
	if (!*dst)
		return (0);
	return (1);
}

int	add_char(char **str, int c)
{
	int	len;
	char	*res;

	len = ft_strlen(*str);
	if (!ft_realloc(&res, sizeof(char) * (len + 2)))
		return (0);
	if (*str)
		ft_memcpy(res, *str, len);
	res[len++] = c;
	res[len] = '\0';
	mem_free(str);
	*str = res;
	return (1);
}

int	get_next_char(t_parser *parser, int *c)
{
	parser->index++;
	*c = parser->string[parser->index];
	parser->cur_c = *c;
	if (!parser->string[parser->index])
		return (0);
	return (1);
}

void	set_error_and_free_pipe(t_job *job, int n)
{
	t_pipe *pipe;

	pipe = get_current_pipe(job);
	free_data_redir(pipe->redir);
	pipe->redir->error = n;
}

void	print_error_syntax_message(char *string, int len)
{
	char	*error;
	error = "minishell> syntax error near unexpected token `";
	write(1, error, strlen(error));
	write(1, string, len);
	write(1, "'\n", 2);
}
