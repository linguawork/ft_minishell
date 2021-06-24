#include "minishell.h"

void	copy_env3(t_main *main, char **env)
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
        main->my_env[i] = ft_strdup(env[i]);
        free(env[i]); // освобождение в цикле чтобы убрать утечки
        if (!main->my_env[i])
            exit_with_error(main, ERROR_MALLOC);
    }
    main->my_env[i] = NULL;
}

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
        main->my_env[i] = ft_strdup(env[i]);
        free(env[i]); // освобождение в цикле чтобы убрать утечки
        if (!main->my_env[i])
            exit_with_error(main, ERROR_MALLOC);
    }
    free(env);
    main->my_env[i] = NULL;
}
