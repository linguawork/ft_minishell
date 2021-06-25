/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/24 19:08:58 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include <dirent.h>

# define NO_VALID_SYMBOLS ""
# define NO_VALID_ENV_VAR "\"'/.,-/= $\'<>\\`\0?*"
# define NO_VALID_COMMAND_SYMBOLS ":\"'"
# define NO_VALID_DOBLE_QUOTE "!"

/*
** Errors
*/
# define ERROR_MALLOC "error malloc"
# define ERROR_COMMAND "command not found"

typedef struct s_parser
{
	char			*line;
	int 			cur_c;
	char			*variable;
	char			*variable_value;
	int 			pars_command;
	int 			pipe_exist;
	int 			pars_var;
	int 			pars_args;
	int 			args_len;
}					t_parser;

typedef struct s_redir
{
	char			*command;
	char			**args;
	char			*error;
	char			*redir_file;
	int				redir_type;
	struct s_redir	*redir_next;
}					t_redir;

typedef struct s_pipe
{
	t_redir			*redir;
}					t_pipe;

typedef struct s_job
{
	t_pipe			*pipe;
	t_pipe			*pipe_next;
	struct s_job	*job_next;
}					t_job;

typedef struct s_main
{
	t_job			*job;
	char			**my_env;
	int				exit;
	int             sub;
	int             flag2;
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
void	arr_free(char **str);

/*
** TESTS
*/
void	tests(void);
char 	*pars_env_variable(t_parser *parser);

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
char    **ft_new_memory_alloc(void *p, size_t length);
int		process_exe(t_main *main);
int		how_many_lines(char **a);
char**	cmd_args_to_argv_recorder(t_main *main);
void	*arrays_free(char **s);
char    *ft_getenv(t_main *main, char *name);
int     cd(t_main *main);


#endif //MINISHELL_H
