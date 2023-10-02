NAME = execute

INC_DIR = ../../includes

SRCS = execute.c \

OBJS = $(SRCS:.c=.o)

SRCS_DIR = ..
LIBFT_DIR = $(SRCS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

LEXER_DIR = $(SRCS_DIR)/lexer
LEXER_FILES = lexer.c \
	bool.c \
	token.c \
	value.c \

LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
LEXER_OBJS = $(LEXER_SRCS:.c=.o)
OBJS += $(LEXER_OBJS)

BUILTIN_DIR = $(SRCS_DIR)/builtin
BUILTIN_FILES = builtin_echo.c \
	builtin_pwd.c \
	builtin_exit.c \
#	builtin_cd.c \
	builtin_export.c \
	builtin_unset.c \
	builtin_env.c \

BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)
OBJS += $(BUILTIN_OBJS)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEBUGFLAGS = -g3 -O0

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(NAME)

re: clean all

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += $(DEBUGFLAGS)
endif

debug: re

.PHONY: all clean re debug