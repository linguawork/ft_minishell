/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/10 22:24:50 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <string.h>
# include <errno.h>

# define NO_VALID_ENV_VAR ".,-'?/$"
# define NO_VALID_COMMAND_SIMBOLS ":\"'$"

/*
** Errors
*/
# define ERROR_MALLOC "malloc"
# define ERROR_COMMAND "command not found"

typedef struct s_parser
{
	char			*line;
	int 			cur_c;
	int 			pars_command;
	int 			pars_var;
	int 			pars_args;
	int 			pars_flags;
}					t_parser;

typedef struct s_redir
{
	char			*command;
	char			*flags;
	char			**args;
	int 			redir_to;
	char			*error;
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
	struct t_job	*job_next;
}					t_job;

typedef struct s_main
{
	t_job			*job;
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
void	exit_with_error(t_main *main, char *massage);
int		add_char(char **str, int c);
int		get_next_char(t_parser *parser, int *c);

/*
** TESTS
*/
void	tests(void);
char	*pars_env_variables(t_main *main, t_parser *parser);

/*
** EXECUTION BUILTINS
*/
int     pwd(t_main *main);
int     ft_strcmp(const char *s1, const char *s2);
void    process_externals(t_main *main);
void    process_builtins_and_divide_externals(t_main *main);
void	copy_env(t_main *main, char **env);
void	copy_env2(t_main *main, char **env);// с функцией free
void	copy_env3(t_main *main, char **env);// с функцией free отключил
void	overwrite_args(t_main *main, char **a);
int		check_string_to_eraze(t_main *main, char **args, char **en);
int		check_string_to_eraze2(t_main *main, char **args, char **en);
int		char_count(const char *str);
void	*ft_new_memory_alloc(void *p, size_t length);
int		process_exe(t_main *main);
int		how_many_lines(char **a);
char	*ft_itoa(int n);


#endif //MINISHELL_H
