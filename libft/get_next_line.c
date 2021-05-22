/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 09:53:26 by meunostu          #+#    #+#             */
/*   Updated: 2021/04/26 13:42:53 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*before_n(char *cache)
{
	char		*dst;
	size_t		i;

	i = 0;
	while (cache && cache[i] && cache[i] != '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	while (i--)
		dst[i] = cache[i];
	return (dst);
}

static	char	*after_n(char *cache)
{
	char		*p_n;
	char		*dst;

	p_n = ft_strchr(cache, '\n');
	if (!cache || !*cache || !p_n)
	{
		free(cache);
		return (NULL);
	}
	dst = ft_strdup(p_n + 1);
	free(cache);
	return (dst);
}

static int	write_cache(char **cache, int fd)
{
	int		readed;
	char	*buf;

	readed = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!ft_strchr(*cache, '\n'))
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == 0)
			break ;
		else if (readed < 0)
		{
			free(buf);
			free(*cache);
			return (-1);
		}
		buf[readed] = '\0';
		*cache = ft_strjoin(*cache, buf);
		if (!*cache)
			return (-1);
	}
	free(buf);
	return (readed);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache;
	int			readed;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || (read(fd, NULL, 0) == -1))
		return (-1);
	readed = write_cache(&cache, fd);
	if (readed == -1)
		return (-1);
	*line = before_n(cache);
	if (!*line)
		return (-1);
	cache = after_n(cache);
	if (readed == 0)
		return (0);
	else
		return (1);
}
