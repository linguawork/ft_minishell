#include "minishell.h"

// предлагаю использовать указатель на структуру
int count_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return(i);
}

int how_many_lines(char **a)
{
    int i;
    char **env;

    i = 0;
    env = a;
    while(env[i])
    {
        i++;
    }
    return(i);
}

int echo(t_main *main) // работает с костылем флага в init shell
{
	char *command;
	char **args;
	char *flags;

	command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
	flags = main->job->pipe->redir->flags;
	if (command != '\0')
	{
	    if (command && !flags && !args)// при подаче просто команды echo без аргументов не заходит
		// если я пишу в условии !args тогда заходит, но нам нужно разыменование как во флагах
            fputc('\n', stdout);
	    if (command && flags && !(args))
        {
            if (command && ft_strncmp(flags, "-n", 2) == 0)
                return (1);
        }
        if (command && !flags && args)
        {
            if (command && args)
            {
//                fputs(*args, stdout);
//                printf("here");
                write(1, *args, ft_strlen(*args));
                while (*++args)
                {
                    write(1, " ", 1);
                    write(1, *args, ft_strlen(*args));

//                    fputc(' ', stdout);
//                    fputs(*args, stdout);
                }
                write(1, "\n", 1);
            }
        }
	}

	return(0);
}

int cd(t_main *main)
{
	char *command;// функция отрабатывает, но прога завершается и просходит возврат директорию программы
	char **args;
	char *flags;

	// pwd(main); //проверка для отработки cd
	const char *p;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	flags = main->job->pipe->redir->flags;

	if (args)
	{
		// printf("testing args\n");
		p = *args;
		// printf("%s", args[0]);
		chdir(p);
		// printf("%s\n", p);
		// pwd (main); //проверка для отработки cd
	}
	else
	{
		p = getenv("HOME");
		// printf("no args"); //проверка отработки условия
		if (p == NULL)
		{
			printf("There is no HOME env var\n");
		}
		// else
		// {
		// 	chdir(p);
		// 	pwd (command, flags); //проверка для отработки cd
		// }
	}
	// if (chdir(p) < 0) // это условие я отключил на период пока не запускаем в цикле потом можно включить
	// {
	// 	perror(p);
	// 	return(1);
	// }
	return(0);
}

int pwd(t_main *main)
{
	char *command;
	char *flags;
	command = main->job->pipe->redir->command;
	flags = main->job->pipe->redir->flags;
	char buffer[1024];

	// if (*flags != NULL) // по сабжекту не нужно отрабатывать аргументы
	// 	{
	// 		printf("Too many arguments\n");
	// 		return(1);
	// 	}
	if (getcwd(buffer, 1024) == NULL)
	{
		printf("Could not get current working directory\n");
	}
	printf("%s\n", buffer);
	return(0);
}

int exit_command(t_main *main)
{

	char *flags;
	char *cmd;

	flags = main->job->pipe->redir->flags;
    cmd = main->job->pipe->redir->command;

    cmd = NULL; // чтобы не выводил по команде exit содержание command

	if (flags != NULL )
		exit(1);
	exit(1);
}

int check_equal_sign_for_env(t_main *main)
{
    int i;
    int j;
    char **env;

    env = main->my_env;
    i = 0;
    while(env[i] != NULL)
    {
        j = 0;
        while (env[i][j] != '\0')
        {
            if (env[i][j] == '=')
            {
                return (1);
                break;
            }
            j++;
        }
        i++;
    }
    return(0);
}

int env(t_main *main)
{
	char *command;
	// char **args;// комманда env по сабджекту подается без аргументов и флагов
	char **envir;
	int len;
//	int flag;
	int i;
	int j;

	command = main->job->pipe->redir->command;
	// args = main->job->pipe->redir->args;
	envir = main->my_env;

    len= how_many_lines(envir);//  Длина у меня уже увеличилась на один в функции realloc
    printf("export--->%d\n", len); // проверка длины после
//    flag = check_equal_sign_for_env(main);
	//if ((command && !args))// комманда env по сабджекту подается без аргументов и флагов
	if (command)
	{
	    j = 0;
	    i = 0;
		while(envir[i])
		{
//		    if (flag == 1)

//            while (envir[i][j] != '\0')
//            {
//                if (ft_strchr("=", envir[i][j]))
//                {
//                    printf("--->%s\n", envir[i]);
//                    i++;
//                }
////                if (!(ft_strchr("=", envir[i][j])))
////                    i++;
//                j++;
//            }
            if (ft_strchr(envir[i], '='))
                printf("%s\n", envir[i]);
            i++;
		}

	}
	return(0);
}

void	double_for_sort_algo(char **envir, int size)
{
    char *tmp;
    int i;
    int j;

    i = -1; //если начать с нуля то TMPDIR выводится первым
    while (++i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (ft_strcmp(envir[i], envir[j]) > 0)
            {
                tmp = envir[i];
                envir[i] = envir[j];
                envir[j] = tmp;
            }
//            if (ft_strcmp(envir[i], envir[j]) <= 0)
//			    return;
            j++;
        }
    }
}

