/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 05:36:17 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/03 16:13:19 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // Delete

typedef struct s_data
{
	char			*command;
	char			*flags;
	char			*args;
	struct s_mini	*next;
}					t_data;

typedef struct s_mini
{
	t_data		*data;
}				t_mini;

/*
** MINISHELL
*/

/*
** PARSING
*/


/*
** UTILS
*/

#endif //MINISHELL_H
