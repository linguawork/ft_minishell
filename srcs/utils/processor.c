/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:57 by areggie           #+#    #+#             */
/*   Updated: 2021/07/26 21:36:32 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_buildins2(t_main *main)
{
	if (ft_strncmp(main->job->pipe->redir->command, "export", 6) == 0)
	{
		export(main);
		return (1);
	}
	else if (ft_strncmp(main->job->pipe->redir->command, "unset", 5) == 0)
	{
		unset(main);
		return (1);
	}
	else if (ft_strncmp(main->job->pipe->redir->command, "env", 3) == 0)
	{
		env(main);
		return (1);
	}
	else if (ft_strncmp(main->job->pipe->redir->command, "exit", 4) == 0)
	{
		exit_command(main);
		return (1);
	}
	return (0);
}

int	process_buildins(t_main *main)
{
	char	*command;
	int		flag;

	command = main->job->pipe->redir->command;
	if (ft_strncmp(command, "echo", 4) == 0)
	{
		echo(main);
		return (1);
	}
	else if (ft_strncmp(command, "cd", 2) == 0)
	{
		cd(main);
		return (1);
	}
	else if (ft_strncmp(command, "pwd", 3) == 0)
	{
		pwd(main);
		return (1);
	}
	else
	{
		flag = process_buildins2(main);
		return (flag);
	}
}

void	process_builtins_and_divide_externals(t_main *main)
{
	int	flag;

	flag = process_buildins(main);
	process_folder_or_ready_exe(main);
	if (main->flag2 != 1 && flag == 0)
		process_exe(main);
	main->flag2 = 0;
}
