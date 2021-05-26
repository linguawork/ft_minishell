/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:27:26 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/26 09:20:57 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*dest;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(str);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (str && str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
