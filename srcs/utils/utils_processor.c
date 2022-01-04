/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:09:25 by areggie           #+#    #+#             */
/*   Updated: 2022/01/04 21:01:59 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*arrays_free(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
	return (NULL);
}

int	char_count(const char *str)
{
	int	i;

	i = 0;
	if (!(ft_strchr(str, '=')))
		return (0);
	else
	{
		while (str[i] != '=')
		{
			i++;
		}
	}
	return (i);
}

void	copy_env3(t_main *main, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = how_many_lines(env);
	free(main->my_env);
	main->my_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	while (++i < len)
	{
		main->my_env[i] = ft_strdup(env[i]);
		free(env[i]);
		if (!main->my_env[i])
			exit_with_error(main, ERROR_MALLOC);
	}
	main->my_env[i] = NULL;
}

void	copy_env2(t_main *main, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = how_many_lines(env);
	free(main->my_env);
	main->my_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	while (++i < len)
	{
		main->my_env[i] = ft_strdup(env[i]);
		free(env[i]);
		if (!main->my_env[i])
			exit_with_error(main, ERROR_MALLOC);
	}
	main->my_env[i] = NULL;
}

int	exec_mistakes(t_main *main)
{
	char	*error_mes;

	error_mes = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(main->job->pipe->redir->command, 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(error_mes, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
