#include "minishell.h"

char **pipe_next_cmd_recorder(t_job *job)
{
    char **cmd_array;
    int len;
    char **args;
    char *cmd;

    cmd = job->pipe_next->redir->command;
    args = job->pipe_next->redir->args;
    int i = 1;
    int j = 0;
    if (args == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
    {
        cmd_array = (char **) malloc(sizeof(char *) * (1 + 1));
        cmd_array[0] = cmd;
    }
    else// если аргументов не один
    {
        len = how_many_lines((char **) args);// считаем кол-во аргументов
        cmd_array = (char **) malloc(sizeof(char *) * (len + 1+1)); // выделяем память + 1 для ноля и +1 для команды
        cmd_array[0] = cmd;
        while (args[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
        {
            cmd_array[i] = args[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
            j++;
            i++;
        }
    }
    cmd_array[i]=NULL;// в конце добав терминатор
    return(cmd_array);
}

char ***pipe_cmd_args_recorder(t_main *main) // запись команд и их аргументов в 2м массив
{
    int i;
    int c_num;
    char ***cmds;
    int p_num;
    t_job *job;

    job = main->job;
    c_num= main->job->num_commands;
    cmds = (char ***) malloc(sizeof(char *) * (c_num + 1));
    p_num = c_num - 1;
    i = 0;
    if (p_num == 1)
    {
        cmds[i] = cmd_args_to_argv_recorder_p(job);
        cmds[++i] = pipe_next_cmd_recorder(job);
        cmds[++i] = NULL;
        return(cmds);
    }
    if (p_num > 1)
    {
        cmds[i] = cmd_args_to_argv_recorder_p(job);
        cmds[++i] = pipe_next_cmd_recorder(job);

        while (job->job_next)
        {
            job = job->job_next;// трансформация структуры
            cmds[++i] = cmd_args_to_argv_recorder_p(job); // функция для job->pipe

            if (job->pipe_next != NULL)
                cmds[++i] = pipe_next_cmd_recorder(job); // функция для job->pipe_next
        }
        cmds[++i] = NULL;
    }
    return(cmds);
}

void connect_stdio_to_pipes(int prev_fds[], int next_fds[])
{
    if (prev_fds[0] >= 0) // если есть что-то в нулевом фд (вход) или ноль ()
    {
        dup2(prev_fds[0], 0); // дублируем нулевой в ноль (запись в файл) // вливание в трубу
        close(prev_fds[0]);
        close(prev_fds[1]);
    }
    if (next_fds[1] >= 0)// след 1 фд на выход имеет что-то
    {
        dup2(next_fds[1], 1); // дублируем 1 в 1 (письмо из файла = выход) выливание из трубы
        close(next_fds[1]);
        close(next_fds[0]);
    }
}

void simultaneous_pipes (int i, t_main *main, char ***commands)
{
    int prev_pipe_fds[2]; // объявляем массив предыдущ файловых дескрипторов
    int next_pipe_fds[2];
    char **cmd;
    while (i < main->job->num_commands) // пока не прошлись по всем командам
    {
        prev_pipe_fds[0] = next_pipe_fds[0]; // предыдущ нулевой присваивает значение след нулевого
        prev_pipe_fds[1] = next_pipe_fds[1];
        if (i != main->job->num_commands - 1) // если кол-во команд не равно количеству команд-1 (те кол-ву пайпов)
            pipe(next_pipe_fds);// создаем каналы (трубы для следующих команд)
        else // иначе если команды равны пайпам
        {
            next_pipe_fds[0] = -1; // инициализируем на -1
            next_pipe_fds[1] = -1;
        }
//        status = 0;
        cmd = &*commands[i];
        process_folder_in_pipes(main, cmd);// обработка папки
        if (main->flag2 != 1)
        {
            if (fork() == 0) // в дочери
            {
                connect_stdio_to_pipes(prev_pipe_fds, next_pipe_fds); // соединяем предыд в следующие
                process_builtins_in_pipes(main, cmd);
                if (ft_strchr(cmd[0], '/')) {
                    execve(cmd[0], cmd, NULL);// если absolute path
                } else {
                    process_exe_in_pipes(main, cmd);// if external cmd without path
                }
            }
        }
//        if (main->flag2 == 1)
        main->flag2 = 0;// если нашел папку
        close(prev_pipe_fds[0]); // закрываем вход предыдущ
        close(prev_pipe_fds[1]); // закрываем вход предыдущ
        i++;
    }
    wait(NULL); // один wait может ждать несколько процессов без pid но проблема что долго ждет и выводит после minishell
}


int execute_pipes (t_main *main)
{
    int c_num;
    char ***commands;
    int prev_pipe_fds[2]; // объявляем массив предыдущ файловых дескрипторов
    int next_pipe_fds[2];
    char **cmd;
    int fork_res;
    int status;

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

    int i = 0; // итератор
    next_pipe_fds[0] = -1; // инициализация  значения следующих файловых дескрипторов нулевого элемента
    next_pipe_fds[1] = -1;
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
//        process_folder_in_pipes(main, cmd);// обработка папки
        if (main->flag2 != 1)
        {
            if ((ft_strcmp(cmd[0],"yes")== 0) || (ft_strcmp(cmd[0],"cat")== 0))
            simultaneous_pipes(i, main, commands);
            else
            {
                fork_res = fork();

                if (fork_res == 0) // в дочери
                {
                    connect_stdio_to_pipes(prev_pipe_fds, next_pipe_fds); // соединяем предыд в следующие
                    process_builtins_in_pipes(main, cmd);
                    if (ft_strchr(cmd[0], '/'))
                    {
                        execve(cmd[0], cmd, NULL);// если absolute path
                    }
                    else
                    {
                        process_exe_in_pipes(main, cmd);// if external cmd without path
                    }
                }
                close(prev_pipe_fds[0]); // закрываем вход предыдущ
                close(prev_pipe_fds[1]); // закрываем вход предыдущ
                waitpid(fork_res, &status, 0); // через waitpid завершение до вывода минишелл
                main->exit = WEXITSTATUS(status);
                if (status == 11) // command not found
                {
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd(cmd[0], 2);
                    ft_putstr_fd(": Command not found\n", 2);
                    main->exit = 127;
                    break;
                }
            }
        }

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
//    wait(NULL); // один wait может ждать несколько процессов без pid но проблема что долго ждет и выводит после minishell
//    main->job->num_commands = 0; // занулил в end_session
//    main->job->num_pipes = 0;
    return(0);
}