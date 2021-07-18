#include "minishell.h"

void redir_one_right_in_pipes(t_main *main)
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
            close(fd);// закрытие фд3 так как он сдублировался в фд0
            process_builtins_and_divide_externals_in_rp(main);
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
            process_builtins_and_divide_externals_in_rp(main);
            dup2(saved_stdout, 1);
            close(saved_stdout);
            break ;
        }
    }
}

void redir_two_right_in_pipes(t_main *main)
{
    int fd;
    int saved_stdout;
    t_redir *redir;
    int len;


    redir = main->job->pipe->redir;

    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
    {
//        if (!redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file )// костыль пока парсер правит один редирект >> и один файл
//        {
//            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644); // empty file // поменяли флаг на дозапись
//            if (fd == -1)
//                exit(1);
//        }
        check_valid_redir(main);

        if (redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)// команда и редирект тип >> и файл
        {
            saved_stdout = dup(1);
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644); // поменяли флаг на дозапись
            if (fd == -1)
                exit(1);
//            printf("The fd to file1: %d\n", file1); // печать номера 3
            dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
            close(fd);// закрытие фд3 так как он сдублировался в фд1
            process_builtins_and_divide_externals_in_rp(main);
            dup2(saved_stdout, 1);
            close(saved_stdout);
        }
    }
    len = count_redirects(main);
    while (redir->redir_next != NULL) // если есть структура redir   и redir_next( 1 комманда и редирект >1)
    {
        if (redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);// fd 1-3
            if (fd == -1)
                exit(1);
        }
        redir = redir->redir_next;
        if (!redir->command && redir->redir_type == APPEND_OUTPUT && redir->redir_file)// команда и редирект тип и файл
        {
            while (len-1) // отняли один предыдущий с командой и печатаем всю длину
            {
                fd = open(redir->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);// создание файлов по одной
                if (fd == -1)
                    exit(1);
                len--;
                redir = redir->redir_next; // переход к след редиректу
            }
            saved_stdout = dup(1);// сохранение
//            printf("The fd to file1: %d\n", file1); // печать номера 3
            dup2(fd, STDOUT_FILENO); // файл дескр 3 забирает номер у stdout, 1)
            close(fd);// закрытие фд3 так как он сдублировался в фд1
            process_builtins_and_divide_externals_in_rp(main);
            dup2(saved_stdout, 1);
            close(saved_stdout);
            break ;
        }
    }
}

int redir_one_left_in_pipes(t_main *main)
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
                process_builtins_and_divide_externals_in_rp(main);
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
            process_builtins_and_divide_externals_in_rp(main);
            redir->command = NULL;
            cmd = NULL;
            dup2(saved_stdin, 0);
            close(saved_stdin);
            break ;
        }
    }
    return(0);
}

int redir_two_left_in_pipes(t_main *main)
 {
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
//            if (ft_strcmp(redir->command, "cat") == 0)
//            {
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

                process_builtins_and_divide_externals_in_rp(main);
//                execute_pipes(main);
//                redir->args = NULL;
//            }
//            else
//                process_builtins_and_divide_externals_in_rp(main);
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
//        if (ft_strcmp(cmd, "cat") == 0)
//        {
//                redir->command = cmd;
            main->job->pipe->redir->args = (char **)malloc(sizeof(char *) * 2);// смещение аргумента в первую ноду редир из redir next
            // чтобы послед функция записи в двумерн массив выполнялась
            fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU); // empty file
            if (fd == -1)
                exit(1);
            ft_putstr_fd(redir->redir_file, fd);
            main->job->pipe->redir->args[0] = file;
            main->job->pipe->redir->args[1] = NULL;
            process_builtins_and_divide_externals_in_rp(main);
//                cmd =NULL;
//                redir->args = NULL;
//        }
//        else
//            process_builtins_and_divide_externals_in_rp(main);
    }
    cmd =NULL;
    redir->args = NULL;
    return 0;
}

//{
//    int fd[2];
//    t_redir *redir;
//    char str[ft_strlen(main->job->pipe->redir->redir_file) + 1];
//    int len;
//    int fork_res;
////    int savedstdin;
//
//    redir = main->job->pipe->redir;
//    if (pipe(fd) == -1)
//        return(1);
//    fork_res = fork();
//    if (fork_res == -1)
//        return(2);
//    if (fork_res == 0)
//    {
//        close(fd[0]);
//        ft_putstr_fd(redir->redir_file, 0);
//        redir->redir_file[ft_strlen(redir->redir_file) - 1] = '\0';
//        len = ft_strlen(redir->redir_file) + 1;
//        if (write(fd[1], &len, sizeof(int)) < 0)
//            return 3;
//        if (write(fd[1], &redir->redir_file, sizeof(char) * len) < 0)
//            return 4;
//        close(fd[1]);
//    }
//    else
//    {
//        close(fd[1]);
//        if (read(fd[0], &len, sizeof(int)) < 0)
//            return 5;
//        if (read(fd[0], &str, sizeof(int) * len) < 0)
//            return 6;
//        if (main->job->pipe_next != NULL)
//        {
//            dup2(STDOUT_FILENO, main->saved_stdout);
//            dup2(fd[0], STDOUT_FILENO);
////            dup2(savedstdin, 1);
////            close(savedstdin);
//        }
//
////        ft_putchar_fd('\n', 1);
//        close(fd[0]);
//        wait(NULL);
//    }
//    return 0;
//}

void process_redirects_in_pipes2(t_main *main)
{
    if (main->job->pipe->redir->redir_type == OUTPUT)
        redir_one_right_in_pipes(main);
    if (main->job->pipe->redir->redir_type == APPEND_OUTPUT)
        redir_two_right_in_pipes(main);
    if (main->job->pipe->redir->redir_type == INPUT)
        redir_one_left_in_pipes(main);
    if (main->job->pipe->redir->redir_type == INPUT_MULTILINE)
        redir_two_left_in_pipes(main);

}
