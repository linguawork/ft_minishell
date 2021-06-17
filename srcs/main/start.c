/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/17 08:47:47 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_main *main, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	main->my_env = (char **)malloc(sizeof(char *) * (i));// добавление 1 не помогло
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	main->my_env[i] = NULL;
	while (--i >= 0)
	{
		main->my_env[i] = ft_strdup(env[i]);
		if (!main->my_env[i])
			exit_with_error(main, ERROR_MALLOC);
	}
}

static void	init_shell(t_main *main, char **env)
{
	t_job	*job;
	t_pipe	*pipe;
	t_redir	*redir;

	job = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));

	main->exit = 0;
	redir->redir_to = 0;
	main->job = job;
	main->job->pipe = pipe;
	main->job->pipe->redir = redir;
	main->job->pipe->redir->command = NULL;
	main->job->pipe->redir->flags = NULL;
	main->job->pipe->redir->args = NULL;
	copy_env(main, env);
}

void	end_session(t_main *main)
{
	mem_free(&main->job->pipe->redir->command);
	arr_free(&main->job->pipe->redir->args);
}

int	main(int ac, char **av, char **env)
{
	t_main	main;

	init_shell(&main, env);
//	tests();
	while (1)
	{
		write(1, "minishell: ", 11);
		parser(&main);
        process_builtins_and_divide_externals(&main);
		end_session(&main);
	}
	av[ac] = env[ac];
	return (0);
}
