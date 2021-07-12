/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/07/12 14:47:51 by meunostu         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <term.h>
//#include <signal.h>
//#include <termios.h>

# define NO_VALID_SYMBOLS ""
# define VALID_SYMBOLS_FILES "._"
# define NO_VALID_ENV_VAR "\"'/.,-/= $\'<>\\`\0?*"
# define NO_VALID_COMMAND_SYMBOLS ":\"'"
# define NO_VALID_DOBLE_QUOTE "!"
# define SPEC_SYMBOLS "$'\" \n><|"
# define SPECIFICATORS "&;|><!()"

/*
** Errors
*/
# define ERROR_MALLOC "error malloc"
# define ERROR_COMMAND "command not found"

typedef enum	e_options
{
	OUTPUT,
	APPEND_OUTPUT,
	INPUT,
	INPUT_MULTILINE,
	ERROR,
}				t_options;

typedef struct s_parser
{
	char			*string;
	char			*line;
	int 			cur_c;
	char			*variable;
	char			*variable_value;
	int 			pars_command;
	int 			pipe_exist;
	int 			pars_var;
	int 			pars_args;
	int 			args_len;
	int 			double_quote;
	int 			quote;
	int 			index;
}					t_parser;

typedef struct s_redir
{
	char			*command;
	char			**args;
	char			*redir_file;
	t_options		redir_type;
	struct s_redir	*redir_next;
	int				error;
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
	int             num_commands;
	int             num_pipes;
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
void	init_struct(t_main *main);
void	end_session(t_main *main);

/*
** PARSER
*/
void	parser(t_main *main, char *string);
void	pars_quote(t_parser *parser, t_main *main);
void	write_pars_line(t_main *main, t_job *job, t_parser *parser);

/*
** PARSER INIT
*/
void	init_parser(t_parser *parser);
void	init_struct_job_next(t_job *job);
void	init_struct_pipe_next(t_job *job, int job_next);
void	init_struct_redir_next(t_redir *redir);

/*
** PARSER PIPE
*/
t_job	*get_next_pipe_addr(t_job *job, t_main *main, t_parser *parser);
t_pipe	*get_current_pipe(t_job *job);
t_redir *get_curren_redir(t_redir *redir);
void	pars_quote(t_parser *parser, t_main *main);

/*
** PARSER REDIRECT
*/
void	redirect(t_main *main, t_job *job, t_parser *parser);

/*
** PARSER WRITE TO MAIN
*/
void	write_pars_line(t_main *main, t_job *job, t_parser *parser);
void	check_symbols_and_append_line(t_main *main, t_job *job, t_parser
*parser);

/*
** PARSER ENV
*/
void	pars_env_and_append_line(t_parser *parser, t_main *main);
char 	*pars_env_variable(t_parser *parser);

/*
** UTILS
*/
void	free_data_redir(t_redir * redir);
void	all_mem_free(t_main *main);
void	exit_with_error(t_main *main, char *massage);
char 	**ft_arrdup(char **src, int len);

/*
** UTILS PARSER
*/
int		add_char(char **str, int c);
int		get_next_char(t_parser *parser, int *c);
void	set_error_and_free_pipe(t_job *job, int n);
void	print_error_syntax_message(char *string, int len);

/*
** FREE_STRUCTURES
*/
void	job_free(t_job **structure);
void	pipe_free(t_pipe **structure);
void	redir_free(t_redir **structure);
void	main_free(t_main **structure);

/*
** TESTS
*/
void	tests(void);

/*
** EXECUTION BUILTINS
*/
int     pwd(t_main *main);
void    process_builtins_and_divide_externals(t_main *main);
void	copy_env(t_main *main, char **env);
void	copy_env2(t_main *main, char **env);// с функцией free 2 раза
void	copy_env3(t_main *main, char **env);// с функцией free 1 раз
int		check_string_to_eraze(t_main *main, char **args, char **en);
int		check_string_to_eraze2(t_main *main, char **args, char **en);
int		char_count(const char *str);
int		process_exe(t_main *main);
int		how_many_lines(char **a);
char**	cmd_args_to_argv_recorder(t_main *main);
void	*arrays_free(char **s);
char    *ft_getenv(t_main *main, char *name);
int     cd(t_main *main);
char**  cmd_args_to_argv_recorder2(t_main *main);
int     exists(const char *command);
int     check_dir (char *cmd);
int     execute_pipes (t_main *main);
char**  cmd_args_to_argv_recorder_p(t_job *job);
int     echo(t_main *main);
int     exit_command(t_main *main);
int     env(t_main *main);
int     export(t_main *main);
char**  env_recorder(t_main *main);
char**  env_recorder2(char **envir, int len);
int     checker (t_main *main, char **a, char **e);
int     unset(t_main *main);
void    process_folder_or_ready_exe(t_main *main);
//char**  cmd_args_to_argv_recorder_p(t_main *main);
void    process_builtins_in_pipes(t_main *main, char **cmd);
int     process_exe_in_pipes(t_main *main, char **cmd);
void    process_folder_in_pipes(t_main *main, char **cmd);
void    redir_one_right(t_main *main);
void    redir_two_right(t_main *main);
int     count_redirects(t_main *main);
int     redir_one_left(t_main *main);
void    check_valid_redir(t_main *main);


void	rl_replace_line();
#endif //MINISHELL_H
