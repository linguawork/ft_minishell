#include "minishell.h"

void check_valid_redir(t_main *main)
{
    t_redir *redir;
    int fd;
//    char *message;

    redir = main->job->pipe->redir;
    if ((!redir->command && redir->redir_type == OUTPUT && redir->redir_file ) || // один редирект > и один файл
    (!redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)) // один редирект >> и один файл
    {
        fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // empty file
        if (fd == -1)
        {
            main->exit = 1;
//            message = strerror(errno);
//            ft_putstr_fd(message, 2);
        }

    }
    if ((redir->command && redir->redir_type == OUTPUT && !redir->redir_file ) || // один редирект > и один файл
    (redir->command && redir->redir_type == APPEND_OUTPUT && !redir->redir_file ) || // один редирект > и один файл
    (redir->command && redir->redir_type == INPUT && !redir->redir_file)) // один редирект >> и один файл
    {
        ft_putstr_fd ("minishell: ", 2);
        ft_putchar_fd ('\n', 2);
        ft_putstr_fd("syntax error near unexpected token `newline'", 2);
        main->exit = 258; // Command not found
        strerror(main->exit);
    }
}

int count_redirects(t_main *main)
{
    int i;

    i = 1; // файловые дескрипторы считаем не с нуля
    t_redir *redir;

    redir = main->job->pipe->redir;
    while (redir->redir_next != NULL)
    {
        redir = redir->redir_next;
        i++;
    }
    return(i);
}


void redir_one_right(t_main *main)
{
    int fd;
    int saved_stdout;
    t_redir *redir;
    int len;


    redir = main->job->pipe->redir;

    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
    {
        if (!redir->command && redir->redir_type == OUTPUT && redir->redir_file )// один редирект и один файл
        {
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // empty file
            if (fd == -1)
                exit(1);
        }
        check_valid_redir(main);

        if (redir->command && redir->redir_type == OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            saved_stdout = dup(1);
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                exit(1);
//            printf("The fd to file1: %d\n", file1); // печать номера 3
            dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
            close(fd);// закрытие фд3 так как он сдублировался в фд1
            process_builtins_and_divide_externals(main);
            dup2(saved_stdout, 1);
            close(saved_stdout);
        }
    }
    len = count_redirects(main);
    while (redir->redir_next != NULL) // если есть структура redir   и redir_next( 1 комманда и редирект >1)
    {
        if (redir->command && redir->redir_type == OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);// fd 1-3
            if (fd == -1)
                exit(1);
        }
        redir = redir->redir_next;
        if (!redir->command && redir->redir_type == OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            while (len-1) // отняли один предыдущий с командой и печатаем всю длину
            {
                fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);// создание файлов по одной
                if (fd == -1)
                    exit(1);
                len--;
                redir = redir->redir_next; // переход к след редиректу
            }
                saved_stdout = dup(1);// сохранение
//            printf("The fd to file1: %d\n", file1); // печать номера 3
                dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
                close(fd);// закрытие фд3 так как он сдублировался в фд1
                process_builtins_and_divide_externals(main);
                dup2(saved_stdout, 1);
                close(saved_stdout);
                break ;
        }
    }
}