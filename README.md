## Info

Russian brief intro

Командный (парный) проект подразумевает знание и использование команд системы контроля версий GIT.
Напарником по проекту был mihdevel (указан в качестве collaborator в этом проекте).

Язык проекта – С. Разработка собственной упрощенной версии командной оболочки Unix shell: minishell, которая запускается в терминале и способна с помощью парсинга входных данных анализировать вводимые команды и исполнять их. 

Напарник писал парсер, сигналы и подключил библиотеку readline. 
Моя роль в проекте – написать исполнительную часть. Я написал реализацию встроенных (builtin) функций: echo, unset, export, cd, pwd, env, также реализовал пайпы и редиректы. Проект направлен на изучение работы ядра системы Unix, понимание создания и взаимодействия процессов.


English intro

The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.
It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.
Thanks to Minishell, I am able to travel through time and come back to problems
people faced when Windows didn’t exist.


The project is written in C.
• It is written in accordance with the Norm.

• The project has Makefile which compiles source files to the required output with the flags -Wall, -Wextra and -Werror

• Makefile contains the rules $(NAME), all, clean, fclean and re.






### Shell for Unix 

Minishell is the project of the **School 21**. It's a minimum viable version of a real shell. 
The main goal is to have a good understanding of process creation and synchronisation using the C programmming language.

    Status: finished
    Result: 105%
    It is compatible with Linux and Mac OS.

Developed by:  **linguawork** and **mihdevel**
***

## Getting Started

1. Inslall `readline` library;
2. Make sure you have brew installed to run readline,otherwise check the bottom of the page for the command to run
3. Use `git` to clone this project `git clone https://github.com/linguawork/ft_minishell`;
4. Direct to the root directory `cd ./minishell`;
5. Build this project using Makefile `make` (make rules: all, run, clean, fclean and re);
6. Get Started! `./minishell`.
7. Please, check the readline version (currently it is 8.1.2)
   and correct the version folder name in Makefile to avoid conflicts
***

## How install readline library

### Linux

On Debian based platforms, like Ubuntu:

    sudo apt install libreadline-dev

Platforms with yum, like SUSE:

    yum install readline-devel

For other platform please search for the package name on google, thx :)

### MAC
Initially make sure you have brew installed. If not, please, run:

    curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

then run:

    brew install readline

#Additional resources:
    An instruction document that describes how to debug a child process in VSCode.
    [ChildProcessDebuggingVSCode.docx](https://github.com/linguawork/ft_minishell/files/8890385/ChildProcessDebuggingVSCode.docx)




