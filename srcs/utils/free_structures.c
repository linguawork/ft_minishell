/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:52:36 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/09 12:52:36 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	job_free(t_job **structure)
{
	if (structure && *structure)
	{
		free(*structure);
		*structure = NULL;
	}
}

void	pipe_free(t_pipe **structure)
{
	if (structure && *structure)
	{
		free(*structure);
		*structure = NULL;
	}
}

void	redir_free(t_redir **structure)
{
	if (structure && *structure)
	{
		free(*structure);
		*structure = NULL;
	}
}

void	main_free(t_main **structure)
{
	if (structure && *structure)
	{
		free(*structure);
		*structure = NULL;
	}
}
