/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/11 09:22:39 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# define NO_VALID_ENV_VAR ".,-'?/$"

/*
** Errors
*/
# define ERROR_MALLOC "malloc"


typedef struct s_redir
{
	char			*command;
	char			*flags;
	char			**args;
	int 			redir_to;
	struct t_job	*job_next;
}					t_redir;

typedef struct s_pipe
{
	t_redir			*redir;
	t_redir			*redir_next;
}					t_pipe;

typedef struct s_job
{
	t_pipe			*pipe;
	t_pipe			*pipe_next;
}					t_job;

typedef struct s_parser
{
	char			*line;
}					t_parser;

typedef struct s_main
{
	t_job			*job;
	t_job			*next_job;
	char			**my_env;
	int				exit;
}					t_main;

/*
** MAIN
*/

/*
** PARSING
*/
void	parser(t_main *main);


/*
** UTILS
*/
void	exit_game_with_error(t_main *main, char *massage);

/*
** TESTS
*/
void	tests(void);
char	*pars_env_variables(t_main *main, char **line);
void	test_pars_env_variables(t_main *main);

#endif //MINISHELL_H
