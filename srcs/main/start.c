/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2022/05/19 14:25:25 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_main *main, char **env)
{
	int		i;
	int		j;
	int		len;

	len = how_many_lines(env);
	main->my_env = ft_calloc(len + 1, sizeof(char *));
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (strchr(env[i], '='))
			main->my_env[++j] = ft_strdup(env[i]);
	}
	main->my_env[++j] = NULL;
	inc_SHLVL(main->my_env);
}

void	ctrl_d(int sig)
{
	printf("\e[u\e[Aminishell: exit\n");
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

char	*get_line(void)
{
	char	*string;

	printf("\e[s");
	string = readline("minishell: ");
	if (!string)
		ctrl_d(131);
	else if (*string)
		add_history(string);
	return (string);
}

int	main(int ac, char **av, char **env)
{
	t_main			main;
	struct termios	term;
	char			*string;

	init_minishell(&main);
	copy_env(&main, env);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	while (1)
	{
		string = get_line();
		parser(&main, string);
		mem_free(&string);
		processor(&main);
		end_session(&main);
	}
	av[ac] = env[ac];
	return (0);
}
