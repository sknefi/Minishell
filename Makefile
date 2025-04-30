NAME		= minishell

RED   		= \033[31m
GREEN 		= \033[32m
YELLOW		= \033[33m
BLUE  		= \033[34m
RESET 		= \033[0m

SRCS =  source/minishell.c source/signals.c source/token/token.c source/token/env_var.c \
		source/token/token_utils.c source/token/extract_token_utils.c \
		source/ast/ast.c source/ast/ast_utils.c
		
OBJS 		= $(SRCS:.c=.o)

CC			= cc
CCFLAGS		= -Wall -Wextra -Werror -g #-lreadline -g
RM			= rm -f

LIBFT_NAME	= libft.a
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/$(LIBFT_NAME)




all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)COMPILING: $(NAME)$(RESET)"
	$(CC) $(CCFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 
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
