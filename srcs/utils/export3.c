/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:10 by areggie           #+#    #+#             */
/*   Updated: 2021/07/25 20:05:38 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	elseif1(t_main *main, char **args, char **en)
{
	char	*a_name;
	int		len;

	len = char_count(*args);
	a_name = ft_substr(*args, 0, len);
	if (ft_strcmp(a_name, *en) != 0)
		free(a_name);
	if (ft_strcmp(a_name, *en) == 0)
	{
		free(*en);
		*en =ft_strdup(*args);
		free(a_name);
		main->sub = 1;
		return (1);
	}
	return (0);
}

int	elseif2(t_main *main, char **args, char **en)
{
	char	*a_name;
	char	*e_name;
	int		len2;
	int		len;

	len = char_count(*args);
	len2 = char_count(*en);
	a_name = ft_substr(*args, 0, len);
	e_name = ft_substr(*en, 0, len2);
	if (ft_strcmp(a_name, e_name) != 0)
	{
		free(e_name);
		free(a_name);
	}
	if (ft_strcmp(a_name, e_name) == 0)
	{
		free(*en);
		*en = ft_strdup(*args);
		free(a_name);
		free(e_name);
		main->sub = 1;
		return (1);
	}
	return (0);
}

int	elseif3(char **args, char **en)
{
	char	*e_name;
	int		len;

	len = char_count(*en);
	e_name = ft_substr(*en, 0, len);
	if (strcmp(*args, e_name) != 0)
		free(e_name);
	if (strcmp(*args, e_name) == 0)
	{
		free(e_name);
		return (1);
	}
	return (0);
}

int	check_doubles(t_main *main, char **args, char **en)
{
	int	flag;

	while (*en != NULL)
	{
		if (ft_strcmp(*args, *en) == 0)
			return (1);
		else if ((ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
			flag = elseif1(main, args, en);
		else if ((ft_strchr(*args, '=')) && (ft_strchr(*en, '=')))
			flag = elseif2(main, args, en);
		else if (!(ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
		{
			if (ft_strcmp(*args, *en) == 0)
				return (1);
		}
		else if (!(ft_strchr(*args, '=')) && (ft_strchr(*en, '=')))
			flag = elseif3(args, en);
		if (flag == 1)
			return (1);
		en++;
	}
	return (0);
}

int	checker (t_main *main, char **a, char **e)
{
	if (check_doubles(main, a, e) == 1)
		return (1);
	else
		return (0);
}
