#include "minishell.h"

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
    while(env[i] != NULL)
    {
        i++;
    }
    return(i);
}

int echo(t_main *main)
{
	char *command;
	char **args;
//	char **dup_args;

	command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
//    dup_args = args;
    main->exit = 0;
	if (command)
	{
        if (!args)
            ft_putchar_fd('\n', 1);
        if (args)
        {
            if (ft_strcmp(*args, "-n") == 0)
            {
                while (*args != NULL && (ft_strcmp(*args, "-n") == 0))
                    args++;
                if (*args == NULL)
                    return (0);
                write(1, *args, ft_strlen(*args));
                while (*++args != NULL)
                {
                    ft_putchar_fd(' ', 1);
                    write(1, *args, ft_strlen(*args));
                }
            }
            else
            {
                while (*args != NULL)
                {
                    ft_putstr_fd(*args, 1);
                    ft_putchar_fd(' ', 1);
                    args++;
                }
                ft_putchar_fd('\n', 1);
            }
        }
    }// here we need to free leaks after working
	return(0);
}


int pwd(t_main *main)
{
	char *command;
	char buffer[1024];

	//$? = 0; это у нас инициализовано в init_shell там main->exit = 0
	command = main->job->pipe->redir->command;
	if (getcwd(buffer, 1024) == NULL)
	{
		main->exit = 1;
		printf("Could not get current working directory\n");
	}
	printf("%s\n", buffer);
	return(0);
}

void	process_valid_args( char **s)
{
	char	*str;
	int		i;
	
	str = *s;
	i = 0;
	while (str[i] != '\0' )
	{	
		if(!ft_isdigit(str[i]) && ft_isascii(str[i]) )
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd(": numeric argument required", 1);
			exit((unsigned char) -1);//кастануть чтобы выдать 255
		}
		i++;
	}
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

int exit_command(t_main *main)
{
	char *cmd;
	char ** args;
	int i;

	args = main->job->pipe->redir->args;
    cmd = main->job->pipe->redir->command;
	i = 0;
	if (cmd && !args)
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS); // выход с кодом 0
	}
	if (cmd && args[i] && !args[i+1]) // если один аргумент
	{
		if ((*args[0] == '-' && ft_strncmp(*args,"--", 2) != 0 && ft_strncmp(*args,"-+", 2) != 0)||
		(*args[0] == '+' && ft_strncmp(*args,"++", 2) != 0 && ft_strncmp(*args,"+-", 2) != 0))
		{
			ft_putstr_fd("exit\n", 1);
			exit((unsigned char) ft_atoi(*args));// кастануть чтобы выдать 255
		}
		else
			process_valid_args(args); // проверка на цифры в аргументе с выводом ошибки //и сохранением в структуру чтобы можно было вызвать через $?
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(*args));// выход только с цифрами в аргументе (аргумент можно записать в main->exit) они будут выводится через $?
	 	// если подавать в аргумент цифру >256 то система дает остаток от деления на 256
	}	
	if ((cmd && args[i] && args[i+1])) // если много аргументов
	{
			process_valid_args(args);
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 1);
			exit(main->exit = 1);
	}
	// sleep(1000);// for test leaks
	return(0);
}

