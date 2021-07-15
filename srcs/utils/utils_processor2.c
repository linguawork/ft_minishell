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