#include "minishell.h"

int redir_two_left(t_main *main) {
    int fd;
//    int saved_stdout;
    t_redir *redir;
//    char str[ft_strlen(main->job->pipe->redir->redir_file) + 1];
//    int len;
//    int fork_res;
    char *cmd;
    char *file;

    check_valid_redir(main);
    file = "tmp";
    redir = main->job->pipe->redir;
    cmd = redir->command;
    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
    {
        if (redir->command && redir->redir_type == INPUT_MULTILINE &&
            redir->redir_file)// команда и редирект тип >> и файл
        {
            if (ft_strcmp(redir->command, "cat") == 0)
            {
                redir->args = (char **)malloc(sizeof(char *) * 2);
//                saved_stdout = dup(0);
                fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU); // empty file
                if (fd == -1)
                    exit(1);
//                dup2(fd, STDIN_FILENO); // файл дескр 3 забирает номер у stdout, 0)
//                close(fd);// закрытие фд3 так как он сдублировался в фд1
                ft_putstr_fd(redir->redir_file, fd);
//                dup2(saved_stdout, 0);
//                close(saved_stdout);
//                redir->args[0] = file;
//                redir->args[1] = NULL;
                 redir->args[0] = file;
                 redir->args[1] = NULL;
//                printf ("__%d___%d\n", dup2(fd, STDIN_FILENO), fd);

                process_builtins_and_divide_externals(main);
//                execute_pipes(main);
//                redir->args = NULL;
            }
            else
                process_builtins_and_divide_externals(main);
//            cmd = NULL;
        }

    }
    while (redir && redir->redir_next != NULL) // если редир > 1
        redir = redir->redir_next;
    if (!redir->command && redir->redir_type == INPUT_MULTILINE &&
        redir->redir_file && redir->redir_next == NULL)// команда и редирект тип >> и файл
        {
            if (cmd == NULL)
                return(0);
            if (ft_strcmp(cmd, "cat") == 0)
            {
//                redir->command = cmd;
                main->job->pipe->redir->args = (char **)malloc(sizeof(char *) * 2);// смещение аргумента в первую ноду редир из redir next
                // чтобы послед функция записи в двумерн массив выполнялась
                fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU); // empty file
                if (fd == -1)
                    exit(1);
                ft_putstr_fd(redir->redir_file, fd);
                main->job->pipe->redir->args[0] = file;
                main->job->pipe->redir->args[1] = NULL;
                process_builtins_and_divide_externals(main);
//                cmd =NULL;
//                redir->args = NULL;
            }
            else
                process_builtins_and_divide_externals(main);
        }
    cmd =NULL;
    redir->args = NULL;
    return 0;
}

//{
//    int fd;
//    int saved_stdin;
//    t_redir *redir;
//    int len;
//
//
//    redir = main->job->pipe->redir;
//
//    len = count_redirects(main);
//
//    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
//    {
//
//    //        check_valid_redir(main);
//
//        if (redir->command && redir->redir_type == INPUT_MULTILINE && redir->redir_file)// команда и редирект тип >> и файл
//        {
//            saved_stdin = dup(0);// copy of stdin
//            fd = open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); // поменяли флаг на дозапись
//            if (fd == -1)
//                exit(1);
//            //            printf("The fd to file1: %d\n", file1); // печать номера 3
//            dup2(fd, STDIN_FILENO); // файл дескр 3 забирает номер у stdin, 0)
//            close(fd);// закрытие фд3 так как он сдублировался в фд0
//            process_builtins_and_divide_externals(main);
//            dup2(saved_stdin, 0);
//            close(saved_stdin);
//        }
//    }
//


//    len = count_redirects(main);
//    while (redir->redir_next != NULL) // если есть структура redir   и redir_next( 1 комманда и редирект >1)
//    {
//        if (redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)// команда и редирект тип и файл
//        {
//            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);// fd 1-3
//            if (fd == -1)
//            exit(1);
//        }
//        redir = redir->redir_next;
//        if (!redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)// команда и редирект тип и файл
//        {
//        while (len-1) // отняли один предыдущий с командой и печатаем всю длину
//        {
//            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);// создание файлов по одной
//            if (fd == -1)
//                exit(1);
//            len--;
//            redir = redir->redir_next; // переход к след редиректу
//        }
//        saved_stdout = dup(1);// сохранение
//        //            printf("The fd to file1: %d\n", file1); // печать номера 3
//        dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
//        close(fd);// закрытие фд3 так как он сдублировался в фд1
//        process_builtins_and_divide_externals(main);
//        dup2(saved_stdout, 1);
//        close(saved_stdout);
//        break ;
//    }
//}
//}