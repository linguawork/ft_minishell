/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:09:25 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:09:28 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int how_many_lines(char **a)
{
    int i;
    char **env;

    i = 0;
    env = a;
    while(env[i] != NULL)
    {
        i++;
    }
    return(i);
}

void	*arrays_free(char **s)
{
    int	i;

    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
    return (NULL);
}

int char_count(const char *str)
{
    int i;

    i = 0;
    if (!(ft_strchr(str, '=')))
        return(0);
    else
    {
        while (str[i] != '=')
        {
            i++;
        }
    }
    return(i);
}

void	copy_env3(t_main *main, char **env)
{
    int i;
    int len;

    i = -1;
    len = how_many_lines(env);
    free(main->my_env);
    main->my_env = (char **)malloc(sizeof(char *) * (len + 1));// добавление + 1 довало утечку - убрал и утечек не было но стало сегаться
    // когда подаю аргументы в экспорт После того как снова прибавил +1 сега исчезла (сегу находил с помощью санитайзера)
    if (!main->my_env)
        exit_with_error(main, ERROR_MALLOC);
    while (++i < len)
    {
        main->my_env[i] = ft_strdup(env[i]);
        free(env[i]); // освобождение в цикле чтобы убрать утечки
        if (!main->my_env[i])
            exit_with_error(main, ERROR_MALLOC);
    }
    main->my_env[i] = NULL;
}

void	copy_env2(t_main *main, char **env)
{
    int i;
    int len;

    i = -1;
    len = how_many_lines(env);
    free(main->my_env);
    main->my_env = (char **)malloc(sizeof(char *) * (len + 1));// добавление + 1 довало утечку - убрал и утечек не было но стало сегаться
    // когда подаю аргументы в экспорт После того как снова прибавил +1 сега исчезла (сегу находил с помощью санитайзера)
    if (!main->my_env)
        exit_with_error(main, ERROR_MALLOC);
    while (++i < len)
    {
        main->my_env[i] = ft_strdup(env[i]);
        free(env[i]); // освобождение в цикле чтобы убрать утечки
        if (!main->my_env[i])
            exit_with_error(main, ERROR_MALLOC);
    }
    free(env);
    main->my_env[i] = NULL;
}
