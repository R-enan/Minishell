#include "header.h"

int	minishell(t_env *env)
{
	char	*input;
	char	*cwd;

	while (env)
	{
		//input = readline("Digite o comando> ");
		cwd = getcwd(NULL, 0); // Caminho maior que 4096
		ft_strlcpy(cwd + ft_strlen(cwd), "> ", 3);
		input = readline(cwd);
		free(cwd); // Free no bang dá certo
		if (has_input_error(input))
		{
			// echo $? should print 2
			free(input);
			continue ;
		}
		//remove_quotes(input);
		removing_useless_quotes(input);
		ft_putendl_fd(input, 1);
		//execute_command(input, env);
	}
	return (0);
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
	return (minishell(list));
}
