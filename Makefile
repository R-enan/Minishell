
NAME	=	minishell

FILES	=	main quotemarks utils
OBJS	=	$(addsuffix .o, $(FILES))

HEADERS	=	header.h
INCLUDE	=	-I .

FLAGS	=	-Wall -Werror -Wextra
LFLAGS	=	-lreadline

RM		=	rm -f

%.o: %.c $(HEADERS)
	cc -c $< $(INCLUDE) -o $@

all: $(NAME)

$(NAME): $(OBJS)
	cc  $^ $(LFLAGS) $(INCLUDE) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re