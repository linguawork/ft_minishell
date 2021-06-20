/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 08:36:15 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/20 11:28:40 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	my_malloc(char **dest, int size)
{
	*dest = (char *)malloc(size);
	if (!*dest)
		return (0);
	else
		return (1);
}
