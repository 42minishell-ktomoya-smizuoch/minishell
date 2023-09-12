NAME = minishell

INC_DIR = ./includes
SRCS_DIR = ./srcs
LIBFT_DIR = $(SRCS_DIR)/libft

SRCS_FILES = minishell.c \
	display_prompt.c \
	launch_executable.c \
	set_errno_and_exit.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

LEXER_DIR = $(SRCS_DIR)/lexer
LEXER_FILES = lexer.c \
	lexer_bool.c \
	lstadd_back_token.c \
	create_token.c \
	get_token_len.c \

LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
LEXER_OBJS = $(LEXER_SRCS:.c=.o)
OBJS += $(LEXER_OBJS)

PARSER_DIR = $(SRCS_DIR)/parser
PARSER_FILES = parser.c \
	node.c \

PARSER_SRCS = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
PARSER_OBJS = $(PARSER_SRCS:.c=.o)
OBJS += $(PARSER_OBJS)

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEBUGFLAGS = -g3 -O0
RM = rm
RMFLAGS = -f

.PHONY: all clean fclean re debug

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
re: fclean all

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += $(DEBUGFLAGS)
endif

debug: re
