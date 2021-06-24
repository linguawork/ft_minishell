#include "minishell.h"

char	*ft_getenv(t_main *main, char *name)
{
    int		len;
    int		i;
    char	*name_or_value;

    i = 0;
    while (main->my_env[i++] != NULL)
    {
        if (ft_strchr(main->my_env[i], '='))
        {
            len= char_count(main->my_env[i]);
            name_or_value = ft_substr(main->my_env[i], 0, len);
            if(ft_strcmp(name_or_value, name) != 0)
                free(name_or_value);
            if(ft_strcmp(name_or_value, name) == 0)
            {
                free(name_or_value);
                name_or_value = ft_strchr(main->my_env[i], '=')+1;
                return(name_or_value);
            }
        }
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