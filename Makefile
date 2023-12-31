NAME = minishell

INC_DIR = ./includes
SRCS_DIR = ./srcs
LIBFT_DIR = $(SRCS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_FILES = minishell.c \
	env_to_envp.c \
	env_init.c \
	signal.c \
	search_env.c \
	pipe.c \
	pipe_utils.c \
	signal_utils.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

LEXER_DIR = $(SRCS_DIR)/lexer
LEXER_FILES = lexer.c \
	bool.c \
	token.c \
	value.c \

LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
LEXER_OBJS = $(LEXER_SRCS:.c=.o)
OBJS += $(LEXER_OBJS)

PARSER_DIR = $(SRCS_DIR)/parser
PARSER_FILES = parser.c \
	node.c \
	grammar.c \
	consume.c \
	free.c \
	parser_error.c \
	expect_node.c \
	consume_right.c \

PARSER_SRCS = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
PARSER_OBJS = $(PARSER_SRCS:.c=.o)
OBJS += $(PARSER_OBJS)

EXPAND_DIR = $(SRCS_DIR)/expansion
EXPAND_FILES = expand.c \
	expand_bool.c \
	count_len.c \
	copy_expand.c \

EXPAND_SRCS = $(addprefix $(EXPAND_DIR)/, $(EXPAND_FILES))
EXPAND_OBJS = $(EXPAND_SRCS:.c=.o)
OBJS += $(EXPAND_OBJS)

BUILTIN_DIR = $(SRCS_DIR)/builtin
BUILTIN_FILES = builtin_echo.c \
	builtin_pwd.c \
	builtin_exit.c \
	builtin_cd.c \
	builtin_export.c \
	builtin_env.c \
	builtin_unset.c \
	builtin_utility.c \

BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)
OBJS += $(BUILTIN_OBJS)

REDIRECT_DIR = $(SRCS_DIR)/redirect
REDIRECT_FILES = redirect.c \
	here_document.c \
	redirect_error.c \

REDIRECT_SRCS = $(addprefix $(REDIRECT_DIR)/, $(REDIRECT_FILES))
REDIRECT_OBJS = $(REDIRECT_SRCS:.c=.o)
OBJS += $(REDIRECT_OBJS)

EXECUTE_DIR = $(SRCS_DIR)/execute
EXECUTE_FILES = execute.c \
	execute_error.c \
	execute_bool.c \
	execute_path.c \
	execute_utils.c \
	execute_redirect.c \
	launch_command.c \

EXECUTE_SRCS = $(addprefix $(EXECUTE_DIR)/, $(EXECUTE_FILES))
EXECUTE_OBJS = $(EXECUTE_SRCS:.c=.o)
OBJS += $(EXECUTE_OBJS)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(shell brew --prefix readline)/include
DEBUGFLAGS = -g3 -fsanitize=address -O0
# DEBUGFLAGS = -g3 -O0 
RM = rm
RMFLAGS = -f

.PHONY: all clean fclean re debug

$(NAME): $(OBJS) $(LIBFT)
	@echo "set echo-control-characters off" > ~/.inputrc
	@echo "set enable-bracketed-paste off" >> ~/.inputrc
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -L $(shell brew --prefix readline)/lib

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
re: fclean all

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += $(DEBUGFLAGS)
endif

debug: re
