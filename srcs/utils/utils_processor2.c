#include "minishell.h"

int count_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return(i);
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