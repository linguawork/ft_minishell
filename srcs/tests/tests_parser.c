/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:35:39 by meunostu          #+#    #+#             */
/*   Updated: 2021/05/11 12:17:35 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_pars_env_variables(t_main *main)
{
	char *str;

	str = "$PATH,";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$PWD";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$321";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$fdsgbkldmbklfdsmklfmd";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$?";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$w$e'";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));

	str = "$lkjlkjllkdfs$q$w$e$r";
	printf("|%s| - $%s\n", str, pars_env_variables(main, &str));
}

void tests(void)
{
	t_main	main;

	test_pars_env_variables(&main);
}

