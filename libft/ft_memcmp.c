/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:23:16 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/18 19:21:29 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*copy1;
	const unsigned char	*copy2;

	copy1 = s1;
	copy2 = s2;
	while (n--)
		if (*copy1++ != *copy2++)
			return (*--copy1 - *--copy2);
	return (0);
}