int env(t_main *main)
{
	char *command;
	char **envir;
	int len;
	int i;
	int j;

	command = main->job->pipe->redir->command;
	envir = main->my_env;
    len= how_many_lines(envir);//  Длина у меня уже увеличилась на один в функции realloc
    // printf("export--->%d\n", len); // проверка кол-ва строк в массиве
	if (command)
	{
	    j = 0;
	    i = 0;
		while(envir[i])
		{
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

int char_count(const char *str)
{
	int i;

	i = 0;
	if (!(ft_strchr(str, '=')))
		return(0);
	else
	{
		while (str[i] != '=')
		{
			i++;
		}
	}
	return(i);
}

void put_da_brackets( char **e)
{
	char *value1;
	char *value;
	int len;

	len = char_count(*e);
	value1 = (ft_strchr(*e, ('='))); // pointer marks the symbol in the string// all after =, including =str
	value = value1 + 1;//отрубаю после знака равно строку значения// пропускаем знак = через +1
	write(1, *e, len);// пишем до знака равно
	ft_putchar_fd('=', 1); // дописываем
	ft_putchar_fd('\"', 1); //
	ft_putstr_fd(value, 1); //
	ft_putchar_fd('\"', 1); //
}

char** env_recorder(t_main *main)
{
    char **e;
    int length;

    length = how_many_lines(main->my_env);
    e = (char **) malloc(sizeof(char *) * (length + 1));

    int i = 0;
    while (main->my_env[i] != NULL) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
    {
        e[i] = main->my_env[i];// лучше записывать через индекс
        i++;
    }
	e[i]=NULL;
    return(e);
}

char** env_recorder2(char **envir, int len)
{
    char **e;

    e = (char **) malloc(sizeof(char *) * (len + 2));

    int i = 0;
    while (envir[i] && i != len) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
    {
        e[i] = envir[i];// лучше записывать через индекс
        i++;
    }
//    e[len] = envir[i++];
//    e[len+1]=NULL;
    return(e);
}


// recent version
int check_doubles(t_main *main, char **args, char **en)
{
	char *a_name;
	int len;
	char *e_name;
	int len2;

	while (*en != NULL)
	{
		if(ft_strcmp(*args, *en) == 0)
			return(1);
		else if((ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
		{
			len= char_count(*args); // замер до равно
			a_name = ft_substr(*args, 0, len); // отрезать до равно получается арг без равно
			if (ft_strcmp(a_name, *en) != 0) // полное несоответствие строк до знака = и освобождение указателя
				free(a_name);
			if(ft_strcmp(a_name, *en) == 0) // сравнение без знаков равно
			{
				free(*en);
				*en =ft_strdup(*args);
                free(*args);// убрал утечку после исполнения команды
				free(a_name);
                main->sub = 1;
				return(1);
			}
		}
		else if((ft_strchr(*args, '=')) && (ft_strchr(*en, '='))) // если и арг и env со знаком =
		{
			len= char_count(*args);
			len2 = char_count(*en);
			a_name = ft_substr(*args, 0, len); // получ арг до знака равно
			e_name = ft_substr(*en, 0, len2); // получ env до знака равно
			if (ft_strcmp(a_name, e_name) != 0) // полное соответствие строк до знака =
			{
					free(e_name);
					free(a_name);
			}
			if (ft_strcmp(a_name, e_name) == 0) // полное соответствие строк до знака =
			{
				free(*en);
				*en =ft_strdup(*args);// перезапись
				free(*args);// убрал утечку после исполнения команды
				free(a_name);
				free(e_name);
				main->sub = 1;
				return(1);
			}
		}
		else if(!(ft_strchr(*args, '=')) && !(ft_strchr(*en, '=')))
		{
			if(ft_strcmp(*args, *en) == 0) // полное соответствие строк без знака =
				return(1);
		}
		else if(!(ft_strchr(*args, '=')) && (ft_strchr(*en, '=')))
		{
			len= char_count(*en); // переопределение и замер до равно
			e_name = ft_substr(*en, 0, len); // отрезать до равно получается en без равно
			// e_name = read_name(*en);
			if (strcmp(*args, e_name) != 0) // полное соответствие строк до знака =
				free(e_name);
			if(strcmp(*args, e_name) == 0)// сравнение без знаков равно
			{
				free(e_name);
				return(1);
			}
		}
		en++;
	}
	return(0);
}

int checker (t_main *main, char **a, char **e)
{
	if (check_doubles(main, a, e) == 1)
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

void check_args(t_main *main, char **a)
{
    char invalid_char_str[5] = {'-','+',',','.',':'};
    int i;

    if (ft_strchr (*a, '_')) // допустимый символ в аргументе
        return;
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
            main->flag2 = 1;
            break;
        }
        i++;
    }
}

int export(t_main *main)
{
	char *command;
	char **args;
	char **envir;
	int len;
    int i;
	int flag;

    envir = env_recorder(main);// копия чтобы в env не было алфавитного порядка, утечки были и я их убрал
    command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	
	len = how_many_lines(envir);
	i = 0;
	if (command && !args)
	{	
        // len= how_many_lines(envir);// Длина у меня уже увеличилась на один в функции realloc
        // printf("export--->%d\n", len); // проверка длины после
		double_for_sort_algo(envir, len);
		while( envir[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			if (!(ft_strchr(envir[i], '=')))// печать строки без знака =
			{
				ft_putstr_fd(envir[i], 1);
				ft_putchar_fd('\n', 1);
			}
			else // печать строки со знаком =
			{
				put_da_brackets(&envir[i]);// ставим кавычки
				ft_putchar_fd('\n', 1);
			}
			if(envir[i] == NULL)
					return(1);
			i++;
		}
		free(envir);// убирает только основной массив подмассивы не трогаем иначе теряются указатели на подстроки
	}
	else
	{

            char **e;
			flag = 0;
			i = 0;// первый аргумент нулевой
			len = how_many_lines(envir);
			// sleep(5);
			// printf("here\n");
			while (args[i] != NULL)// в цикле реалок еще на один аргумент с каждым новым аргументом
			{
			    if (i > 0)
                    envir = env_recorder(main);
				check_args(main, &args[i]);// проверка на допустимые символы
				flag = checker(main, &args[i], envir);
				if ((flag != 1) && (main->flag2 != 1))
				{
                    e = env_recorder2(envir,len); //перезапись на лен +2
				    e[len] = args[i];// в выделенную ячейку добавляем аргумент по индексу длины рядов массива, ставим аргумент в конце массива
				    e[len + 1] = NULL; //сместили указатель на ноль по индексу длины рядов массива
				    len++; //Длина у меня уже увеличилась на один в функции realloc и не нужно прибавлят
				}
				if (flag == 1 && main->sub == 1)
				{
                    copy_env3(main, envir);
                    main->sub = 0;
                }
                if ((flag != 1) && (main->flag2 != 1))
                    copy_env2(main, e);
                free(envir);
				flag = 0;
                main->flag2 = 0;
				i++; //переход к следующему аргументу
			}
//		copy_env2(main, e);
//        free(envir);
//        free(e);
	}
	// arrays_free(envir);
	// sleep(1000);// for test leaks
	return(0);
}

int checker2 (t_main *main, char **a, char **e)
{
	if ((check_string_to_eraze(main,a,e) == 1) || (check_string_to_eraze2(main, a, e) == 1))
		return(1);
	else
		return(0);
}

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

int process_ready_exe(t_main *main)
{
	char *command;
	char **args;
	char **envir;
	int fork_res;
	char **argv;
    int status;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	envir = main->my_env;
    status = 0;

    argv = cmd_args_to_argv_recorder2(main);
    fork_res = fork();
    if (fork_res == 0)
        execve(command, argv, envir);
    if (fork_res > 0)
    {
        waitpid(fork_res, &status, 0);
        main->exit = WEXITSTATUS(status);
    }
    // for testing
//    ft_putstr_fd("status number is ", 1);
//    ft_putnbr_fd(status, 1);
//    ft_putnbr_fd (WEXITSTATUS(status), 1); // запись кода выхода 1
//    write(1, "\n", 1);
//    ft_putstr_fd("main_>exit is ", 1);
//    ft_putnbr_fd (main->exit, 1);
//    write(1, "\n", 1);
//    ft_putstr_fd("parent id is ", 1); // если использовать printf то печатает после завершения программы
//    ft_putnbr_fd (fork_res, 1);// ID родителя
//    write(1, "\n", 1);
    // end for testing
    if (main->exit == 0)
        return(1);// можно просто брейкать
    else
        return(0);
    return(0);
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

int check_dir(char *cmd)
{

    DIR *dir = opendir(cmd);
//    int errnum;
    if (dir)
    {
        closedir(dir);
        return(1);
    } else if (ENOENT == errno)
    {
        return(2);
    } else if (EACCES == errno)
        return(3);
    return(0);
}

void process_builtins_and_divide_externals(t_main *main)
{
	char *command;
    struct stat sb;

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
		unset(main);
	else if(ft_strncmp(command, "env", 3) == 0)
		env(main);
	else if(ft_strncmp(command, "exit", 4) == 0)
		exit_command(main);
	else
	{
	    int status_num;
	    int f;
	    int d;
        char *message;

	    status_num = stat(command, &sb);
        f = exists(command); // checking for file is redundant
        d = check_dir(command);

        if (ft_strchr(command, '/')) {
            if (d == 2 && status_num == -1) // no entry to dir (non existent), no file, no status
            {
                main->flag2 = 1;
                ft_putstr_fd("minishell: ", 1);
                ft_putstr_fd(command, 1);
                ft_putstr_fd(": No such file or directory\n", 1);
                main->exit = 127;
                strerror(main->exit);
            }
            else if ((sb.st_mode & S_IFMT) == S_IFDIR)//directory present in the local directory
            {
                main->flag2 = 1;
                ft_putstr_fd("minishell: ", 1);
                ft_putstr_fd(command, 1);
                ft_putstr_fd(": is a directory\n", 1);
                main->exit = 126;
                strerror(main->exit);
            }
            else if (status_num < 0 && d == 3)  // dir exists but can not be entered
            {
                message = strerror(errno);
                main->flag2 = 1;
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(command, 2);
                ft_putchar_fd(' ', 2);
                ft_putstr_fd(message, 2);
                ft_putchar_fd('\n', 2);
                main->exit = 126;
            }
            else if ((sb.st_mode & S_IFMT) == S_IFREG)// clean command
                main->flag2 = process_ready_exe(main);
        }
        if (main->flag2 != 1)
            process_exe(main);
        main->flag2 = 0;
	}
}





