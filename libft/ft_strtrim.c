/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:20:09 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/28 10:43:46 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		size;

	size = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1)
		size = ft_strlen(s1);
	while (*s1 && ft_strrchr(set, s1[size]) && size > 0)
		size--;
	dest = ft_substr(s1, 0, size + 1);
	return (dest);
}
