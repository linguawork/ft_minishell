/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:10 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:14 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_doubles(t_main *main, char **args, char **en)
{
    char *a_name;
    int len;
    char *e_name;
    int len2;

    while (*en != NULL)
    {
        if(ft_strcmp(*args, *en) == 0)
            return(1);
        else if((ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
        {
            len= char_count(*args); // замер до равно
            a_name = ft_substr(*args, 0, len); // отрезать до равно получается арг без равно
            if (ft_strcmp(a_name, *en) != 0) // полное несоответствие строк до знака = и освобождение указателя
                free(a_name);
            if(ft_strcmp(a_name, *en) == 0) // сравнение без знаков равно
            {
                free(*en);
                *en =ft_strdup(*args);
                free(*args);// убрал утечку после исполнения команды
                free(a_name);
                main->sub = 1;
                return(1);
            }
        }
        else if((ft_strchr(*args, '=')) && (ft_strchr(*en, '='))) // если и арг и env со знаком =
        {
            len= char_count(*args);
            len2 = char_count(*en);
            a_name = ft_substr(*args, 0, len); // получ арг до знака равно
            e_name = ft_substr(*en, 0, len2); // получ env до знака равно
            if (ft_strcmp(a_name, e_name) != 0) // если нет полного соответствия строк до знака =
            {
                free(e_name);
                free(a_name);
            }
            if (ft_strcmp(a_name, e_name) == 0) // полное соответствие строк до знака =
            {
                free(*en);
                *en =ft_strdup(*args);// перезапись
                free(*args);// убрал утечку после исполнения команды
                free(a_name);
                free(e_name);
                main->sub = 1;
                return(1);
            }
        }
        else if(!(ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
        {
            if(ft_strcmp(*args, *en) == 0) // полное соответствие строк без знака =
                return(1);
        }
        else if(!(ft_strchr(*args, '=')) && (ft_strchr(*en, '=')))
        {
            len= char_count(*en); // переопределение и замер до равно
            e_name = ft_substr(*en, 0, len); // отрезать до равно получается en без равно
            // e_name = read_name(*en);
            if (strcmp(*args, e_name) != 0) // полное соответствие строк до знака =
                free(e_name);
            if(strcmp(*args, e_name) == 0)// сравнение без знаков равно
            {
                free(e_name);
                return(1);
            }
        }
        en++;
    }
    return(0);
}

int checker (t_main *main, char **a, char **e)
{
    if (check_doubles(main, a, e) == 1)
        return(1);
    else
        return(0);
}

char** env_recorder2(char **envir, int len)
{
    char **e;

    e = (char **) malloc(sizeof(char *) * (len + 2));

    int i = 0;
    while (envir[i] && i != len) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
    {
        e[i] = envir[i];// лучше записывать через индекс
        i++;
    }
//    e[len] = envir[i++];
//    e[len+1]=NULL;
    return(e);
}