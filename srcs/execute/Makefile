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