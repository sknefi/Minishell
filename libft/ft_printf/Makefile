# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 15:25:12 by tmateja           #+#    #+#              #
#    Updated: 2024/10/11 14:58:54 by tmateja          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libftprintf.a

RM	=	rm -f

AR	=	ar -rcs

SOURCES	=	ft_printf.c ft_putchar.c ft_put_str.c ft_put_ptr.c ft_put_num.c ft_put_unum.c ft_low_hex.c ft_upper_hex.c

OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJECTS)
			$(AR) $(NAME) $(OBJECTS)

.c.o:	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJECTS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re