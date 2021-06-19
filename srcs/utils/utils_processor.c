#include "minishell.h"

void    *ft_new_memory_alloc(void *p, size_t length)// не добавляет терминир ноль
{
	void	*result;

	result = (void *)malloc(sizeof(void *) * length);// создаем новую строку с новым размером
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

void	copy_env2(t_main *main, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	main->my_env = (char **)malloc(sizeof(char *) * (i + 1));// добавление + 1 довало утечку - убрал и утечек не было но стало сегаться
	// когда подаю аргументы в экспорт После того как снова прибавил +1 сега исчезла (сегу находил с помощью санитайзера)
	if (!main->my_env)
		exit_with_error(main, ERROR_MALLOC);
	main->my_env[i] = NULL;
	while (--i >= 0)
	{
		main->my_env[i] = ft_strdup(env[i]);
		free(env[i]); // освобождение в цикле чтобы убрать утечки
		if (!main->my_env[i])
			exit_with_error(main, ERROR_MALLOC);
	}
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