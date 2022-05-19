/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in_pipes5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:14:41 by areggie           #+#    #+#             */
/*   Updated: 2021/07/28 19:15:13 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	noforking_in_rp(t_main *main, char **binar, int i, char *command)
{
	char	*exe;
	char	*exe2;
	char	**argv;

	argv = cmd_args_to_argv_recorder(main);
	exe = ft_strjoin(binar[i], "/");
	exe2 = ft_strjoin(exe, command);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(exe2, argv, NULL);
	exec_mistakes(main);
	exit(126);
	arrays_free(binar);
	free(exe);
	free(exe2);
}

void	no_forking2_in_rp(t_main *main, char **binar, int i, char *command)
{
	DIR	*folder;

	folder = opendir(binar[i]);
	noforking_in_rp(main, binar, i, command);
	closedir(folder);
	signal(SIGINT, &ctrl_c);
}