void	*arrays_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

void put_quotes_in_str(t_main *main)
{
	char **splitstr;
	char *str;
	int strlen;
    char **args;

	args = main->job->pipe->redir->args;
	strlen = ft_strlen(*args);
	str = (char *)malloc(sizeof(char*)*(strlen + 3));

	str[0] = 0;
	splitstr = ft_split(*args,'=');// можно в одинарных (это инт и он символ)
	strcpy(str, splitstr[0]);//написать свою функцию
	strcat(str, "=");//написать свою функцию
	strcat(str,"\"");// нельзя в одинарных (это инт) в двойных это char pointer
	strcat(str, splitstr[1]);
	strcat(str,"\"");// нельзя в одинарных (это инт) в двойных это char pointer
	*args = str;
	// printf("___%s\n", *args);
	// free(str);
	arrays_free(splitstr);
}

void put_quotes_in_no_str(t_main *main)
{
	// char **splitstr;
	char *str;
	int strlen;
	char **args;

	args = main->job->pipe->redir->args;
	strlen = ft_strlen(*args);
	str = (char *)malloc(sizeof(char*)*(strlen + 3));

	str[0] = 0;
	// splitstr = ft_split(*args,'=');// можно в одинарных (это инт и он символ)
	strcpy(str, *args);
	// strcat(str, "=");
	strcat(str,"\"\"");// нельзя в одинарных (это инт) в двойных это char pointer
	*args = str;
	printf("__%s\n", *args);
	// free(str);
}

void check_equal_sign_add_quotes(t_main *main)
{
	int i;
	int j;
	char **args;

	args = main->job->pipe->redir->args;
	i = 0;
	while(args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '=' && args[i][j+1] != 0)
				put_quotes_in_str(main);
			else if (args[i][j] == '=' && args[i][j + 1] == 0)
				put_quotes_in_no_str(main);
			++j;
		}
		++i;
	}
}



void change_value(t_main *main)
{
	char **splitstr;
	char **splitenvir;
	// char *s;
	int i;
	int len;
	int len2;
	int flag;
	char **args;
	char **envir;

	envir = main->my_env;
	args = main->job->pipe->redir->args;
	// s[0] = 0;
	flag = 0;
	i = 0;
	splitstr = ft_split(*args,'=');// можно в одинарных (это инт и он символ)
	// strcpy(s, splitstr[0]); // пока сделаем без маллока
	// strcat(s, "=");
	len = ft_strlen(splitstr[0]);// длина имени для сравнения в strncmp
	len2 = ft_strlen(splitstr[1]);// длина хвоста аргумента
	while(envir[i])
	{
		// printf("%s ||| %s\n", );
		// if (strncmp(envir[i], splitstr[0], 4) == 0)
		// 	printf("OKEY\n");
		if (flag == 0 && ft_strncmp(envir[i], splitstr[0], len) == 0) // сравнение аргумента до знака равно но без знака равно
		{
			printf("inside\n");
			splitenvir = ft_split(envir[i], '=');
			free((void *)envir[i]); //переназначение типа (так как free требует  void*)
			envir[i] = (char *)malloc(sizeof(char*)*(len +1 + len2 + 1)); // выделение памяти под длину имени и хвостоа
			strcpy((char *)envir[i], splitenvir[0]);// копия имени в выделенную память
			strcat((char *)envir[i], "="); // приклеивание =
			strcat((char *)envir[i], splitstr[1]); // приклеивание хвоста
			printf("%s\n", envir[i]);// проверка заполенения выделенной памяти
			arrays_free(splitstr);// освобождение отработанной строки
			flag = 1;// флаг чтобы не заходил больше одного раза
		}
		// printf("WTF\n%s\n", envir[i]);
		// while(envir[i])
		// {
		// 	printf("-->%s\n", envir[i]);
		// 	i++;
		// }
		i++;
	}
	// arrays_free(splitstr);
}

void check_duplicate_name(t_main *main)
{
	int i;
	int j;
	int flag;
	char **args;

	flag = 0;
	args = main->job->pipe->redir->args;
	i = 0;
	while(args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if ((args[i][j] == '=' && args[i][j+1] != 0) || \
			(args[i][j] == '=' && args[i][j + 1] == 0))
				change_value(main);
			++j;
		}
		++i;
	}
}

int char_count(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return(i);
}

void divider(t_main *main)
{
	char *name;
	char *value;
	char *s;
	int len;
	int len2;
	char **args;

	args = main->job->pipe->redir->args;
	len = char_count(*args); // длина имени до знака равно
	name = ft_substr(*args, 0, len);// отрубаю до знака равно имя
	value = ft_strdup(ft_strchr(*args, ('='+1)));//отрубаю после знака равно строку значения
	len2 = ft_strlen(value);// замер длина строки значения

	s = (char *)malloc(sizeof(char *)*(len+1 + len2+1+3)); // выделение памяти для новой строки
	s[0] = 0;

	
	strcpy(s, name); // пока сделаем без маллока
	strcat(s, "=");
	strcat(s, "\"");
	strcat(s, value);
	strcat(s, "\"");
	*args = s;
	free(s);
}

