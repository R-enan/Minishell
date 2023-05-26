#include "header.h"

void	free_matrix(void **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
	}
}

int	minishell(t_env *env)
{
	char	*input;
	char	*cwd;

	while (env)
	{
		//input = readline("Digite o comando> ");
		input = getcwd(NULL, 0); // Caminho maior que 4096
		cwd = malloc(ft_strlen(input) + 3);
		if (!cwd)
		{}
		ft_strlcpy(cwd, input, ft_strlen(input) + 1);
		ft_strlcpy(cwd + ft_strlen(cwd), "> ", 3);
		free(input);
		input = readline(cwd);
		free(cwd); // Free no bang dá certo
		if (has_input_error(input))
		{
			// echo $? should print 2
			free(input);
			continue ;
		}
		clean_inner_set(input, IS_SPACE_SET);
		ft_adjust_delimiters(input, IS_SPACE_SET);
		if (*input == ' ')
			ft_memmove(input + 1, input, ft_strlen(input));
		size_t	len = ft_strlen(input) - 1;
		if (input[len] == ' ')
			input[len] = 0;
		input = redirect(input);
		input = one_after_redirects(input);
		// split commands // Emojis
		// split command // Emojis
		char **coman = ft_split_set(input, IS_SPACE_SET);
		int i = 0;
		while (coman && coman[i])
		{
			restore_inner_set(coman[i], IS_SPACE_SET);
			// Tilde Expansion
			coman[i] = tilde_expansion(coman[i], env); // Verificar error
			ft_modify_quotemarks_to_remove(coman[i], "'\"");
			coman[i] = expand_variables(coman[i], env); // Verificar error
			//ft_putendl_fd(coman[i], 1);
			ft_removing_modified_quotemarks(coman[i], "'\"");
			ft_putendl_fd(coman[i++], 1);
			//i++;
		}
		// Remove redirects from command
		t_redirects redir_data;
		
		redir_data.inputs_redirects = get_redirects(coman, '<');
		redir_data.outputs_redirects = get_redirects(coman, '>');
		set_input(&redir_data);
		if (redir_data.fd_input < 0)
			return (-1);
		set_output(&redir_data);
		if (redir_data.fd_output < 0)
			return (-1);
		// dup2
		// fork
		ft_putstr_fd("Esse é o output: ", 1);
		int pid = fork();
		if (pid == 0)
		{
			int bkp_input = dup(0);
			int bkp_output = dup(1);
			dup2(redir_data.fd_input, 0);
			dup2(redir_data.fd_output, 1);
			// |--Check if command is a directory, or the full path of binary
			// |--executar comando
			// exit // case error
			write(1, "Essa é a saída padrão do filho!\n", 35);
			dup2(bkp_input, 0);
			dup2(bkp_output, 1);
			close(bkp_input);
			close(bkp_output);
			close(redir_data.fd_output);
			free(input);
			free_matrix((void **)coman);
			free_list(&redir_data.outputs_redirects);
			free_list(&env);
			exit(0);
		}
		else
		{
			//ft_putendl_fd(input, 1);
			free_list(&redir_data.outputs_redirects);
			close(redir_data.fd_output);
			free(input);
			free_matrix((void **)coman);
		}
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
	list = pointer_to_list(envp);
	if (!list)
		return (ENOMEM);
	return (minishell(list));
}
