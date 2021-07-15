#include "minishell.h"

int count_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return(i);
}

int exists(const char *command)
{
    FILE *file;
    if ((file = fopen(command, "r+")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

//int	process_valid_cmd(t_main *main, char *s) // от флагов в парсере лучше отказаться и парсить все в аргументы
//{
//	char	*str;
//	int		i;
//
//
//	str = s;
//	i = 0;
//	while (str[i] != '\0' )
//	{
//		if(!ft_isdigit(str[i]) && ft_isascii(str[i]) )
//		{
//			main->exit = 127;// для команды пишем код возврата вручную // программа не завершается
//			break ;
//		}
//		i++;
//	}
//}

//int echo_pipes(char **cmd)
//{
//    char *command;
//    char *args;
//    int i;
//
//    i = 0;
////	char **dup_args;
//
//    command = cmd[i];
//    args = cmd[++i];
////    dup_args = args;
//    main->exit = 0;
//    if (command)
//    {
//        if (!args)
//            ft_putchar_fd('\n', 1);
//        if (args)
//        {
//            if (ft_strcmp(*args, "-n") == 0)
//            {
//                while (*args != NULL && (ft_strcmp(*args, "-n") == 0))
//                    args++;
//                if (*args == NULL)
//                    return (0);
//                write(1, *args, ft_strlen(*args));
//                while (*++args != NULL)
//                {
//                    ft_putchar_fd(' ', 1);
//                    write(1, *args, ft_strlen(*args));
//                }
//            }
//            else
//            {
//                while (*args != NULL)
//                {
//                    ft_putstr_fd(*args, 1);
//                    ft_putchar_fd(' ', 1);
//                    args++;
//                }
//                ft_putchar_fd('\n', 1);
//            }
//        }
//    }// here we need to free leaks after working
//    return(0);
//}

//void	ctrl_slash2(int sig)
//{
//    ft_putstr_fd("^\\Quit: 3\n", 2);
//    sig = 3;
//
//}

//void simultaneous_pipes (int i, t_main *main, char ***commands)
//{
//    int prev_pipe_fds[2]; // объявляем массив предыдущ файловых дескрипторов
//    int next_pipe_fds[2];
//    char **cmd;
//    while (i < main->job->num_commands) // пока не прошлись по всем командам
//    {
//        prev_pipe_fds[0] = next_pipe_fds[0]; // предыдущ нулевой присваивает значение след нулевого
//        prev_pipe_fds[1] = next_pipe_fds[1];
//        if (i != main->job->num_commands - 1) // если кол-во команд не равно количеству команд-1 (те кол-ву пайпов)
//            pipe(next_pipe_fds);// создаем каналы (трубы для следующих команд)
//        else // иначе если команды равны пайпам
//        {
//            next_pipe_fds[0] = -1; // инициализируем на -1
//            next_pipe_fds[1] = -1;
//        }
////        status = 0;
//        cmd = &*commands[i];
//        process_folder_in_pipes(main, cmd);// обработка папки
//        if (main->flag2 != 1)
//        {
//            if (fork() == 0) // в дочери
//            {
//                connect_stdio_to_pipes(prev_pipe_fds, next_pipe_fds); // соединяем предыд в следующие
//                process_builtins_in_pipes(main, cmd);
//                if (ft_strchr(cmd[0], '/')) {
//                    execve(cmd[0], cmd, NULL);// если absolute path
//                } else {
//                    process_exe_in_pipes(main, cmd);// if external cmd without path
//                }
//            }
//        }
////        if (main->flag2 == 1)
//        main->flag2 = 0;// если нашел папку
//        close(prev_pipe_fds[0]); // закрываем вход предыдущ
//        close(prev_pipe_fds[1]); // закрываем вход предыдущ
//        i++;
//    }
//    wait(NULL); // один wait может ждать несколько процессов без pid но проблема что долго ждет и выводит после minishell
//}