/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processor2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:09:32 by areggie           #+#    #+#             */
/*   Updated: 2021/07/27 18:42:22 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return(i);
}

int exists(const char *command)
{
    FILE *file;
    if ((file = fopen(command, "r+")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int	count_redirects(t_main *main)
{
	int		i;
	t_redir	*redir;

	i = 1;
	redir = main->job->pipe->redir;
	while (redir->redir_next != NULL)
	{
		redir = redir->redir_next;
		i++;
	}
	return (i);
}
