NAME       = minishell

RED        = \033[31m
GREEN      = \033[32m
YELLOW     = \033[33m
BLUE       = \033[34m
RESET      = \033[0m

SRCS = \
    ./src/signal/signals_01.c \
    ./src/signal/signals_02.c \
    \
    ./src/token/token.c \
    ./src/token/token_utils.c \
    ./src/token/handle_operators.c \
    ./src/token/handle_word.c \
    ./src/token/handle_word_utils.c \
    ./src/token/ft_realloc_token.c \
    \
    ./src/ast/ast.c \
    ./src/ast/ast_norm.c \
    ./src/ast/ast_utils.c \
    ./src/ast/free_ast.c \
    \
    ./src/builtins/env_utils_01.c \
    ./src/builtins/sh_cd.c \
    ./src/builtins/sh_env.c \
    ./src/builtins/sh_pwd.c \
    ./src/builtins/sh_echo.c \
    ./src/builtins/sh_exit.c \
    ./src/builtins/sh_unset.c \
    ./src/builtins/sh_export.c \
    \
    ./src/init/init_builtins.c \
    ./src/init/init_app.c \
    ./src/init/init_env.c \
    \
    ./src/exec/status_res.c \
    ./src/exec/sh_exec.c \
    ./src/exec/exec_external.c \
    ./src/exec/exec_builtin.c \
    \
    ./src/utils/utils_01_dpp.c \
    \
    ./src/handlers/pipe.c \
    ./src/handlers/heredoc.c \
    ./src/handlers/heredoc_utils.c \
    ./src/handlers/redirection.c \
    ./src/handlers/redirection_utils.c \
    \
    ./src/main.c

OBJS       = $(SRCS:.c=.o)

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g
LDFLAGS    = -lreadline
RM         = rm -f

LIBFT_NAME = libft.a
LIBFT_DIR  = ./libft
LIBFT      = $(LIBFT_DIR)/$(LIBFT_NAME)


all: $(NAME)

%.o: %.c
	@printf "$(BLUE)Compiling$(RESET): %-50s" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@ && printf "$(GREEN)✔\n$(RESET)" || printf "$(RED)✖\n$(RESET)"

$(NAME): $(OBJS)
	@printf "\n$(YELLOW)Building libft library...$(RESET)\n"
	@make -C $(LIBFT_DIR)
	@printf "$(BLUE)Linking$(RESET):    %-50s" "$(NAME)"
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) \
	  && printf "$(GREEN)✔\n$(RESET)" \
	  || printf "$(RED)✖\n$(RESET)"
	@printf "$(GREEN)Done! $(NAME) is ready to go!$(RESET)\n"

clean:
	@printf "$(YELLOW)Cleaning objects...$(RESET)\n"
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@printf "$(GREEN)Cleaned all object files.$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)Removing binaries...$(RESET)\n"
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@printf "$(GREEN)Removed $(NAME).$(RESET)\n"

re: fclean all
	@printf "$(YELLOW)Rebuilding everything...$(RESET)\n"
	@$(MAKE) all

.PHONY: all clean fclean re
