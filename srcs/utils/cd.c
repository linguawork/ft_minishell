#include "minishell.h"

char *ft_getenv(t_main *main, char *name)
{
    char **env;
    int len;
    int i;
    char *name_or_value;

    env = main->my_env;
    i = 0;
    while (env[i] != NULL)
    {
        if(ft_strchr(env[i], '='))
        {
            len= char_count(env[i]); // замер до равно (длина строки до =)
            name_or_value = ft_substr(env[i], 0, len); // отрезать до равно получается en без равно
            if(ft_strcmp(name_or_value, name) != 0)// освобождаем если не нашли
                free(name_or_value);
            if(ft_strcmp(name_or_value, name) == 0)// сравнение без знаков равно
            {
                free(name_or_value);
                name_or_value = ft_strchr(env[i], '=')+1; // pointer marks the symbol in the string// all after =, including =str
                // +1 убирает знак "=
                // name_or_value = name_or_value + 1;
                // ft_putstr_fd(name_or_value, 1);
                // ft_putchar_fd('\n', 1);
                return(name_or_value);
            }
        }
        i++;
    }
    return(0);
}

int cd(t_main *main)
{
    char *p;

    if (main->job->pipe->redir->command && !main->job->pipe->redir->args)
    {
        p = ft_getenv(main, "HOME");
        if (p == NULL)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 1);
            main->exit = 1;
        }
        else
            chdir(p);
    }
    if (main->job->pipe->redir->command && main->job->pipe->redir->args)
    {
        p = *main->job->pipe->redir->args;
        if (chdir(p) < 0)
        {
            ft_putstr_fd("minishell: cd: ", 1);
            ft_putstr_fd(p, 1);
            ft_putstr_fd(": No such file or directory\n", 1);
            main->exit = 1;
        }
    }
    return(0);
}