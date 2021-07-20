/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:59 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:00 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	process_valid_args( char **s)
{
    char	*str;
    int		i;

    str = *s;
    i = 0;
    while (str[i] != '\0' )
    {
        if(!ft_isdigit(str[i]) && ft_isascii(str[i]) )
        {
            ft_putstr_fd("exit\nminishell: exit: ", 1);
            ft_putstr_fd(str, 1);
            ft_putstr_fd(": numeric argument required", 1);
            exit((unsigned char) -1);//кастануть чтобы выдать 255
        }
        i++;
    }
}

int exit_command(t_main *main)
{
    char *cmd;
    char ** args;
    int i;

    args = main->job->pipe->redir->args;
    cmd = main->job->pipe->redir->command;
    i = 0;
    if (cmd && !args)
    {
        ft_putstr_fd("exit\n", 1);
        all_mem_free(main);
        exit(EXIT_SUCCESS); // выход с кодом 0
    }
    if (cmd && args[i] && !args[i+1]) // если один аргумент
    {
        if ((*args[0] == '-' && ft_strncmp(*args,"--", 2) != 0 && ft_strncmp(*args,"-+", 2) != 0)||
            (*args[0] == '+' && ft_strncmp(*args,"++", 2) != 0 && ft_strncmp(*args,"+-", 2) != 0))
        {
            ft_putstr_fd("exit\n", 1);
            all_mem_free(main);
            exit((unsigned char) ft_atoi(*args));// кастануть чтобы выдать 255
        }
        else
            process_valid_args(args); // проверка на цифры в аргументе с выводом ошибки //и сохранением в структуру чтобы можно было вызвать через $?
        ft_putstr_fd("exit\n", 1);
        all_mem_free(main);
        exit(ft_atoi(*args));// выход только с цифрами в аргументе (аргумент можно записать в main->exit) они будут выводится через $?
        // если подавать в аргумент цифру >256 то система дает остаток от деления на 256
    }
    if ((cmd && args[i] && args[i+1])) // если много аргументов
    {
        process_valid_args(args);
        ft_putstr_fd("exit\n", 1);
        ft_putstr_fd("minishell: exit: too many arguments\n", 1);
        all_mem_free(main);
        exit(main->exit = 1);
    }
    // sleep(1000);// for test leaks
    return(0);
}