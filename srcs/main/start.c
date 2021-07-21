/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/17 22:14:07 by meunostu         ###   ########.fr       */
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
//	printf("\033[Aminishell: exit\n");
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

char *get_value(char *str, int *index)
{
	int	i;
	i = 0;
	while (str && str[i] != '=')
		i++;
	*index = ++i;
	return (str + i);
}

void	inc_SHLVL(t_main *main)
{
	int		i;
	int		len;
	char 	**env;
	int		nbr;
	char 	*str;

	i = -1;
	env = main->my_env;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL", 5))
		{
			nbr = ft_atoi(get_value(env[i], &len));
			str = ft_substr(env[i], 0, len);
			free(env[i]);
			env[i] = ft_strjoin(str, ft_itoa(++nbr));
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_main			main;
	char			*string;
	struct termios	term;

	init_struct(&main);
	copy_env(&main, env);
	inc_SHLVL(&main);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	while (1)
	{
	    printf("\e[s");
		string = readline("minishell: ");
		if (!string) {
            printf("\e[u\e[Aminishell: exit\n");
            ctrl_d(131);
        }
		else if (*string)
			add_history(string);

		parser(&main, string);
		mem_free(&string);
        if (main.job->pipe->redir->command && !main.job->pipe->redir->error && main.job->num_pipes == 0 &&
        main.job->num_redirects == 0)
            process_builtins_and_divide_externals(&main);
        if (main.job->num_pipes != 0 && main.job->num_redirects == 0)
            execute_pipes(&main);
        if (main.job->num_pipes == 0 && main.job->num_redirects != 0)
            process_redirects(&main);
        if (main.job->num_pipes != 0 && main.job->num_redirects != 0)
            execute_pipes_and_redirs(&main);
		end_session(&main);
	}
	av[ac] = env[ac];
	return (0);
}
