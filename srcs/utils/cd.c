/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:28 by areggie           #+#    #+#             */
/*   Updated: 2021/07/22 19:05:55 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_main *main, char *name)
{
	char	**env;
	int		len;
	int		i;
	char	*name_or_value;

	env = main->my_env;
	i = 0;
	while (env[i++] != NULL)
	{
		if (ft_strchr(env[i], '='))
		{
			len = char_count(env[i]);
			name_or_value = ft_substr(env[i], 0, len);
			if (ft_strcmp(name_or_value, name) != 0)
				free(name_or_value);
			if (ft_strcmp(name_or_value, name) == 0)
			{
				free(name_or_value);
				name_or_value = ft_strchr(env[i], '=') + 1;
				return (name_or_value);
			}
		}
	}
	return (0);
}

int	cd_mistakes(t_main *main, char *p)
{
	char	*error_mes;

	error_mes = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(main->job->pipe->redir->command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(p, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(error_mes, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	cd_ifpart1(t_main *main, char *p)
{
	if (p == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		main->exit = 1;
	}
	else
		chdir(p);
}

int	cd(t_main *main)
{
	char	*p;
	char	buffer[1024];

	p = ft_getenv(main, "HOME");
	if (main->job->pipe->redir->command && !main->job->pipe->redir->args)
		cd_ifpart1(main, p);
	if (main->job->pipe->redir->command && main->job->pipe->redir->args)
	{
		p = *main->job->pipe->redir->args;
		if (chdir(p) < 0)
		{
			main->exit = 1;
			return (cd_mistakes(main, p));
		}
		else
		{
			if (getcwd(buffer, 1024) == NULL)
			{
				main->exit = 1;
				return (cd_mistakes(main, p));
			}
		}
	}
	return (0);
}
