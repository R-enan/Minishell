#include "header.h"

int	minishell(t_env *env)
{
	char	*input;
	char	cwd[4096];

	while (env)
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
		remove_quotes(input);
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
