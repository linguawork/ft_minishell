/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:04 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:05 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

char** env_recorder(t_main *main)
{
    char **e;
    int length;

    length = how_many_lines(main->my_env);
    e = (char **) malloc(sizeof(char *) * (length + 1));

    int i = 0;
    while (main->my_env[i] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
    {
        e[i] = main->my_env[i];// лучше записывать через индекс
        i++;
    }
    e[i]=NULL;
    return(e);
}

void	double_for_sort_algo(char **envir, int size)
{
    char *tmp;
    int i;
    int j;

    i = -1; //если начать с нуля то TMPDIR выводится первым
    while (++i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (ft_strcmp(envir[i], envir[j]) > 0)
            {
                tmp = envir[i];
                envir[i] = envir[j];
                envir[j] = tmp;
            }
            j++;
        }
    }
}

void put_da_brackets( char **e)
{
    char *value1;
    char *value;
    int len;

    len = char_count(*e);
    value1 = (ft_strchr(*e, ('='))); // pointer marks the symbol in the string// all after =, including =str
    value = value1 + 1;//отрубаю после знака равно строку значения// пропускаем знак = через +1
    write(1, *e, len);// пишем до знака равно
    ft_putchar_fd('=', 1); // дописываем
    ft_putchar_fd('\"', 1); //
    ft_putstr_fd(value, 1); //
    ft_putchar_fd('\"', 1); //
}

void check_args(t_main *main, char **a)
{
    char invalid_char_str[5] = {'-','+',',','.',':'};
    int i;

    if (ft_strchr (*a, '_')) // допустимый символ в аргументе
        return;
    i = 0;
    while(invalid_char_str[i])
    {
        if (!ft_isalpha(*a[0]) || (ft_strchr(*a, invalid_char_str[i]))) // если первый  символ не буква то сообщение об ошибке
        {
            ft_putstr_fd ("minishell: ", 2);
            ft_putstr_fd (main->job->pipe->redir->command, 2);
            ft_putstr_fd (": `", 2);
            ft_putstr_fd (*a, 2);
            ft_putstr_fd ("': not a valid identifier", 2); // sega
            ft_putchar_fd ('\n', 2);
            main->flag2 = 1;
            break;
        }
        i++;
    }
}

int export(t_main *main)
{
    char *command;
    char **args;
    char **envir;
    int len;
    int i;
    int flag;

    envir = env_recorder(main);// копия чтобы в env не было алфавитного порядка, утечки были и я их убрал
    command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;

    len = how_many_lines(envir);
    i = 0;
    if (command && !args)
    {
        // len= how_many_lines(envir);// Длина у меня уже увеличилась на один в функции realloc
        // printf("export--->%d\n", len); // проверка длины после
        double_for_sort_algo(envir, len);
        while( envir[i] != NULL)
        {
            ft_putstr_fd("declare -x ", 1);
            if (!(ft_strchr(envir[i], '=')))// печать строки без знака =
            {
                ft_putstr_fd(envir[i], 1);
                ft_putchar_fd('\n', 1);
            }
            else // печать строки со знаком =
            {
                put_da_brackets(&envir[i]);// ставим кавычки
                ft_putchar_fd('\n', 1);
            }
            if(envir[i] == NULL)
                return(1);
            i++;
        }
        free(envir);// убирает только основной массив подмассивы не трогаем иначе теряются указатели на подстроки
    }
    else
    {

        char **e;
        flag = 0;
        i = 0;// первый аргумент нулевой
        len = how_many_lines(envir);
        // sleep(5);
        // printf("here\n");
        while (args[i] != NULL)// в цикле реалок еще на один аргумент с каждым новым аргументом
        {
            if (i > 0)
                envir = env_recorder(main);
            check_args(main, &args[i]);// проверка на допустимые символы
            flag = checker(main, &args[i], envir);
            if ((flag != 1) && (main->flag2 != 1))
            {
                e = env_recorder2(envir,len); //перезапись на лен +2
                e[len] = ft_strdup(args[i]);// в выделенную ячейку добавляем аргумент по индексу длины рядов массива, ставим аргумент в конце массива
                e[len + 1] = NULL; //сместили указатель на ноль по индексу длины рядов массива
                len++; //Длина у меня уже увеличилась на один в функции realloc и не нужно прибавлят
            }
            if (flag == 1 && main->sub == 1)
            {
                copy_env3(main, envir);
                main->sub = 0;
            }
            if ((flag != 1) && (main->flag2 != 1))
            {
                copy_env2(main, e);
                free(e);
            }
            free(envir);
            flag = 0;
            main->flag2 = 0;
            i++; //переход к следующему аргументу
        }
//		copy_env2(main, e);
//        free(envir);
//        free(e);
    }
    // arrays_free(envir);
    // sleep(1000);// for test leaks
    return(0);
}