/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: areggie <areggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:07:49 by areggie           #+#    #+#             */
/*   Updated: 2021/07/18 18:07:52 by areggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_folder_in_pipes(t_main *main, char **cmd)
{
    char *command;
    struct stat sb;
    int status_num;
//    int f;
    int d;
    char *message;

    command = cmd[0];
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
        }
        else if ((sb.st_mode & S_IFMT) == S_IFDIR)//directory present in the local directory
        {
            main->flag2 = 1;
            ft_putstr_fd("minishell: ", 1);
            ft_putstr_fd(command, 1);
            ft_putstr_fd(": is a directory\n", 1);
            main->exit = 126;
            strerror(main->exit);
        }
        else if (status_num < 0 && d == 3)  // dir exists but can not be entered
        {
            main->flag2 = 1;
            message = strerror(errno);
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(command, 2);
            ft_putchar_fd(' ', 2);
            ft_putstr_fd(message, 2);
            ft_putchar_fd('\n', 2);
            main->exit = 126;
        }
//        else if ((sb.st_mode & S_IFMT) == S_IFREG)// clean command
//            process_exe_in_pipes(main, cmd);
    }
}