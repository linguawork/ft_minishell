/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/07 13:05:57 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_main *main, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	main->my_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!main->my_env)
	i++;
	while (--i)
	{
		main->my_env[i] = ft_strdup(env[i]);
		if (!main->my_env[i])
			exit_game_with_error(main, ERROR_MALLOC);
	}
}
static void	init_shell(t_main *main, char **env)
{
	t_job	job;
	t_pipe	pipe;
	t_redir	redir;

	redir.redir_to = 0;
	main->job = &job;
	main->job->pipe = &pipe;
	main->job->pipe->redir = &redir;
	main->exit = 0;
	copy_env(main, env);
}

int	main(int ac, char **av, char **env)
{
	t_main	main;

	init_shell(&main, env);
	while (!main.exit)
	{
		printf("minishell: ");
		parser(&main);
		if (main.exit == 1)
			exit(0);
	}
	av[ac] = env[ac];
	return (0);
}
