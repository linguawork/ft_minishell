#include "minishell.h"

int check_string_to_eraze2(t_main *main, char **args, char **en)// проверка наличия переменных без знака =
{
    int i;
    int len;

    // len = how_many_lines(en);
    // printf("Before___%d\n", len);
    i = 0;
    while (en[i] != NULL)
    {
        if(!(ft_strchr(*args, '=')) && !(ft_strchr(en[i], '=')) )
        {
            if(ft_strcmp(*args, en[i]) == 0)// сравнение без знаков равно
            {
                free(en[i]);
                while(en[i])
                {
                    en[i] = en[i+1]; // смещаем указатель на следующий для всех элемнтов после того как я зафришил
                    i++;
                }
                while(en[i])
                    i--;// смещаем указатель на следующий для всех элемнтов после того как я зафриши
                len = how_many_lines(en);
                copy_env2(main, en);
                free(*args);
                return(1);
            }
        }
        i++;
    }
    return(0);
}

int check_string_to_eraze(t_main *main, char **args, char **en)// проверка наличия переменных env со знаком =
{
    char *name;
    int len;
    int i;
//	char **temp;

    i = 0;
    while (en[i] != NULL)
    {
        if(!(ft_strchr(*args, '=')) && (ft_strchr(en[i], '=')) ) // аргумент без знака =
        {
            len= char_count(en[i]); // замер до равно (длина строки до =)
            name = ft_substr(en[i], 0, len); // отрезать до равно получается en без равно
            if(ft_strcmp(*args, name) != 0)
                free(name);
            if(ft_strcmp(*args, name) == 0)// сравнение без знаков равно
            {
                // len = how_many_lines(en);//для проверки
                // printf("before-->%d", len);
                free(en[i]);
                while(en[i])
                {
                    en[i] = en[i+1]; // смещаем указатель на следующий для всех элемнтов после того как я зафришил
                    i++;
                }
                while(en[i])
                    i--;// смещаем указатель на следующий для всех элемнтов после того как я зафриши
                len = how_many_lines(en);// переопределение лен (длина массива строк)
//				temp = ft_new_memory_alloc(en, len); // просто лен так как уменьшили на один элемент
//				 len = how_many_lines(temp);
                // printf("after-->%d", len);
                copy_env2(main, en);
                free (name);// зачистка утечки
                free(*args);//зачистка утечки (после выполнения след команды после unset)
                return(1);
            }
        }
        else
            return(0);
        i++;
    }
    // if (name)
    // 	free(name);

    return(0);
}

int checker2 (t_main *main, char **a, char **e)
{
    if ((check_string_to_eraze(main,a,e) == 1) || (check_string_to_eraze2(main, a, e) == 1))
        return(1);
    else
        return(0);
}

int check_args_unset(t_main *main, char **a)
{
    char invalid_char_str[6] = {'=','-','+',',','.',':'};
    int i;

    if (ft_strchr (*a, '_')) // допустимый символ в аргументе
        return(0);
    i = 0;
    while(invalid_char_str[i])
    {
        if (!ft_isalpha(*a[0]) || (ft_strchr(*a, invalid_char_str[i]))) // если первый  символ не буква то сообщение об ошибке
        {
            ft_putstr_fd ("minishell: ", 1);
            ft_putstr_fd (main->job->pipe->redir->command, 1);
            ft_putstr_fd (": `", 1);
            ft_putstr_fd (*a, 1);
            ft_putstr_fd ("': not a valid identifier", 1); // sega
            ft_putchar_fd ('\n', 1);
            return(1);
        }
        i++;
    }
    return(0);
}

int unset(t_main *main)
{
    char *command;
    char **args;
    char **envir;
    int flag;

    command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
    // envir = main->my_env;


    while (command && args && *args != NULL)
    {
        flag = check_args_unset(main, args);
        if(flag == 1)
            free(*args);
        if (flag != 1)
        {
            envir = env_recorder(main);
            checker2 (main, args, envir);
        }
        // if(checker2 (args, envir)== 1)
        // 	copy_env3(main, envir);
        args++;
    }
    // while (*envir != NULL)
    // {
    // 	printf("%s", *envir);
    // 	envir++;
    // }
    return(0);
}