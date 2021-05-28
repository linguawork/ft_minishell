/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 08:32:49 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/28 12:02:10 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_realloc(char **dst, int size)
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
	res[len] = c;
	mem_free(str);
	*str = res;
	return (1);
}

int	get_next_char(t_parser *parser,int *c)
{
	char	*buf;
	int		readed;

	buf = malloc(sizeof(char) * 1);
	readed = read(0, buf, 1);
	if (readed == 0)
		return (0);
	else if (readed < 0)
		return (-1);
	*c = *buf;
	parser->cur_c = *buf;
	mem_free(&buf);
	return (1);
}

void	set_error(t_redir *redir, char *error)
{
	redir->error = error;
}
