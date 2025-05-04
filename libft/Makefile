CC	=	clang
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

RM	=	rm -f

AR	=	ar -rcs

INCLUDE	=	libft.h
SOURCES	=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_tolower.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c \
			ft_memcmp.c ft_memset.c ft_strchr.c ft_strlcat.c ft_toupper.c \
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_calloc.c ft_strrchr.c \
			ft_memmove.c ft_strdup.c ft_strnstr.c ft_strjoin.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c \
			ft_strtrim.c ft_substr.c ft_split.c ft_itoa.c ft_striteri.c \
			ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_put_str.c \
			ft_printf/ft_put_ptr.c ft_printf/ft_put_num.c ft_printf/ft_put_unum.c \
			ft_printf/ft_low_hex.c ft_printf/ft_upper_hex.c ft_realloc.c

BSOURCES =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS	=	$(SOURCES:.c=.o)
BOBJECTS =	$(BSOURCES:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJECTS) $(INCLUDE)
			$(AR) $(NAME) $(OBJECTS)

.c.o:	$(CC) (CFLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

bonus: $(NAME) $(BOBJECTS)
		$(AR) $(NAME) $(BOBJECTS)
clean:
		$(RM) $(OBJECTS) $(BOBJECTS)

fclean:	clean
		$(RM) $(NAME) $(bonus)

re:	fclean all