char** env_recorder(t_main *main)
{
    char **e;
    int length;

    length = how_many_lines((char **) main->my_env);
    e = (char **) malloc(sizeof(char *) * (length));

    int i = 0;
    while (main->my_env[i]) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
    {
        e[i] = main->my_env[i];// лучше записывать через индекс
        i++;
    }
    return(e);
}

int export(t_main *main)
{
    // 2021 05 22 20-31 export works with space
	char *command;
	char **args;
	char **envir;
	char *prefix;
	int len;
    int i;
    int j;

//	envir = main->my_env;
    envir = env_recorder(main);
    command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	prefix = "declare -x ";
	len = how_many_lines(envir);

	i = 0;

	if (command && !args)
	{

        len= how_many_lines(envir);//  Длина у меня уже увеличилась на один в функции realloc
        printf("export--->%d\n", len); // проверка длины после
        double_for_sort_algo(envir, len);
        if(ft_strncmp(envir[i], "declare -x", 10) == 0 && envir[i] != NULL)
        {
//            double_for_sort_algo(main, len);
            j = 0;
            while (envir[i])
            {
                if(envir[i][j+11] == 'd') // первая ячейка с нулевого элемента
                {
                    // printf("here");
                    // break ;
                    i++;
                    if(envir[i] == NULL)
                        return(1);
                }
                printf("%s\n", envir[i]);
                i++;
            }
        }
        else
        {
//            double_for_sort_algo(main, len);
            while( envir[i] != NULL)
            {
//                j = 0;
//                while(ft_strncmp(envir[i], "declare -x", 10) == 0) // здесь точное количество элементов счет с 1 не с 0
//                {
//
//                    if(envir[i][j+11] == 'd') // первая ячейка с нулевого элемента
//					{
//						// printf("here");
//                        // break ;
//						i++;
//						if(envir[i] == NULL)
//                    		return(1);
//					}
//					printf("%s\n", envir[i]);
//                    i++;
//                }
//                envir[i] = ft_strjoin(prefix, envir[i]);
                printf("%s", prefix);
                printf("%s\n", envir[i]);
               	if(envir[i] == NULL)
                       return(1);
                i++;
            }
        }
	}
	if (command && args)// условие != NULL дает сегу
	{

		// divider(args);
//		check_duplicate_name(main);
//		check_equal_sign_add_quotes(main);
        i = 0;// первый аргумент нулевой
        len= how_many_lines(envir);
//        double_for_sort_algo(main, len);// сортировка с новой длиной после добавления всех элементов
		while ( i >= 0 && args[i]) // в цикле реалок еще на один аргумент с каждым новым аргументом
		{
//			len= how_many_lines(envir);
//			printf("export+arg in->%d\n", len); // проверка длины до
			envir = ( char **)realloc(envir,(sizeof(char*)*(len + 2))); // обязательно нужно указывать на размер чего-то (в данном случае чаров)
			// printf("test%s\n", args[i]);
			envir[len] = args[i];// в выделенную ячейку добавляем аргумент по индексу длины рядов массива, ставим аргумент в конце массива
            envir[len + 1] = NULL; // сместили указатель на ноль по индексу длины рядов массива
//            printf("%s", prefix);
//            printf("%s\n", envir[i]);
//            envir[len] = ft_strjoin(prefix, envir[len]);// так как новый добавленный в конце аргумент не имеет префикса я его добавляю в конец и перезаписываю
			len++; //  Длина у меня уже увеличилась на один в функции realloc и не нужно прибавлять
			i++; // переход к следующему аргументу
//			len= how_many_lines(envir);//  Длина у меня уже увеличилась на один в функции realloc
//			printf("export+arg out--->%d\n", len); // проверка длины посл
		}
		copy_env(main, envir);
        double_for_sort_algo(envir, len);


//		double_for_sort_algo(main, len);// сортировка с новой длиной после добавления всех элементов
//        i = 0;
//		while(envir[i])
//		{
//			envir[i] = ft_strjoin(prefix, envir[i]);
//			printf("%s\n", envir[i]);
//			i++;
//		}
//		printf("inside");
        arrays_free(envir);
	}
	return(0);
}

void process_builtins_and_divide_externals(t_main *main)
{
	char *command;

	command = main->job->pipe->redir->command;
	if (ft_strncmp(command, "echo", 4) == 0)
		echo(main);
	else if (ft_strncmp(command, "cd", 2) == 0)
		cd(main);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		pwd(main);
	else if(ft_strncmp(command, "export", 6) == 0)
		export(main);
	else if(ft_strncmp(command, "unset", 5) == 0)
		printf("unset\n");
	else if(ft_strncmp(command, "env", 3) == 0)
		env(main);
	else if(ft_strncmp(command, "exit", 4) == 0)
		exit_command(main);
	else
		process_externals(main);
}

void process_externals(t_main *main)
{
	char *command; 

	command = main->job->pipe->redir->command;

	printf("%s", command);
}


