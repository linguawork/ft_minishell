/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:31:53 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/18 20:09:37 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_src;
	unsigned char	*temp_dst;

	if (!src && !dst)
		return (dst);
	temp_src = (unsigned char *)src;
	temp_dst = (unsigned char *)dst;
	while (n--)
		*temp_dst++ = *temp_src++;
	return (dst);
}
