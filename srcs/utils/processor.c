#include "minishell.h"

// предлагаю использовать указатель на структуру

int echo(t_main *main)
{
	char *command;
	char **args;
	char *flags;

	command = main->job->pipe->redir->command;
    args = main->job->pipe->redir->args;
	flags = main->job->pipe->redir->flags;
	if (command != '\0')
	{
	    if (command && !(flags) && !(args))
            fputc('\n', stdout);
	    if (command && flags && !(args))
        {
            if (command && ft_strncmp(flags, "-n", 2) == 0)
                return(1);
        }
        if (command && !*flags && *args)
        {
            if (command && args)
            {
                fputs(*args++, stdout);
                while (*args)
                {
                    fputc(' ', stdout);
                    fputs(*args++, stdout);
                }
            }
        }
	}
	else
	// fputc('\n', stdout);
	return(0);
}

int cd(t_main *main)
// функция отрабатывает, но прога завершается и просходит возврат директорию программы
{
	char *command;
	char **args;
	char *flags;

	pwd(main); //проверка для отработки cd
	const char *p;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	flags = main->job->pipe->redir->flags;
	if (*args != NULL)
	{
		p = *args;
		// printf("%s", args[0]);
		chdir(p);
		// printf("%s\n", p);
		pwd (main); //проверка для отработки cd
	}
	else
	{
		p = getenv("HOME");
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
	if (chdir(p) < 0)
	{
		perror(p);
		return(1);
	}
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

	flags = main->job->pipe->redir->flags;

	if (flags != NULL )
		exit(1);
	exit(1);
}

int env(t_main *main)
{
	char *command;
	char **args;
	char **envir;

	command = main->job->pipe->redir->command;
	args = main->job->pipe->redir->args;
	envir = main->my_env;

	if ((command && *args == NULL) || (command && *args != NULL))
	{
		while(*envir)
		{
			printf("%s\n", *envir);
			envir++;
		}

	}
	return(0);
}

void	double_for_sort_algo(t_main *main, int size)
{
    // char **args;
	char **envir;

	// args = main->job->pipe->redir->args;
	envir = main->my_env;
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

void reconstruct(t_main *main)
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

void withzero(t_main *main)
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
				reconstruct(main);
			else if (args[i][j] == '=' && args[i][j + 1] == 0)
				withzero(main);
			++j;
		}
		++i;
	}
}

void reconstruct2(t_main *main)
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
	len = ft_strlen(splitstr[0]);// для сравнения в strncmp
	len2 = ft_strlen(splitstr[1]);// длина хвоста аргумента
	while(envir[i])
	{
		// printf("%s ||| %s\n", );
		// if (strncmp(envir[i], splitstr[0], 4) == 0)
		// 	printf("OKEY\n");
		if (flag == 0 && ft_strncmp(envir[i], splitstr[0], len) == 0) // сравнение без знака равно
		{
			printf("inside\n");
			splitenvir = ft_split(envir[i], '=');
			free((void *)envir[i]); //переназначение типа (так как free требует  void*)
			envir[i] = (char *)malloc(sizeof(char*)*(len +1 + len2 + 1));
			strcpy((char *)envir[i], splitenvir[0]);
			strcat((char *)envir[i], "=");
			strcat((char *)envir[i], splitstr[1]);
			printf("%s\n", envir[i]);
			arrays_free(splitstr);
			flag = 1;
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

void check_duplicates(t_main *main)
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
				reconstruct2(main);
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
	len = char_count(*args); // lenght до знака равно
	name = ft_substr(*args, 0, len);
	value = ft_strdup(ft_strchr(*args, ('='+1)));
	len2 = ft_strlen(value);

	s = (char *)malloc(sizeof(char *)*(len+1 + len2+1+3));
	s[0] = 0;

	
	strcpy(s, name); // пока сделаем без маллока
	strcat(s, "=");
	strcat(s, "\"");
	strcat(s, value);
	strcat(s, "\"");
	*args = s;
	free(s);
}

int export(t_main *main)
{
	char *command;
	char **args;
	char **envir;
	char **newenvir;
	char *prefix;
	int len;
	int newlen;
    int i;

	envir = main->my_env;
	args = main->job->pipe->redir->args;
	prefix = "declare -x ";
	len = how_many_lines(envir);
//	newenvir = ( char **)malloc(sizeof(char*)*(len+1));
//
//	int i = 1;
//	while (envir[i]) // запись из оригинала в замолоченный двумерный массив с размером рядов оригинала
//	{
//		newenvir[i] = ft_strdup(envir[i]);// лучше записывать через индекс
//		i++;
//	}
//	newenvir[i] = NULL;
	newlen= how_many_lines(newenvir);
	i = 1;
	if (command && *args == NULL)
	{
		double_for_sort_algo(main, newlen);
		while(newenvir[i])
		{
			newenvir[i] = ft_strjoin(prefix, newenvir[i]);
			printf("%s\n", newenvir[i]);
			i++;
		}
	}
	if (command && *args != NULL)
	{
		// printf("I am working on it\n");
		int i;
		i = 0;

		// divider(args);
		check_duplicates(main);
		check_equal_sign_add_quotes(main);
		while ( i >= 0 && args[i] != NULL)
		{
			newlen= how_many_lines(newenvir);
			printf("%d\n", newlen);
			newenvir = ( char **)realloc(envir,(sizeof(char*)*(newlen + 2))); // обязательно нужно указывать на размер чего-то (в данном случае чаров)
			newenvir[newlen + 1] = NULL; // сместили указатель на ноль по индексу длины рядов массива
			// printf("test%s\n", args[i]);
			newenvir[newlen] = args[i];// в выделенную ячейку добавляем аргумент по индексу длины рядов массива
			newlen = newlen + 1;
			i++;
			newlen= how_many_lines(newenvir);
			printf("%d\n", newlen);
		}

		i = 0;
		double_for_sort_algo(main, newlen);
		while(newenvir[i])
		{
			newenvir[i] = ft_strjoin(prefix, newenvir[i]);
			printf("%s\n", newenvir[i]);
			i++;
		}
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
	printf("worked in externals");
}

//int echo(t_main *main)
//{
//	char *command;
//	char **args;
//
//	command = main->job->pipe->redir->command;
//	args = main->job->pipe->redir->args;
//	while (command)
//	{
//		if(!(args))
//			fputc(' ', stdout);
//		else
//			fputs(*(args), stdout);
//	}
//	fputc('\n', stdout);
//	return(0);
//}


