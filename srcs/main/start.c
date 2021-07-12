/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/12 17:17:16 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_main *main, char **env)
{
	int		i;
	int		len;

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

void	ctrl_slash(int sig)
{
	printf("CTRL + / %d  \n", sig);
	sig = 1;
}

void	ctrl_d(int sig)
{
	rl_replace_line(rl_line_buffer, 0);
	rl_redisplay();
	exit(sig);
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_main			main;
	char			*string;
	struct termios	term;

	init_struct(&main);
	copy_env(&main, env);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	while (1)
	{
		string = readline("minishell> ");
		if (!string)
			ctrl_d(131);
		if (*string)
			add_history(string);
		parser(&main, string);
		mem_free(&string);
		if (main.job->pipe->redir->command && !main.job->pipe->redir->error
			&& main.job->num_pipes == 0)
			process_builtins_and_divide_externals(&main);
		if (main.job->num_pipes != 0)
			execute_pipes(&main);
		end_session(&main);
	}
	av[ac] = env[ac];
	return (0);
}
