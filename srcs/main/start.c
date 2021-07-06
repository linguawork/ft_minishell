/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/05 18:10:29 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_main *main, char **env)
{
	int i;
	int len;

	i = -1;
	len = how_many_lines(env);
	main->my_env = ft_calloc(len + 1, sizeof(char *));
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	while (++i < len)
	{
		main->my_env[i] = ft_strdup(env[i]);
		if (!main->my_env[i])
			exit_with_error(main, ERROR_MALLOC);
	}
    main->my_env[i] = NULL;
}

void	init_struct(t_main *main)
{
	t_job	*job;
	t_pipe	*pipe;
	t_redir	*redir;

	job = (t_job *)malloc(sizeof(t_job));
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	redir = (t_redir *)malloc(sizeof(t_redir));

	main->sub = 0;// for args sub in export
	main->flag2 = 0;// for check_valid_args
	main->exit = 0;
	job->pipe_next = NULL;
	job->job_next = NULL;
	job->num_commands = 0;
	job->num_pipes = 0;
	redir->redir_next = NULL;
	redir->redir_file = NULL;
	redir->redir_type = -1;
	main->job = job;
	main->job->pipe = pipe;
	main->job->pipe->redir = redir;
	main->job->pipe->redir->command = NULL;
	main->job->pipe->redir->args = NULL;
}

void	end_session(t_main *main)
{
	all_mem_free(main);
	main->job->pipe->redir->error = 0;
	main->job->num_commands = 0;
	main->job->num_pipes = 0;
	main->job->pipe_next = NULL;
	main->job->job_next = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_main	main;
	char	*string;

	init_struct(&main);
	copy_env(&main, env);
//	tests();
	while (1)
	{
		string = readline("minishell> ");
		if (*string)
			add_history(string);
		parser(&main, string);
		mem_free(&string);
		if (main.job->pipe->redir->command && !main.job->pipe->redir->error && main.job->num_pipes == 0)
			process_builtins_and_divide_externals(&main);
		if (main.job->num_pipes != 0)
            execute_pipes(&main);
		end_session(&main);
	}
	av[ac] = env[ac];
	return (0);
}
