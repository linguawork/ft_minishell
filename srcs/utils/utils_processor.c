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