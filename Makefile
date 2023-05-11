# Aqui estão as variáveis que serão usadas assim que colocarmos \
as pastas devidas nos arquivos.

# Mesmo não separando os arquivos por pastas, as variáveis estarão \
escritas já se preparando para o futuro. Pois, poucas coisas seriam \
alteradas no momento final

NAME			=	minishell

BUILTIN_PATH	=	
BUILTIN_SRC		=	
BUILTIN_OBJ		=	$(addsuffix .o, $(BUILTIN_SRC))

REDIRECTS_PATH	=	
REDIRECTS_SRC	=	
REDIRECTS_OBJ	=	$(addsuffix .o, $(REDIRECTS_SRC))

QUOTEMARKS_PATH	=	
QUOTEMARKS_SRC	=	quotemarks
QUOTEMARKS_OBJ	=	$(addsuffix .o, $(QUOTEMARKS_SRC))

PIPES_PATH		=	
PIPES_SRC		=	
PIPES_OBJ		=	$(addsuffix .o, $(PIPES_SRC))

SPACES_PATH		=	
SPACES_SRC		=	
SPACES_OBJ		=	$(addsuffix .o, $(SPACES_SRC))

EXECUTE_PATH	=
EXECUTE_SRC		=
EXECUTE_OBJ		=	$(addsuffix .o, $(EXECUTE_SRC))

ENV_PATH		=
ENV_SRC			=	env list
ENV_OBJ			=	$(addsuffix .o, $(ENV_SRC))

SRC_PATH		=
SRC_SRC			:=	main checker
SRC_OBJ			:=	$(addsuffix .o, $(SRC_SRC))

INCLUDES		=	-I libft

FLAGS			=	-Wall -Werror -Wextra 
READLINE_FLAGS	=	-lreadline

LIBFT_PATH		=	libft/
LIBFT			=	$(addprefix $(LIBFT_PATH),libft.a)

%.o: %.c
	cc -c $(FLAGS) $(INCLUDES) $< -o $@

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH) --no-print-directory

$(NAME): $(BUILTIN_OBJ) $(REDIRECTS_OBJ) $(PIPES_OBJ) \
 $(QUOTEMARKS_OBJ) $(EXECUTE_OBJ) $(SRC_OBJ) $(ENV_OBJ)
	cc $(FLAGS) $(INCLUDES) $^ $(LIBFT) $(READLINE_FLAGS) -o $@

clean:
	rm -f $(BUILTIN_OBJ) $(REDIRECTS_OBJ) $(PIPES_OBJ) 
	rm -f $(QUOTEMARKS_OBJ) $(EXECUTE_OBJ) $(SRC_OBJ) $(ENV_OBJ)
	@make clean -C $(LIBFT_PATH) --no-print-directory

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

v: all
	clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	--trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' \
	--suppressions=valgrind_suppressions ./minishell

.PHONY: all clean fclean re libft v