/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:04 by areggie           #+#    #+#             */
/*   Updated: 2021/07/25 18:14:36 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(t_main *main, char **a)
{
	char	*invalid_char_str;
	int		i;

	invalid_char_str = INVALID_CHAR_STR;
	if (ft_strchr (*a, '_'))
		return ;
	i = 0;
	while (invalid_char_str[i])
	{
		if (!ft_isalpha(*a[0]) || (ft_strchr(*a, invalid_char_str[i])))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(main->job->pipe->redir->command, 2);
			ft_putstr_fd(": `", 2);
			ft_putstr_fd(*a, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			main->flag2 = 1;
			break ;
		}
		i++;
	}
}

int	export_if_no_args(char **envir, int len, int i)
{
	double_for_sort_algo(envir, len);
	while (envir[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		if (!(ft_strchr(envir[i], '=')))
		{
			ft_putstr_fd(envir[i], 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			put_da_brackets(&envir[i]);
			ft_putchar_fd('\n', 1);
		}
		if (envir[i] == NULL)
			return (1);
		i++;
	}
	free(envir);
	return (0);
}

void	export_with_args_ifs(t_main *main, char **envir, char **args, int i)
{
	char	**e;
	int		flag;
	int		len;

	flag = checker(main, &args[i], envir);
	if ((flag != 1) && (main->flag2 != 1))
	{
		len = how_many_lines(envir);
		e = env_recorder2(envir, len);
		e[len] = ft_strdup(args[i]);
		e[len + 1] = NULL;
		len++;
		copy_env2(main, e);
		free(e);
	}
	if (flag == 1 && main->sub == 1)
	{
		copy_env3(main, envir);
		main->sub = 0;
	}
}

void	export_with_args(t_main *main, char **envir, char **args)
{	
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (args[i] != NULL)
	{
		envir = env_recorder(main);
		check_args(main, &args[i]);
		export_with_args_ifs(main, envir, args, i);
		free(envir);
		flag = 0;
		main->flag2 = 0;
		i++;
	}
}

int	export(t_main *main)
{
	char	*command;
	char	**args;
	char	**envir;
	int		len;
	int		i;

	envir = env_recorder(main);
	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	len = how_many_lines(envir);
	i = 0;
	if (command && !args)
		export_if_no_args(envir, len, i);
	else
	{
		export_with_args(main, envir, args);
		free(envir);
	}
	return (0);
}
