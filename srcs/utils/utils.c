/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:42:03 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/26 09:20:57 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	all_mem_free(t_main *main)
{
	while (main->my_env)
		mem_free(main->my_env++);
}

void	exit_with_error(t_main *main, char *massage)
{
	all_mem_free(main);
	printf("Error: %s\n", massage);
	exit(-1);
}
