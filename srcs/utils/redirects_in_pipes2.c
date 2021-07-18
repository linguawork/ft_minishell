#include "minishell.h"


int process_exe_in_rp(t_main *main)
{
    char *command;
    char **envir;
    char **binar;
    char *path;
    char *exe;
    char *exe2;
    int i;
//    int fork_res;
//    int status;
    DIR *folder;
    struct dirent *entry;
//    status = 0;

    command = main->job->pipe->redir->command;
    char **argv;
    envir = main->my_env;
    i = 0;
    path = ft_getenv(main, "PATH");
    if(!path)
        return 0;
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
//                    fork_res = fork();
//                    if (fork_res == 0)
//                    {
////                        for (int j = 0; argv[j] != NULL; ++j) {
////                            printf("%s\n", argv[i]);
////                        }
//                        signal(SIGQUIT, SIG_DFL);
                        execve(exe2, argv, envir);
//                        printf(" we are here\n");

//                    }
////
//                    if (fork_res > 0)
//                    {
//                        waitpid(fork_res, &status, 0);
//                        main->exit = WEXITSTATUS(status);
//                        free(exe);
//                        free(exe2);
//                    }
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
        i++;
    }
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": Command not found\n", 2);
    main->exit = 127;
    return(0);
}

int process_ready_exe_in_rp(t_main *main)
{
    char *command;
    char **args;
    char **envir;
//    int fork_res;
    char **argv;
//    int status;

    command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
    envir = main->my_env;
//    status = 0;

    argv = cmd_args_to_argv_recorder2(main);
//    fork_res = fork();
//    if (fork_res == 0)
        execve(command, argv, envir);
//    if (fork_res > 0)
//    {
//        waitpid(fork_res, &status, 0);
//        main->exit = WEXITSTATUS(status);
//    }
    // for testing
//    ft_putstr_fd("status number is ", 1);
//    ft_putnbr_fd(status, 1);
//    ft_putnbr_fd (WEXITSTATUS(status), 1); // запись кода выхода 1
//    write(1, "\n", 1);
//    ft_putstr_fd("main_>exit is ", 1);
//    ft_putnbr_fd (main->exit, 1);
//    write(1, "\n", 1);
//    ft_putstr_fd("parent id is ", 1); // если использовать printf то печатает после завершения программы
//    ft_putnbr_fd (fork_res, 1);// ID родителя
//    write(1, "\n", 1);
    // end for testing
//    if (main->exit == 0)
//        return(1);// можно просто брейкать
//    else
//        return(0);
    return(0);
}

void process_folder_or_ready_exe_in_rp(t_main *main)
{
    char *command;
    struct stat sb;
    int status_num;
//    int f;
    int d;
    char *message;

    command = main->job->pipe->redir->command;
    status_num = stat(command, &sb);
//    f = exists(command); // checking for file is redundant
    d = check_dir(command);
    if (ft_strchr(command, '/'))
    {
        if (d == 2 && status_num == -1) // no entry to dir (non existent), no file, no status
        {
            main->flag2 = 1;
            ft_putstr_fd("minishell: ", 1);
            ft_putstr_fd(command, 1);
            ft_putstr_fd(": No such file or directory\n", 1);
            main->exit = 127;
            strerror(main->exit);
        } else if ((sb.st_mode & S_IFMT) == S_IFDIR)//directory present in the local directory
        {
            main->flag2 = 1;
            ft_putstr_fd("minishell: ", 1);
            ft_putstr_fd(command, 1);
            ft_putstr_fd(": is a directory\n", 1);
            main->exit = 126;
            strerror(main->exit);
        } else if (status_num < 0 && d == 3)  // dir exists but can not be entered
        {
            message = strerror(errno);
            main->flag2 = 1;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(command, 2);
            ft_putchar_fd(' ', 2);
            ft_putstr_fd(message, 2);
            ft_putchar_fd('\n', 2);
            main->exit = 126;
        } else if ((sb.st_mode & S_IFMT) == S_IFREG)// clean command
            main->flag2 = process_ready_exe_in_rp(main);
    }
}



void process_builtins_and_divide_externals_in_rp(t_main *main)
{
    int flag;

    flag = process_buildins(main);
    process_folder_or_ready_exe_in_rp(main);
    if (main->flag2 != 1 && flag == 0)// flag2 = 0: no folder or ready_exe detected, flag = 0: builtins not found
        process_exe_in_rp(main);
    main->flag2 = 0;
}