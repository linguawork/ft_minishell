/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:46 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:06:47 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int env(t_main *main)
{
    char *command;
    char **envir;
    int len;
    int i;
    int j;

    command = main->job->pipe->redir->command;
    envir = main->my_env;
    len= how_many_lines(envir);//  Длина у меня уже увеличилась на один в функции realloc
    // printf("export--->%d\n", len); // проверка кол-ва строк в массиве
    if (command)
    {
        j = 0;
        i = 0;
        while(envir[i])
        {
            if (ft_strchr(envir[i], '='))
                printf("%s\n", envir[i]);
            i++;
        }
    }
    return(0);
}