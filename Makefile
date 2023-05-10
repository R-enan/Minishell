
###### Aqui, é a separação de arquivos em pastas ######

BUILTINS_PATH	=	builtins/
BUILTINS_SRC	=	

REDIRECTS_PATH	=	redirects/
REDIRECTS_SRC	=

QUOTEMARKS_PATH	=	quotemarks/
QUOTEMARKS_SRC	=	

###########        FIM       ###############
############################################



NAME			=	minishell

#####
###   Você pode usar somente FILES, enquanto não estiver separando os arquivos em pastas
####

FILES			=	
OBJS			=	$(addsuffix .o, $(FILES))

HEADERS			=	header.h
INCLUDE			=	-I Libft -I $(HEADERS)

FLAGS			=	-Wall -Werror -Wextra
LFLAGS			=	-lreadline

RM				=	rm -f

LIBFT			=	Libft/libft.a

%.o: %.c $(HEADERS)
	cc -c $< $(INCLUDE) -o $@

all: libft $(NAME)

libft:
	@make -C Libft --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	cc $^ -g3 $(LFLAGS) $(INCLUDE) $(LIBFT) -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C Libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

v: all
	clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	--trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' \
	--log-file=log --suppressions=valgrind_suppress ./minishell 

.PHONY: all clean fclean re v