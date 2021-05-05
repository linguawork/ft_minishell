/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/05 08:52:50 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

# define ERROR_MALLOC "malloc"

typedef struct s_data
{
	char			*command;
	char			*flags;
	char			*args;
	struct s_data	*next;
}					t_data;

typedef struct s_mini
{
	t_data		*data;
	char		**my_env;
	int			exit;
}				t_mini;


/*
** Functoins
** MINISHELL
*/

/*
** PARSING
*/
void	parser(t_mini *mini);


/*
** UTILS
*/
void	exit_game_with_error(t_mini *mini, char *massage);

#endif //MINISHELL_H
