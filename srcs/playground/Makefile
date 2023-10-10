NAME = a.out

INC_DIR = ../../includes

SRCS = access.c \
	getenv.c \
	strtok.c \
	stat.c \

OBJS = $(SRCS:.c=.o)

SRCS_DIR = ..

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEBUGFLAGS = -g3 -O0
SANITIZEFLAGS = -g3 -O0 -fsanitize=address

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
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