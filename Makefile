NAME = minishell

INC_DIR = ./includes
SRCS_DIR = ./srcs
LIBFT_DIR = $(SRCS_DIR)/libft

FILES = minishell.c \
	lexer.c \
	lexer_utils.c \
	display_prompt.c \
	launch_executable.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEBUGFLAGS = -g3 -O0 -fsanitize=address
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
