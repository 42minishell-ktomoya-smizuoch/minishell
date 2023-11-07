NAME = a.out

INC_DIR = ../../includes

SRCS = lexer.c \
	bool.c \
	token.c \
	value.c \

OBJS = $(SRCS:.c=.o)

SRCS_DIR = ..
LIBFT_DIR = $(SRCS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(shell brew --prefix readline)/include
DEBUGFLAGS = -g3 -O0

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -L $(shell brew --prefix readline)/lib

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
