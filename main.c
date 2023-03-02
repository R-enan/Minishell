#include "header.h"

int	minishell(t_env	*env)
{
	char	*input;

	env = NULL;
	while (1)
	{
		input = readline("Digite o comando> ");
		if (has_unclosed_quotes(input))
			print_error();
		clean_inner_spaces(input);
		if (has_pipe(input))
		{
			if (has_invalid_pipe(input))
			{
				// Pipe error
			}
			// Multiple commands
		}
		else
		{
			// Only command
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		// Error (many arguments)
		return (127);
	}
	minishell(envp);
	return (0);
}
