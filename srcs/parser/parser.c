/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:40:14 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/05 09:56:42 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_mini *mini)
{
	char	*line;

	get_next_line(0, &line);
	printf("%s\n", line);
	if (ft_strnstr(line, "exit", 4))
		mini->exit = 1;
	mem_free(&line);
}
