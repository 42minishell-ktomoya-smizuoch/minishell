NAME = a.out

INC_DIR = ../../includes

SRCS = expand.c \

OBJS = $(SRCS:.c=.o)

SRCS_DIR = ..
LIBFT_DIR = $(SRCS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

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