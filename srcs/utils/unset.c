/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:09:05 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 17:42:46 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string_to_eraze2(t_main *main, char **args, char **en)
{
	int	i;

	i = 0;
	while (en[i] != NULL)
	{
		if (!(ft_strchr(*args, '=')) && !(ft_strchr(en[i], '=')))
		{
			if (ft_strcmp(*args, en[i]) == 0)
			{
				free(en[i]);
				check_string_two_cycles(en, i);
				copy_env2(main, en);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_string_to_eraze(t_main *main, char **args, char **en)
{
	char	*name;
	int		len;
	int		i;

	i = 0;
	while (en[i] != NULL)
	{
		if (!(ft_strchr(*args, '=')) && (ft_strchr(en[i], '=')))
		{
			len = char_count(en[i]);
			name = ft_substr(en[i], 0, len);
			if (ft_strcmp(*args, name) != 0)
				free(name);
			if (ft_strcmp(*args, name) == 0)
			{
				free(en[i]);
				check_string_two_cycles(en, i);
				copy_env2(main, en);
				free (name);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	checker2(t_main *main, char **a, char **e)
{
	if ((check_string_to_eraze(main, a, e) == 1) || \
	(check_string_to_eraze2(main, a, e) == 1))
		return (1);
	else
		return (0);
}

int	check_args_unset(t_main *main, char **a)
{
	char	*invalid_char_str;
	int		i;

	invalid_char_str = UNSET_INVALID_CHAR_STR;
	if (ft_strchr (*a, '_'))
		return (0);
	i = 0;
	while (invalid_char_str[i])
	{
		if (!ft_isalpha(*a[0]) || (ft_strchr(*a, invalid_char_str[i])))
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(main->job->pipe->redir->command, 1);
			ft_putstr_fd(": `", 1);
			ft_putstr_fd(*a, 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset(t_main *main)
{
	char	*command;
	char	**args;
	char	**envir;
	int		flag;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	while (command && args && *args != NULL)
	{
		flag = check_args_unset(main, args);
		if (flag != 1)
		{
			envir = env_recorder(main);
			checker2 (main, args, envir);
			free(envir);
		}
		args++;
	}
	return (0);
}
