/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:01:15 by areggie           #+#    #+#             */
/*   Updated: 2021/07/22 18:01:18 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_redirects(t_main *main)
{
    if (main->job->pipe->redir->redir_type == OUTPUT)
        redir_one_right(main);
    if (main->job->pipe->redir->redir_type == APPEND_OUTPUT)
        redir_two_right(main);
    if (main->job->pipe->redir->redir_type == INPUT)
        redir_one_left(main);
    if (main->job->pipe->redir->redir_type == INPUT_MULTILINE)
        redir_two_left(main);
}

