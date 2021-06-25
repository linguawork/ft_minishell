/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:39:21 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/25 19:53:31 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*dst2;
	const char	*src2;
	size_t		dstsizecpy;
	size_t		dst_new_len;

	dst2 = dst;
	src2 = src;
	dstsizecpy = dstsize;
	while (dstsizecpy-- != 0 && *dst != '\0')
		dst++;
	dst_new_len = dst - dst2;
	dstsizecpy = dstsize - dst_new_len;
	if (dstsizecpy-- == 0)
		return (dst_new_len + ft_strlen(src));
	while (*src != '\0')
	{
		if (dstsizecpy != 0)
		{
			*dst++ = *src;
			dstsizecpy--;
		}
		src++;
	}
	*dst = '\0';
	return (dst_new_len + (src - src2));
}
