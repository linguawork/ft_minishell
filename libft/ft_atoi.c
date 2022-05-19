/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:32:27 by meunostu          #+#    #+#             */
/*   Updated: 2022/05/19 14:22:03 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	countneg;

	countneg = 0;
	i = 0;
	result = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == '\n' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			countneg++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (countneg == 1)
		return (result * (-1));
	else
		return (result);
	return (0);
}
