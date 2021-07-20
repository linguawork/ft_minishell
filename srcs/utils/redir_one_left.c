/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:08:22 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:08:24 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_file_in_folder(t_redir * redir)
{
    DIR *folder;
    struct dirent *entry;
    char *command;
    char buffer[1024];

    command = redir->redir_file;
    folder = opendir(getcwd(buffer, 1024));
//    folder = opendir("/Users/areggie/Desktop/minishell"); // for debugger
//    printf("%s\n", buffer);
        while((entry = readdir(folder)))
        {
            if (ft_strcmp(entry->d_name, command) == 0)
            {
                closedir(folder);
                return(1);
            }
        }
        closedir(folder);
    return(0);
}

int redir_one_left(t_main *main)
{
    int fd;
    int saved_stdin;// input from keyboard
    t_redir *redir;
//    int len;
    char *cmd;
    int file;


    redir = main->job->pipe->redir;
    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
    {
        // Обработка ошибок
//        if (!redir->command && redir->redir_type == INPUT && redir->redir_file )// один редирект < и один файл костыль вместо функции пока Миша делает
//        {
//            file = exists(redir->redir_file);
//            if (file == 0)
//            {
//                ft_putstr_fd("minishell: ", 2);
//                ft_putstr_fd(redir->redir_file, 2);
//                ft_putstr_fd(": No such file or directory\n", 2);
//                main->exit = 1;
//            }
//        }
//        if (redir->command && redir->redir_type == INPUT && !redir->redir_file)// один редирект < и один файл костыль вместо функции пока Миша делает
//        {
//            ft_putstr_fd ("minishell: ", 2);
//            ft_putstr_fd("syntax error near unexpected token `newline'", 2);
//            ft_putchar_fd ('\n', 2);
//            main->exit = 258; // Command not found
//            strerror(main->exit);
//        }
        check_valid_redir(main); // выше костыли вместо этой функции
// ОТРАБОТКА ОДНОГО РЕДИР
        if (redir->command && redir->redir_type == INPUT && redir->redir_file)// команда и редирект тип < и файл
        {
            saved_stdin = dup(0);
            file = find_file_in_folder(redir);
            if (file == 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(redir->redir_file, 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                main->exit = 258; // Command not found
//                strerror(main->exit);
            }
            else // если есть файл открываем
            {
                fd = open(redir->redir_file, O_RDONLY, S_IRWXU);
//            printf("The fd to file1: %d\n", file1); // печать номера 3
                dup2(fd, STDIN_FILENO); // файл дескр 3 забирает номер у stdin, 0)
                close(fd);// закрытие фд3 так как он сдублировался в фд0
                process_builtins_and_divide_externals(main);
                dup2(saved_stdin, 0);
                close(saved_stdin);
            }
        }
    }
//    len = count_redirects(main);
    // ОТРАБОТКА РЕДИР>1

    while (redir->redir_next != NULL) // если есть структура redir  и redir_next( 1 комманда и редирект >1)
    {
        if (redir->command && redir->redir_type == INPUT && redir->redir_file)// команда и редирект тип и файл
        {
            cmd = redir->command;
            file = find_file_in_folder(redir);
            if (file == 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(redir->redir_file, 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                main->exit = 1;
                main->exit = 258; // Command not found
                return(0);
            }
        }
        redir = redir->redir_next; // переход к след редир (уже нет команды
        if (!redir->command && redir->redir_type == INPUT && redir->redir_file)// нет команды и редирект тип и файл
        {
//            len = len - 1;
            while (redir->redir_next) // отняли один предыдущий с командой и печатаем всю длину
            {
                file = find_file_in_folder(redir);
                if (file == 0)
                {
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd(redir->redir_file, 2);
                    ft_putstr_fd(": No such file or directory\n", 2);
                    main->exit = 258; // Command not found
                    return(0);
                }
//                len--;
                redir = redir->redir_next; // переход к след редиректу
            }

            saved_stdin = dup(0);
            file = find_file_in_folder(redir);
            if (file == 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(redir->redir_file, 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                main->exit = 258; // Command not found
                strerror(main->exit);
                break;
            }
            fd = open(redir->redir_file, O_RDONLY, S_IRWXU);
            dup2(fd, STDIN_FILENO); // файл дескр 3 забирает номер у stdin, 0)
            close(fd);// закрытие фд3 так как он сдублировался в фд0
            redir->command = cmd;
            process_builtins_and_divide_externals(main);
            redir->command = NULL;
            cmd = NULL;
            dup2(saved_stdin, 0);
            close(saved_stdin);
            break ;
        }
    }
    return(0);
}