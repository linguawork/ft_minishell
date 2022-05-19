/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:01:15 by areggie           #+#    #+#             */
/*   Updated: 2021/07/29 01:56:37 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	processor(t_main *main)
{
	if (main->job->pipe->redir->command && \
		!main->job->pipe->redir->error && main->job->num_pipes == 0 && \
		main->job->num_redirects == 0)
		process_builtins_and_divide_externals(main);
	if (main->job->num_pipes != 0 && main->job->num_redirects == 0)
		execute_pipes(main);
	if (main->job->num_pipes == 0 && main->job->num_redirects != 0)
		process_redirects(main);
	if (main->job->num_pipes != 0 && main->job->num_redirects != 0)
		execute_pipes_and_redirs(main);
}

void	process_redirects(t_main *main)
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

char	*ft_strchr_equal(const char *s, int c)
{
	size_t		len;
	char		*str;
	int			equal;

	equal = 0;
	if (!s || *s == '\0')
		return (NULL);
	str = (char *)s;
	len = ft_strlen(str) + 1;
	while (len-- && !equal)
	{
		if (*str == '=')
			equal = 1;
		if (*str++ == c)
			return (str - 1);
	}
	return (NULL);
}
