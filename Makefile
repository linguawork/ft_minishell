NAME = minishell

LIBFT_PATH = ./libft/
MAIN_DIR = ./srcs/main/
PARS_DIR = ./srcs/parser/
UTILS_DIR = ./srcs/utils/
TESTS_DIR = ./srcs/tests/

MAIN_FILES = start.c init_struct.c
PARS_FILES = parser.c init_structures.c pipe.c redirect.c write_to_main.c env.c
UTILS_FILES = utils.c processor.c utils_parser.c utils_processor.c exe.c cd.c \
pipes.c  echo.c pwd.c exit.c env.c export.c export2.c unset.c utils_processor2.c \
processor2.c pipes2.c pipes3.c redir_one_right.c redir_two_right.c redir_one_left.c \
free_structures.c  redir_two_left.c
TESTS_FILES = #tests_parser.c

MAIN = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PARS = $(addprefix $(PARS_DIR), $(PARS_FILES))
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_FILES))
TESTS = $(addprefix $(TESTS_DIR), $(TESTS_FILES))

SRC_FILES = $(MAIN) $(PARS) $(UTILS) $(TESTS)
OBJ_FILES = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -Ilibft -Iincludes #-fsanitize=address
#FLAGS += -I/Users/meunostu/$(USER)/Cellar/readline/8.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/

CC= gcc $(FLAGS)

all:$(NAME) $?

%.o: %.c includes/minishell.h
	$(CC) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(OBJ_FILES) $(LIBFT_PATH)libft.a -o $(NAME) -lreadline -I/Users/meunostu/$(USER)/Cellar/readline/8.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	/bin/rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	/bin/rm -f $(NAME)

re: fclean all

#tests: $(OBJ_FILES)
#	$(CC) $(OBJ_FILES) $(TESTS) $(LIBFT_PATH)libft.a -o $(NAME)
#	./$(NAME)

run: $(NAME)
	./$(NAME)

norm:
	norminette $(SRC_FILES) includes/*.h $(LIBFT_PATH)*.c

.PHONY:	all clean fclean re norm run