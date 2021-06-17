/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meunostu <meunostu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:35:39 by meunostu          #+#    #+#             */
/*   Updated: 2021/06/17 08:47:47 by meunostu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_pars_env_variables(t_main *main, t_parser *parser)
{
	parser->line = "$PATH,";
	(!ft_strnstr(pars_env_variables(main, parser), "$PATH", ft_strlen
	(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$PATH.";
	(!ft_strnstr(pars_env_variables(main, parser), "$PATH", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$PATH-";
	(!ft_strnstr(pars_env_variables(main, parser), "$PATH", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$PATH'";
	(!ft_strnstr(pars_env_variables(main, parser), "$PATH", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$PATH/";
	(!ft_strnstr(pars_env_variables(main, parser), "$PATH", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$PWD";
	(!ft_strnstr(pars_env_variables(main, parser), "$PWD", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$321";
	(!ft_strnstr(pars_env_variables(main, parser), "$3211", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$fdsgbkldmbklfdsmklfmd";
	(!ft_strnstr(pars_env_variables(main, parser), "$fdsgbkldmbklfdsmklfmd", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$lkjlkjllkdfs$q$w$e$r";
	(!ft_strnstr(pars_env_variables(main, parser), "$lkjlkjllkdfs", ft_strlen
			(parser->line))) ? printf("OK ") : printf("KO ");

	parser->line = "$?";
	printf("\nfix|%s| - $%s\n", parser->line, pars_env_variables(main, parser));

	parser->line = "$1";
	printf("\nfix|%s| - $%s\n", parser->line, pars_env_variables(main, parser));

	parser->line = "$12hello";
	printf("\nfix|%s| - $%s\n", parser->line, pars_env_variables(main, parser));

	parser->line = "Hello $2World";
	printf("\nfix|%s| - $%s\n", parser->line, pars_env_variables(main, parser));
}

void tests(void)
{
	t_main		main;
	t_parser	parser;

	printf("Tests\n");
	test_pars_env_variables(&main, &parser);
	printf("End tests\n");
}

