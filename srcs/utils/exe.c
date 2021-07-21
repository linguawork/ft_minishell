/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:06:52 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:06:53 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

char *return_cmd_from_absolute_path(t_main *main)
{
    char *cmd;
    char **parts;
    int len;

    parts = ft_split(main->job->pipe->redir->command, '/');
    len = how_many_lines(parts);
    cmd = parts[len-1];
    return(cmd);
}

char** cmd_args_to_argv_recorder2(t_main *main) // запись аргументов в 2мер массив
{
    char **e;
    int length;
    char **a;
    char *cmd;
    cmd = return_cmd_from_absolute_path(main);
    a = main->job->pipe->redir->args;
    int i = 1;
    int j = 0;
    if (a == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
    {
        e = (char **) malloc(sizeof(char *) * (1 + 1));
        e[0] = cmd;
    }
    else// если аргументов не один
    {
        length = how_many_lines((char **) a);// считаем кол-во аргументов
        e = (char **) malloc(sizeof(char *) * (length + 1+1)); // выделяем память + 1 для ноля и +1 для команды
        e[0] = cmd;
        while (a[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
        {
            e[i] = a[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
            j++;
            i++;
        }
    }
    e[i]=NULL;// в конце добав терминатор
    return(e);
}

char** cmd_args_to_argv_recorder_p(t_job *job) // запись аргументов в 2мер массив
{
    char **e;
    int length;
    char **a;
    char *cmd;
//    cmd = main->job->pipe->redir->command;
//    a = main->job->pipe->redir->args;
    cmd = job->pipe->redir->command;
    a = job->pipe->redir->args;
    int i = 1;
    int j = 0;
    if (a == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
    {
        e = (char **) malloc(sizeof(char *) * (1 + 1));
        e[0] = cmd;
    }
    else// если аргументов не один
    {
        length = how_many_lines((char **) a);// считаем кол-во аргументов
        e = (char **) malloc(sizeof(char *) * (length + 1+1)); // выделяем память + 1 для ноля и +1 для команды
        e[0] = cmd;
        while (a[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
        {
            e[i] = a[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
            j++;
            i++;
        }
    }
    e[i]=NULL;// в конце добав терминатор
    return(e);
}

char** cmd_args_to_argv_recorder(t_main *main) // запись аргументов в 2мер массив
{
    char **e;
    int length;
    char **a;
    char *cmd;
    cmd = main->job->pipe->redir->command;
    a = main->job->pipe->redir->args;
    int i = 1;
    int j = 0;
    if (a == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
    {
        e = (char **) malloc(sizeof(char *) * (1 + 1));
        e[0] = cmd;
    }
    else// если аргументов не один
    {
        length = how_many_lines((char **) a);// считаем кол-во аргументов
        e = (char **) malloc(sizeof(char *) * (length + 1+1)); // выделяем память + 1 для ноля и +1 для команды
        e[0] = cmd;
        while (a[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
        {
            e[i] = a[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
            j++;
            i++;
        }
    }
    e[i]=NULL;// в конце добав терминатор
    return(e);
}

//char** cmd_args_to_argv_recorder_p(t_main *main) // запись аргументов в 2мер массив
//{
//    char **e;
//    int length;
//    char **a;
//    char *cmd;
////    cmd = main->job->pipe->redir->command;
////    a = main->job->pipe->redir->args;
//    cmd = job->pipe->redir->command;
//    a = job->pipe->redir->args;
//    int i = 1;
//    int j = 0;
//    if (a == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
//    {
//        e = (char **) malloc(sizeof(char *) * (1 + 1));
//        e[0] = cmd;
//    }
//    else// если аргументов не один
//    {
//        length = how_many_lines((char **) a);// считаем кол-во аргументов
//        e = (char **) malloc(sizeof(char *) * (length + 1+1)); // выделяем память + 1 для ноля и +1 для команды
//        e[0] = cmd;
//        while (a[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
//        {
//            e[i] = a[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
//            j++;
//            i++;
//        }
//    }
//    e[i]=NULL;// в конце добав терминатор
//    return(e);
//}

int path_mistakes(t_main *main, char *p)
{
    char *error_mes;

    error_mes = strerror(errno);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(main->job->pipe->redir->command, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(p, 2);
    ft_putchar_fd(' ', 2);
    ft_putstr_fd(error_mes, 2);
    ft_putchar_fd('\n', 2);
    return (1);
}

int process_exe(t_main *main)
{
    char *command;
    char **envir;
    char **binar;
    char *path;
    char *exe;
    char *exe2;
    int i;
    int fork_res;
    int status;
    DIR *folder;
    struct dirent *entry;
    status = 0;

    command = main->job->pipe->redir->command;
    char **argv;
    envir = main->my_env;
    i = 0;
    path = ft_getenv(main, "PATH");
    if(!path)
    {
        main->exit = 1;
        return (path_mistakes(main, path));
    }
    binar = ft_split(path, ':');
    while (binar[i] != NULL)
    {
        folder = opendir(binar[i]);
        if(folder == NULL)
            i++;
        else
        {
            while((entry = readdir(folder)))
            {
                if (ft_strcmp(entry->d_name, command) == 0)
                {
                    argv = cmd_args_to_argv_recorder(main);
                    exe = ft_strjoin(binar[i], "/");
                    exe2 = ft_strjoin(exe, command);
                    fork_res = fork();
                    if (fork_res == 0)
                    {
//                        for (int j = 0; argv[j] != NULL; ++j) {
//                            printf("%s\n", argv[i]);
//                        }
                        signal(SIGQUIT, SIG_DFL);
                        execve(exe2, argv, envir);
//                        printf(" we are here\n");

                    }
//
                    if (fork_res > 0)
                    {
                        waitpid(fork_res, &status, 0);
                        main->exit = WEXITSTATUS(status);
                        free(exe);
                        free(exe2);
                        free(argv);
                    }
//                    ft_putstr_fd("status number is ", 1);
//                    ft_putnbr_fd (WEXITSTATUS(status), 1); // запись кода выхода 1
//                    write(1, "\n", 1);
//                    ft_putstr_fd("main_>exit is ", 1);
//                    ft_putnbr_fd (main->exit, 1);
//                    write(1, "\n", 1);
//                    ft_putstr_fd("parent id is ", 1); // если использовать printf то печатает после завершения программы
//                    ft_putnbr_fd (fork_res, 1);// ID родителя
//                    write(1, "\n", 1);

//                    ft_putnbr_fd (WIFSIGNALED(status), 2);// для теста сигнала
//                    write(1, "\n", 1);// для теста сигнала
//                    if (WIFSIGNALED(status)== 1) // if true
//                        ft_putstr_fd("^\\Quit: 3\n", 2);


                    closedir(folder);
                    arrays_free(binar);
                    return(1);// можно просто брейкать
                }
            }
            closedir(folder);
        }
//
        i++;
    }
    arrays_free(binar);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": Command not found\n", 2);
    main->exit = 127;
    return(0);
}