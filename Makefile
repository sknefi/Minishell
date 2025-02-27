NAME		= minishell

RED   		= \033[31m
GREEN 		= \033[32m
YELLOW		= \033[33m
BLUE  		= \033[34m
RESET 		= \033[0m

SRCS =  source/minishell.c source/lexer/lexer.c
		
OBJS 		= $(SRCS:.c=.o)

CC			= cc
CCFLAGS		= -Wall -Wextra -Werror -lreadline
RM			= rm -f

LIBFT_NAME	= libft.a
LIBFT_DIR	= ./libft_divinus
LIBFT		= $(LIBFT_DIR)/$(LIBFT_NAME)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)COMPILING: $(NAME)$(RESET)"
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) 
	@echo "$(GREEN)SUCCESS: $(NAME) compiled$(RESET)"

clean:
	$(RM) $(OBJS)
	@echo "$(GREEN)SUCCESS:$(RESET) $(RED)cleaned $(NAME)$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(GREEN)SUCCESS:$(RESET) $(RED)removed $(NAME)$(RESET)"

re: fclean all

e: all clean

libft:
	make re -C $(LIBFT_DIR)

libfte:
	make e -C $(LIBFT_DIR)

libftfclean:
	make fclean -C $(LIBFT_DIR)

.PHONY: all clean fclean re
