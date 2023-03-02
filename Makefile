
NAME	=	minishell

FILES	=	main quotemarks utils
OBJS	=	$(addsuffix .o, $(FILES))

HEADERS	=	header.h
INCLUDE	=	-I Libft

FLAGS	=	-Wall -Werror -Wextra
LFLAGS	=	-lreadline

RM		=	rm -f

LIBFT	=	Libft/libft.a

%.o: %.c $(HEADERS)
	cc -c $< $(INCLUDE) -o $@

all: libft $(NAME)

libft:
	@make -C Libft --no-print-directory

$(NAME): $(OBJS)
	cc  $^ $(LFLAGS) $(INCLUDE) -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C Libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re