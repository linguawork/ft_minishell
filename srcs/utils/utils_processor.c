#include "minishell.h"

char    **ft_new_memory_alloc(void *p, size_t length)// не добавляет терминир ноль
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * length);// создаем новую строку с новым размером
	if (!result)
		return(NULL);
	else
	{
		ft_memset(result, '\0', length);// заполнение нулями на всю длину
		ft_memcpy(result, p, length);// копируем поданную строку в новую
	}
	free(p);
	return (result);
}

//void	copy_env2(t_main *main, char **env)
//{
//	int i;
//
//	i = 0;
//	while (env[i])
//		i++;
//	main->my_env = (char **)malloc(sizeof(char *) * (i + 1));// добавление + 1 довало утечку - убрал и утечек не было но стало сегаться
//	// когда подаю аргументы в экспорт После того как снова прибавил +1 сега исчезла (сегу находил с помощью санитайзера)
//	if (!main->my_env)
//		exit_with_error(main, ERROR_MALLOC);
//	main->my_env[i] = NULL;
//	while (--i >= 0)
//	{
//		main->my_env[i] = ft_strdup(env[i]);
//		free(env[i]); // освобождение в цикле чтобы убрать утечки
//		if (!main->my_env[i])
//			exit_with_error(main, ERROR_MALLOC);
//	}
//}

void	copy_env2(t_main *main, char **env)
{
    int i;
    int len;

    i = -1;
    len = how_many_lines(env);
    free(main->my_env);
    main->my_env = (char **)malloc(sizeof(char *) * (len + 1));// добавление + 1 довало утечку - убрал и утечек не было но стало сегаться
    // когда подаю аргументы в экспорт После того как снова прибавил +1 сега исчезла (сегу находил с помощью санитайзера)
    if (!main->my_env)
        exit_with_error(main, ERROR_MALLOC);
    while (++i < len)
    {
        main->my_env[i] = env[i];
//        free(env[i]); // освобождение в цикле чтобы убрать утечки
        if (!main->my_env[i])
            exit_with_error(main, ERROR_MALLOC);
    }
//    free(env);
    main->my_env[i] = NULL;
}

char** cmd_args_to_argv_recorder(t_main *main) // запись аргументов в 2мер массив
{
    char **e;
    int length;
	char **a;
	char *cmd;
	cmd = main->job->pipe->redir->command;
	a = main->job->pipe->redir->args;
	int i = 1;
	int j = 0;
	if (a == NULL)// если аргумент всего 1 (то это сама команда) то пишем его в массив env и 1 ячейку резерв для терминатора
	{
		e = (char **) malloc(sizeof(char *) * (1 + 1));
		e[0] = cmd;
	}
	else// если аргументов не один
	{
		length = how_many_lines((char **) a);// считаем кол-во аргументов
		e = (char **) malloc(sizeof(char *) * (length + 1+1)); // выделяем память + 1 для ноля и +1 для команды
		e[0] = cmd;
		while (a[j] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала после записи команды
		{
			e[i] = a[j];// лучше записывать через индекс// i = 1 так как в ноль записана команда, j = 0
			j++;
			i++;
		}
	}
	e[i]=NULL;// в конце добав терминатор
    return(e);
}

//int check_doubles2(char **args, char **en)
//{
//    char *a_name;
//    int len;
//    char *e_name;
//    int len2;
//
//
//    len = char_count(*e);
//    value1 = (ft_strchr(*e, ('='))); // pointer marks the symbol in the string// all after =, including =str
//    value = value1 + 1;//отрубаю после знака равно строку значения// пропускаем знак = через +1
//    write(1, *e, len);// пишем до знака равно
//    ft_putchar_fd('=', 1); // дописываем
//    ft_putchar_fd('\"', 1); //
//    ft_putstr_fd(value, 1); //
//    ft_putchar_fd('\"', 1); //
//
//    while (*en != NULL)
//    {
//        if(ft_strcmp(*args, *en) == 0)
//            return(1);
//        else if((ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
//        {
//            a_name =
//
//
//
//            len= char_count(*args); // замер до равно
//            a_name = ft_substr(*args, 0, len); // отрезать до равно получается арг без равно
//            if (ft_strcmp(a_name, *en) != 0) // полное несоответствие строк до знака = и освобождение указателя
//                free(a_name);
//            if(ft_strcmp(a_name, *en) == 0) // сравнение без знаков равно
//            {
//                free(*en);
//                *en =ft_strdup(*args);
//                free(a_name);
//                return(1);
//            }
//        }
//        else if((ft_strchr(*args, '=')) && (ft_strchr(*en, '='))) // если и арг и env со знаком =
//        {
//            len= char_count(*args);
//            len2 = char_count(*en);
//            a_name = ft_substr(*args, 0, len); // получ арг до знака равно
//            e_name = ft_substr(*en, 0, len2); // получ env до знака равно
//            if (ft_strcmp(a_name, e_name) != 0) // полное соответствие строк до знака =
//            {
//                free(e_name);
//                free(a_name);
//            }
//            if (ft_strcmp(a_name, e_name) == 0) // полное соответствие строк до знака =
//            {
//                free(*en);
//                *en =ft_strdup(*args);// перезапись
//                free(a_name);
//                free(e_name);
//                return(1);
//            }
//        }
//        else if(!(ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
//        {
//            if(ft_strcmp(*args, *en) == 0) // полное соответствие строк без знака =
//                return(1);
//        }
//        else if(!(ft_strchr(*args, '=')) && (ft_strchr(*en, '=')))
//        {
//            len= char_count(*en); // переопределение и замер до равно
//            e_name = ft_substr(*en, 0, len); // отрезать до равно получается en без равно
//            // e_name = read_name(*en);
//            if (ft_strcmp(*args, e_name) != 0) // полное соответствие строк до знака =
//                free(e_name);
//            if(ft_strcmp(*args, e_name) == 0)// сравнение без знаков равно
//            {
//                free(e_name);
//                return(1);
//            }
//        }
//        en++;
//    }
//
//    return(0);
//}