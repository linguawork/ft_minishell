/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:37 by areggie           #+#    #+#             */
/*   Updated: 2021/07/22 19:28:31 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_ifpart1(t_main *main)
{
	char	*command;
	char	**args;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	while (*args != NULL && (ft_strcmp(*args, "-n") == 0))
		args++;
	if (*args == NULL)
		return (0);
	write(1, *args, ft_strlen(*args));
	while (*++args != NULL)
	{
		ft_putchar_fd(' ', 1);
		write(1, *args, ft_strlen(*args));
	}
	return (0);
}

void	echo_ifpart2(t_main *main)
{
	char	**args;

	args = main->job->pipe->redir->args;
	while (*args != NULL)
	{
		ft_putstr_fd(*args, 1);
		ft_putchar_fd(' ', 1);
		args++;
	}
	ft_putchar_fd('\n', 1);
}

int	echo(t_main *main)
{
	char	*command;
	char	**args;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	main->exit = 0;
	if (command)
	{
		if (!args)
			ft_putchar_fd('\n', 1);
		if (args)
		{
			if (ft_strcmp(*args, "-n") == 0)
				echo_ifpart1(main);
			else
				echo_ifpart2(main);
		}
	}
	return (0);
}
