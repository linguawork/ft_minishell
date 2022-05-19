/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:08:47 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 21:34:55 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_code(t_main *main)
{
	if (WIFEXITED(main->exit))
		main->exit = (WEXITSTATUS(main->exit));
	else if (WIFSIGNALED(main->exit))
	{
		main->exit = WTERMSIG(main->exit);
		if (main->exit == SIGINT)
			printf("^C\n");
		else if (main->exit == SIGQUIT)
			printf("^Quit %d\n", main->exit);
		main->exit = main->exit + 128;
	}
}

int	path_mistakes(t_main *main)
{
	char	*error_mes;

	error_mes = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(main->job->pipe->redir->command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_mes, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	command_not_found(t_main *main, char **command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*command, 2);
	ft_putstr_fd(": Command not found\n", 2);
	main->exit = 127;
}

void	command_not_found_in_exe(t_main *main, char **command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*command, 2);
	ft_putstr_fd(": Command not found\n", 2);
	main->exit = 127;
}
