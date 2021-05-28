/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/28 12:04:16 by meunostu         ###   ########.fr       */
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

	redir->redir_to = 0;
	main->job = job;
	main->job->pipe = pipe;
	main->job->pipe->redir = redir;
	main->exit = 0;
	main->job->pipe->redir->flags = ft_strdup(""); // раскомментить если нет флага и будут аргументы
	main->job->pipe->redir->args = NULL; // раскомментить если нет флага и будут аргументы
    // main->job->pipe->redir->flags = ft_strdup("-n"); // раскомментить если будет флаг -n и нет аргументов пока так работает на 23 мая
	//если закомментить то -n идет как аргумент и распечатывается как аргумент
	copy_env(main, env);
}

int	main(int ac, char **av, char **env)
{
	t_main	main;

	init_shell(&main, env);
//	tests();
	while (!main.exit)// в условии работает а в цикле перестает работать echo, pwd странно работает
	{
		write(1, "minishell: ", 11);
		parser(&main);
        process_builtins_and_divide_externals(&main);
		if (main.exit == 1)
			exit(0);
	}
	av[ac] = env[ac];
	return (0);
}
