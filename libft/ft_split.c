/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:29:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/17 08:33:04 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_lines(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			count++;
		}
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		count_line;
	char	**array;
	int		i;
	int		j;
	int		start;

	if (!s)
		return (NULL);
	count_line = count_lines(s, c);
	array = malloc((sizeof(char *) * (count_line + 1)));
	if (!array)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count_line)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array[j] = ft_substr(s, start, i++ - start);
	}
	array[j] = NULL;
	return (array);
}
