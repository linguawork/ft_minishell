/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:41:33 by areggie           #+#    #+#             */
/*   Updated: 2021/06/22 10:13:28 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*line1;
	unsigned char	*line2;
	int				i;

	line1 = (unsigned char *)s1;
	line2 = (unsigned char *)s2;
	i = 0;

    while ((s1 != NULL || line1[i] != '\0') && (s2 == NULL || line1[i] == '\0'))
        return(0);

    while (line1[i] == line2[i] && line1[i] != '\0' && line2[i] != '\0')
        i++;
	return (line1[i] - line2[i]);
}
