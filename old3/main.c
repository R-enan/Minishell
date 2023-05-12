#include "header.h"

void	free_matrix(void **matrix)
{
	size_t	index;

	if (matrix)
	{
		index = 0;
		while (matrix[index])
			free(matrix[index++]);
		free(matrix);
	}
}

int	has_input_error(char *input)
{
	if (!input)
	{
		/* write(1, "syntax error NULL\n", 18); */
		// Allocation error
		return (1);
	}
	if (has_invalid_pipe(input))
	{
		write(1, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	if (has_unclosed_quotes(input))
	{
		// Close your quotes
		write(1, "syntax error QUOTES\n", 20);
		return (1);
	}
	return (0);
}

int	minishell(t_env *env)
{
	char	*input;
	char	cwd[4096];

	while (1)
	{
		//input = readline("Digite o comando> ");
		getcwd(cwd, 4096);
		ft_strlcpy(cwd + ft_strlen(cwd), "> ", 3);
		input = readline(cwd);
		if (has_input_error(input))
		{
			// echo $? should print 2
			free(input);
			continue ;
		}
		input = expand_variables(input, env);
		execute_command(input, env);
		
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*list;

	if (argc > 1 || argv[1])
	{
		// Multiples arguments
		return (127);
	}
	list = env_build(envp);
	if (!list)
		return (ENOMEM);
	//ft_env((char *[]) {"env", NULL}, list);
	return (minishell(list));
}
