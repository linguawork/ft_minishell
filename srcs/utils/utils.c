/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/05 09:52:34 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	all_mem_free(t_mini *mini)
{
	while (mini->my_env)
		mem_free(mini->my_env++);
}

void	exit_game_with_error(t_mini *mini, char *massage)
{
	all_mem_free(mini);
	printf("Error: %s\n", massage);
	exit(-1);
}
