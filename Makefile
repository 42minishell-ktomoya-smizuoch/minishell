NAME = minishell

INC_DIR = ./includes
SRCS_DIR = ./srcs
LIBFT_DIR = $(SRCS_DIR)/libft

FILES = minishell.c \
	lexer.c \
	display_prompt.c \
	launch_executable.c \
	is_space_or_tab.c \
	set_errno_and_exit.c \
	lstadd_back_token.c \
	create_token.c \
	get_token_len.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS = $(SRCS:.c=.o)

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
