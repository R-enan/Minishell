
#include "header.h"

void	execute(char *input)
{
	char	**command;

	command = ft_split(input, ' ');
	// Buscar commando (PATH)

	// executar
}

void	clean_inner_spaces(char *input)
{
	while (*input)
	{
		if (*input == '\'' && *++input)
		{
			while (*input != '\'')
			{
				if (*input == ' ')
					*input = -1;
				input++;
			}
		}
		else if (*input == '"' && *++input)
		{
			while (*input != '"')
			{
				if (*input == ' ')
					*input = -1;
				input++;
			}
		}
		input++;
	}
}

char	*read_input(char *terminal)
{
	return (readline(terminal));
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = read_input("Digite o comando > ");
	if (has_unclosed_quotes(input))
		print_error();
	// Dividir por pipes
	clean_inner_spaces(input);
	remove_quotes(input);
	execute(input);
	printf("%s\n", input);
	free(input);
	return (0);
}
