NAME = minishell

CC = cc 

CFLAGS =  -Wall -Wextra -Werror -I./include/

READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INC = $(shell brew --prefix readline)/include

LDFLAGS = -L $(READLINE_LIB) -lreadline
INC_DIR = ./includes
INCLUDES = -I $(READLINE_INC) -I $(INC_DIR)

SRCS = \
    main.c \
    parsing/parsing_util1.c \
    parsing/parsing_util2.c \
    creation/add_back.c \
    creation/creation_util1.c \
	main_utils1.c\
	main_utils2.c\
    parsing/parsing_util3.c \
    parsing/parsing_util5.c \
    syntaxerror/syntaxerror_util1.c \
    syntaxerror/syntaxerror_util2.c \
    syntaxerror/syntaxerror_util3.c \
    herdoc/herdoc_util1.c \
    herdoc/herdoc_util2.c \
	signal/signal_utile1.c \
	creation/creation_util2.c\
	creation/creation_util3.c \
	parsing/parsing_util4.c \
	export/ft_export.c \
	export/util1.c \
	export/util2.c \
	builtins/ft_unset.c \
	builtins/ft_env.c \
	builtins/ft_cd.c \
	builtins/ft_pwd.c \
	builtins/ft_echo.c \
	builtins/ft_exit.c \
	libft/ft_strncmp.c \
	libft/ft_split.c \
	libft/ft_strjoin.c \
	libft/ft_count_word.c \
	libft/ft_strchr.c \
	libft/ft_atoi.c \
	libft/ft_strlen.c \
	fd_print.c \
	libft/ft_strtrim.c \
	libft/ft_itoa.c \
	libft/tax_collector.c \
	parsing/expanding.c \
	parsing/expanding2.c \
	execution/ft_execution.c\
	execution/ft_exec1.c \
	execution/ft_exec2.c \
	execution/ft_exec3.c \
	execution/ft_exec4.c \
	execution/ft_exec5.c \
	execution/ft_exec6.c \
	execution/ft_exec7.c

HEADER = include/structs.h include/minishell.h include/libft.h
OBJ_DIR = objectFile
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
all: $(NAME)

$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

	#for what this
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: clean