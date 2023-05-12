
NAME	=	minishell

FILES	=	builtin commands env execute list main path pipe quotemarks spaces var
OBJS	=	$(addsuffix .o, $(FILES))

HEADERS	=	header.h
INCLUDE	=	-I ../Libft -I $(HEADERS)

FLAGS	=	-Wall -Werror -Wextra -pg
LFLAGS	=	-lreadline

RM		=	rm -f

LIBFT	=	../Libft/libft.a

%.o: %.c $(HEADERS)
	cc $(FLAGS) -c $< $(INCLUDE) -o $@

all: libft $(NAME)

libft:
	@make -C ../Libft 
#--no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	cc $(FLAGS) $^ -g3 $(LFLAGS) $(INCLUDE) $(LIBFT) -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C ../Libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

v: all
#	clear && valgrind -s --xtree-leak=yes
	clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	--trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' \
	--suppressions=kkkkkk --xtree-leak=yes --xtree-leak-file=teste ./minishell
#ifneq ($(shell echo $$? 1>&2 2> /dev/null), 0)
#	$(error Deu ruim... $(shell echo $$?))
#endif
# --suppressions=<arquivo> (O <arquivo> é uma lista de coisas que ele deve ignorar  ..Estude..)
.PHONY: all clean fclean re