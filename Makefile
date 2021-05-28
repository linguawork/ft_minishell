NAME = minishell

LIBFT_PATH = ./libft/
MAIN_DIR = ./srcs/main/
PARS_DIR = ./srcs/parser/
UTILS_DIR = ./srcs/utils/
TESTS_DIR = ./srcs/tests/

MAIN_FILES = start.c
PARS_FILES = parser.c
UTILS_FILES = utils.c utils_parser.c
TESTS_FILES = tests_parser.c

MAIN = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PARS = $(addprefix $(PARS_DIR), $(PARS_FILES))
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_FILES))
TESTS = $(addprefix $(TESTS_DIR), $(TESTS_FILES))

SRC_FILES = $(MAIN) $(PARS) $(UTILS) $(TESTS)
OBJ_FILES = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -g #-fsanitize=address
CC= gcc $(FLAGS)

all:$(NAME) $?

%.o: %.c includes/minishell.h
	$(CC) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(OBJ_FILES) $(LIBFT_PATH)libft.a -o $(NAME)

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