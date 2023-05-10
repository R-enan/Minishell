#include "header.h"

/**
 * @param input the input geted by the readline
 * @brief Checks the common errors in the initial input
 * @return 0 if has no error, 1 if some error is found.
 */
int	has_input_error(char *input)
{
	if (!input)
		return (1);
	/*if (has_invalid_pipe(input))
	{
		write(1, "", 1); // Get the inex of error and print "error near `<pointer>"?
		return (1);
	}
	if (has_unclosed_quotes(input))
	{
		write(1, "Close your quotes!!!\n", 21);
		return (1);
	}*/
	return (0);
}

int	minishell(t_env *env)
{
	char	*input;
	char	cwd[4096];

	while(1)
	{
		getcwd(cwd, 4096);
		ft_strlcpy(cwd + ft_strlen(cwd), "> ", 3);
		input = readline(cwd);
		if (has_input_error(input))
		{
			free(input);
			continue ;
		}
		ft_putendl_fd("Foi!", 1);
		return (1);
		execute_command(input, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*list;

	if (argc != 1)
	{
		// No takes arument
		return (2);
	}
	list = pointer_to_list(envp);
	if (!list)
	{
		// Malloc error
		return (12); // ENOMEM
	}
	return (minishell(list));
}