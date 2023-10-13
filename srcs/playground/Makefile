NAME = a.out

INC_DIR = ../../includes

SRCS = access.c \
	getenv.c \
	strtok.c \
	stat.c \
	test_strtok.c \
	strjoin.c \

OBJS = $(SRCS:.c=.o)

SRCS_DIR = ..
LIBFT_DIR = $(SRCS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEBUGFLAGS = -g3 -O0
SANITIZEFLAGS = -g3 -O0 -fsanitize=address

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(NAME)

re: clean all

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += $(DEBUGFLAGS)
endif

debug: re

ifeq ($(MAKECMDGOALS), address)
CFLAGS += $(SANITIZEFLAGS)
endif

address: re

.PHONY: all clean re debug