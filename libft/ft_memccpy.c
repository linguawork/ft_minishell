/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:45:24 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/12 17:32:59 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dstcpy;
	const unsigned char	*srccpy;

	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	if (n)
	{
		while (n--)
		{
			if (*srccpy == (unsigned char)c)
			{
				*dstcpy++ = *srccpy++;
				return (dstcpy);
			}
			*dstcpy++ = *srccpy++;
		}
	}
	return (NULL);
}
