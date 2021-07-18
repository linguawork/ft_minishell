/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:23 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:26 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_for_redir_type(t_main *main, int i)
{
    t_job *job;
    job = main->job;

    if (i == 0 && job->pipe->redir->redir_type != ERROR)
        main->sub = 1;
    if (i == 1 && job->pipe_next->redir->redir_type != ERROR)
        main->sub = 1;
    if (i > 1)
        job = job->job_next;
    if (i == 2 && job->pipe->redir->redir_type != ERROR)
        main->sub = 1;
    if (i == 3 && job->pipe_next->redir->redir_type != ERROR)
        main->sub = 1;
    return(0);
}

void process_redirs_in_pipes(t_main *main, int *prev_pipe_fds, int *next_pipe_fds)
{
    int fork_res;

        fork_res = fork();
        if (fork_res == 0) // в дочери
        {
            stdin_and_out_to_pipes(prev_pipe_fds, next_pipe_fds); // соединяем предыд в следующие
            signal(SIGQUIT, SIG_DFL);
            process_redirects_in_pipes2(main);
        }

//    if (prev_pipe_fds[0] >= 0) // если есть что-то в нулевом фд (вход) или ноль ()
//    {
//        close(prev_pipe_fds[0]);
//        dup2(prev_pipe_fds[0], 0); // дублируем нулевой в ноль (запись в файл) // вливание в трубу
//        close(prev_pipe_fds[1]);
////        dup2(saved_stdout, 1);
////        close(saved_stdout);
//    }
//    if (next_pipe_fds[1] >= 0)// след 1 фд на выход имеет что-то
//    {
//        close(next_pipe_fds[1]);
//        dup2(next_pipe_fds[1], 1); // дублируем 1 в 1 (письмо из файла = выход) выливание из трубы
//        close(next_pipe_fds[0]);
//    }
}


int execute_pipes_and_redirs(t_main *main)
{
    int c_num;
    char ***commands;
    int prev_pipe_fds[2]; // объявляем массив предыдущ файловых дескрипторов
    int next_pipe_fds[2];
    char **cmd;
    int fork_res;
    int status;
//    t_job *job;

//    int flag;
    if (main->job->num_commands == main->job->num_pipes)
    {
        ft_putstr_fd("Error: According to the subject we do not need to process multiline!\n", 2);
//        main->exit = 1;
        return(0);
    }

    commands = pipe_cmd_args_recorder(main);
//    char **cmd = &*commands[i]; // по адресу передаем значение в разыменовании 3мерного в 2хмерный // test
//    length = how_many_lines(*commands); // кол-во комманд
//    c_num = main->job->num_pipes + 1;
//    c_num = 4;
    c_num= main->job->num_commands;

//    job = main->job;
    int i = 0; // итератор
    next_pipe_fds[0] = -1; // инициализация  значения следующих файловых дескрипторов нулевого элемента
    next_pipe_fds[1] = -1;
//    while (i < c_num) // пока не прошлись по всем командам
    while (i < c_num) // пока не прошлись по всем командам
    {
        prev_pipe_fds[0] = next_pipe_fds[0]; // предыдущ нулевой присваивает значение след нулевого
        prev_pipe_fds[1] = next_pipe_fds[1];
        if (i != c_num - 1) // если кол-во команд не равно количеству команд-1 (те кол-ву пайпов)
            pipe(next_pipe_fds);// создаем каналы (трубы для следующих команд)
        else // иначе если команды равны пайпам
        {
            next_pipe_fds[0] = -1; // инициализируем на -1
            next_pipe_fds[1] = -1;
        }
        status = 0;
        cmd = &*commands[i];
        process_folder_in_pipes(main, cmd);// обработка папки
        check_for_redir_type(main, i);
        if(main->sub == 1 && main->flag2 != 1)
        {
            process_redirs_in_pipes(main, prev_pipe_fds, next_pipe_fds);
            main->sub = 0;

        }
        else
        {
            if (main->flag2 != 1)
                fork_res = fork();
            if (fork_res == 0) // в дочери
            {

                stdin_and_out_to_pipes(prev_pipe_fds, next_pipe_fds); // соединяем предыд в следующие
                process_builtins_in_pipes(main, cmd);
                signal(SIGQUIT, SIG_DFL);
                if (ft_strchr(cmd[0], '/'))
                {
                    execve(cmd[0], cmd, NULL);// если absolute path
                } else
                {
                    process_exe_in_pipes(main, cmd);// if external cmd without path
                }
            }
        }
//        if (i != c_num - 1)
//        {
////            close(prev_pipe_fds[0]); // закрываем вход предыдущ
//            close(prev_pipe_fds[1]); // закрываем вход предыдущ
//        }
//        else
//        {
            close(prev_pipe_fds[0]); // закрываем вход предыдущ
            close(prev_pipe_fds[1]); // закрываем вход предыдущ
//        }

//        waitpid(fork_res, &status, 0); // через waitpid завершение до вывода минишелл
//        main->exit = WEXITSTATUS(status);


//         for testing
//        ft_putstr_fd("status number is ", 1);
//        ft_putnbr_fd(status, 1);
//        write(1, "\n", 1);
//        ft_putstr_fd("Wexitstatus(status) is ", 1);
//        ft_putnbr_fd (WEXITSTATUS(status), 1); // запись кода выхода 1
//        write(1, "\n", 1);
//        ft_putstr_fd("main_>exit is ", 1);
//        ft_putnbr_fd (main->exit, 1);
//        write(1, "\n", 1);
//        ft_putstr_fd("parent id is ", 1); // если использовать printf то печатает после завершения программы
//        ft_putnbr_fd (fork_res, 1);// ID родителя
//        write(1, "\n", 1);
        i++;
    }
    waitpid(fork_res, &status, 0); // через waitpid завершение до вывода минишелл
    main->exit = WEXITSTATUS(status);
    if (status == 11) // command not found
    {
        ft_putstr_fd("minishell: ", 1);
        ft_putstr_fd(cmd[0], 1);
        ft_putstr_fd(": Command not found\n", 1);
        main->exit = 127;
    }
    i = 1;
    while (i < c_num)
    {
//        ft_putnbr_fd(i, 1);
        wait(NULL);
        i++;
    }
    // один wait может ждать несколько процессов без pid но проблема что долго ждет и выводит после minishell
//    main->job->num_commands = 0; // занулил в end_session
//    main->job->num_pipes = 0;
    return(0);
}