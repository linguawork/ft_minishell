/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 18:13:53 by areggie           #+#    #+#             */
/*   Updated: 2021/07/25 20:05:55 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_recorder2(char **envir, int len)
{
	char	**e;
	int		i;

	e = (char **) malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (envir[i] && i != len)
	{
		e[i] = envir[i];
		i++;
	}
	return (e);
}

char	**env_recorder(t_main *main)
{
	char	**e;
	int		length;
	int		i;

	length = how_many_lines(main->my_env);
	e = (char **) malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (main->my_env[i] != NULL)
	{
		e[i] = main->my_env[i];
		i++;
	}
	e[i] = NULL;
	return (e);
}

void	double_for_sort_algo(char **envir, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(envir[i], envir[j]) > 0)
			{
				tmp = envir[i];
				envir[i] = envir[j];
				envir[j] = tmp;
			}
			j++;
		}
	}
}

void	put_da_brackets(char **e)
{
	char	*value1;
	char	*value;
	int		len;

	len = char_count(*e);
	value1 = (ft_strchr(*e, ('=')));
	value = value1 + 1;
	write(1, *e, len);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('\"', 1);
	ft_putstr_fd(value, 1);
	ft_putchar_fd('\"', 1);
}
