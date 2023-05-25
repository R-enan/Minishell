#include "header.h"

int	ft_has_invalid_pipe(char *input)
{
	while (input && ft_is_in_set(*input, IS_SPACE_SET))
		input++;
	if (input && *input == '|')
		return (1);
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (*input == '|')
		{
			input++;
			while (ft_is_in_set(*input, IS_SPACE_SET))
				input++;
			if (*input == '|' || !*input)
				return (1);
		}
		else
			input++;
	}
	return (0);
}

/**
 * Usar o dup(1) pra copiar o stdout
 * Usar o dup2(dup(1),o_que_eu_quero) pra usar como pipes;
 * O último processo vai ser dup2(dup(1), dup(1)); // Assim não tenho B.O. com fds
 * 
 * 
 * Lógica análoga para fazer o conteúdo ir para os arquivos.
 * Write... >>>>> printf
 */
