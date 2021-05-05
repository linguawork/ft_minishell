/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:41 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/05 10:08:12 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_mini *mini, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	mini->my_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!mini->my_env)
	i++;
	while (--i)
	{
		mini->my_env[i] = ft_strdup(env[i]);
		if (!mini->my_env[i])
			exit_game_with_error(mini, ERROR_MALLOC);
	}
}
static void	init_shell(t_mini *mini, char **env)
{
	t_data	data;

	mini->data = &data;
	mini->exit = 0;
	copy_env(mini, env);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	init_shell(&mini, env);
	while (!mini.exit)
	{
		printf("minishell: ");
		parser(&mini);
		if (mini.exit == 1)
			exit(0);
	}
	av[ac] = env[ac];
	return (0);
}
