#include "minishell.h"

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


void redir_one_right (t_main *main)
{
    int fd;
//    int *files;
    int saved_stdout;
    t_redir *redir;
    int i;
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
    i = 0;
    len = count_redirects(main);
//    files = (int *) malloc(sizeof(int *) * (len + 1));

    while (redir->redir_next != NULL) // если есть структура redir (одна команда  один редирект и один файл) и redir_next( редир тип и файло)
    {
//        fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);// создание файлов
//        if (fd == -1)
//            exit(1);
        if (redir->command && redir->redir_type == OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                exit(1);
        }
        redir = redir->redir_next;
        if (!redir->command && redir->redir_type == OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            while (len-1)
            {

                fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);// создание файлов
                if (fd == -1)
                    exit(1);
                len--;
                redir = redir->redir_next;
            }
//            if (redir->redir_next == NULL) // запись в последний файл
//            {
                saved_stdout = dup(1);
//            printf("The fd to file1: %d\n", file1); // печать номера 3
                dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
                close(fd);// закрытие фд3 так как он сдублировался в фд1
                process_builtins_and_divide_externals(main);
                dup2(saved_stdout, 1);
                close(saved_stdout);
                break ;
//                files[i++] = 0;
//            }


//            printf("The fd to file1: %d\n", file1); // печать номера 3
//            dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
//            close(fd);// закрытие фд3 так как он сдублировался в фд1
//            process_builtins_and_divide_externals(main);
//            dup2(saved_stdout, 1);
//            close(saved_stdout);
        }
    }
//    if (p_num > 1)
//    {
//        cmds[i] = cmd_args_to_argv_recorder_p(job);
//        cmds[++i] = pipe_next_cmd_recorder(job);
//
//        while (job->job_next)
//        {
//            job = job->job_next;// трансформация структуры
//            cmds[++i] = cmd_args_to_argv_recorder_p(job); // функция для job->pipe
//
//            if (job->pipe_next != NULL)
//                cmds[++i] = pipe_next_cmd_recorder(job); // функция для job->pipe_next
//        }
//        cmds[++i] = NULL;
//    }
//    return(cmds);
}