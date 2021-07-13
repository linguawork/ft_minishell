#include "minishell.h"

int redir_two_left(t_main *main)
{
    int fd[2];
    t_redir *redir;
    char str[ft_strlen(main->job->pipe->redir->redir_file) + 1];
    int len;
    int fork_res;
    char *cmd;

    redir = main->job->pipe->redir;
    cmd = redir->command;
    if (redir && redir->redir_next == NULL) // если есть структура redir - одна команда  один редирект и один файл
    {
        if ((redir->command && redir->redir_type == INPUT_MULTILINE &&
            redir->redir_file) && ft_strcmp (redir->command, "cat") == 0)// команда и редирект тип >> и файл
        {
            if (pipe(fd) == -1)
                return (1);
            fork_res = fork();
            if (fork_res == -1)
                return (2);
            if (fork_res == 0)
            {
                close(fd[0]);
                ft_putstr_fd(redir->redir_file, 0);
                redir->redir_file[ft_strlen(redir->redir_file) - 1] = '\0';
                len = ft_strlen(redir->redir_file) + 1;
                if (write(fd[1], &len, sizeof(int)) < 0)
                    return 3;
                if (write(fd[1], &redir->redir_file, sizeof(char) * len) < 0)
                    return 4;
                close(fd[1]);
            }
            else
            {
                close(fd[1]);
                if (read(fd[0], &len, sizeof(int)) < 0)
                    return 5;
                if (read(fd[0], &str, sizeof(int) * len) < 0)
                    return 6;
                ft_putchar_fd('\n', 1);
                close(fd[0]);
                wait(NULL);
            }
        }
        if (!(ft_strcmp (redir->command, "cat") == 0))
            process_builtins_and_divide_externals(main);
    }
    while (redir && redir->redir_next != NULL) // если редир > 1
        redir = redir->redir_next;
    if ((!redir->command && redir->redir_type == INPUT_MULTILINE &&
        redir->redir_file && redir->redir_next == NULL) && ft_strcmp (cmd, "cat") == 0)// команда и редирект тип >> и файл
    {
        if (pipe(fd) == -1)
            return (1);
        fork_res = fork();
        if (fork_res == -1)
            return (2);
        if (fork_res == 0)
        {
            close(fd[0]);
            ft_putstr_fd(redir->redir_file, 0);
            redir->redir_file[ft_strlen(redir->redir_file) - 1] = '\0';
            len = ft_strlen(redir->redir_file) + 1;
            if (write(fd[1], &len, sizeof(int)) < 0)
                return 3;
            if (write(fd[1], &redir->redir_file, sizeof(char) * len) < 0)
                return 4;
            close(fd[1]);
        }
        else
        {
            close(fd[1]);
            if (read(fd[0], &len, sizeof(int)) < 0)
                return 5;
            if (read(fd[0], &str, sizeof(int) * len) < 0)
                return 6;
            ft_putchar_fd('\n', 1);
            close(fd[0]);
            wait(NULL);
        }
    }
    if (!(ft_strcmp (redir->command, "cat") == 0))
            process_builtins_and_divide_externals(main);
    cmd = NULL;
    redir->command = NULL;
    return (0);
}
