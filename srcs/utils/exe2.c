/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 22:14:44 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 23:36:50 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_cmd_from_absolute_path(t_main *main)
{
	char	*cmd;
	char	**parts;
	int		len;

	parts = ft_split(main->job->pipe->redir->command, '/');
	len = how_many_lines(parts);
	cmd = ft_strdup(parts[len - 1]);
	arrays_free(parts);
	return (cmd);
}

char	**cycle(int length, char *cmd, char **e, char **a)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	length = how_many_lines((char **) a);
	e = (char **) malloc(sizeof(char *) * (length + 1 + 1));
	e[0] = cmd;
	while (a[j] != NULL)
	{
		e[i] = a[j];
		j++;
		i++;
	}
	e[i] = NULL;
	return (e);
}

char	**cmd_args_to_argv_recorder2(t_main *main)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;
	int		i;

	e = NULL;
	length = 0;
	cmd = return_cmd_from_absolute_path(main);
	a = main->job->pipe->redir->args;
	i = 1;
	if (a == NULL)
	{
		e = (char **) malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i] = NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return (e);
}

char	**cmd_args_to_argv_recorder_p(t_job *job)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;
	int		i;

	e = NULL;
	length = 0;
	cmd = job->pipe->redir->command;
	a = job->pipe->redir->args;
	i = 1;
	if (a == NULL)
	{
		e = (char **)malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i] = NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return (e);
}

char	**cmd_args_to_argv_recorder(t_main *main)
{
	char	**e;
	int		length;
	char	**a;
	char	*cmd;
	int		i;

	e = NULL;
	length = 0;
	cmd = main->job->pipe->redir->command;
	a = main->job->pipe->redir->args;
	i = 1;
	if (a == NULL)
	{
		e = (char **) malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
		e[i] = NULL;
	}
	else
		e = cycle(length, cmd, e, a);
	return (e);
}
