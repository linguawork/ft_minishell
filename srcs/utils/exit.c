/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:59 by areggie           #+#    #+#             */
/*   Updated: 2021/07/25 14:48:57 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_valid_args(char **s)
{
	char	*str;
	int		i;

	str = *s;
	i = 0;
	while (str[i] != '\0' )
	{
		if (!ft_isdigit(str[i]) && ft_isascii(str[i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd(": numeric argument required", 1);
			exit((unsigned char) -1);
		}
		i++;
	}
}

void	if_many_args(t_main *main)
{
	char	*cmd;
	char	**args;

	args = main->job->pipe->redir->args;
	cmd = main->job->pipe->redir->command;
	process_valid_args(args);
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	exit(main->exit = 1);
}

void	if_one_arg(t_main *main)
{
	char	*cmd;
	char	**args;

	args = main->job->pipe->redir->args;
	cmd = main->job->pipe->redir->command;
	if ((*args[0] == '-' && ft_strncmp(*args, "--", 2) != 0 && \
	ft_strncmp(*args, "-+", 2) != 0) || \
	(*args[0] == '+' && ft_strncmp(*args, "++", 2) != 0 && \
	 ft_strncmp(*args, "+-", 2) != 0))
	{
		ft_putstr_fd("exit\n", 1);
		exit((unsigned char) ft_atoi(*args));
	}
	else
		process_valid_args(args);
	ft_putstr_fd("exit\n", 1);
	exit(ft_atoi(*args));
}

int	exit_command(t_main *main)
{
	char	*cmd;
	char	**args;
	int		i;

	args = main->job->pipe->redir->args;
	cmd = main->job->pipe->redir->command;
	i = 0;
	if (cmd && !args)
	{
		ft_putstr_fd("exit\n", 1);
		all_mem_free(main);
		exit(EXIT_SUCCESS);
	}
	if (cmd && args[i] && !args[i + 1])
		if_one_arg(main);
	if ((cmd && args[i] && args[i + 1]))
		if_many_args(main);
	return (0);
}
