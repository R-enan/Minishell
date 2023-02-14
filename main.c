
#include "header.h"

void	execute(char *input)
{
	char	**command;

	// Arrumar os espaços dentro e fora das aspas

	// Splitar

	// Buscar commando (PATH)

	// executar
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
	remove_quotes(input);
	execute(input);
	printf("%s\n", input);
	free(input);
	return (0);
}
