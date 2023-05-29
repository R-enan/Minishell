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

char	*make_expansions_and_remove_quotes(char *input, t_env *env)
{
	/************* Expandir variáveis e remover aspas ***********/
	if (input)
	{
		restore_inner_set(input, IS_SPACE_SET);
		// Tilde Expansion
		input = tilde_expansion(input, env); 
		// Verificar error
		ft_modify_quotemarks_to_remove(input, "'\"");
		input = expand_variables(input, env); 
		// Verificar error
		ft_removing_modified_quotemarks(input, "'\"");
	}
	return (input);
}

char	*treat_input(char *input)
{
	/******** Ajustar aspas **********/
	clean_inner_set(input, IS_SPACE_SET);
	/********* Normalizar string ********/
	ft_adjust_delimiters(input, IS_SPACE_SET);
	/*********Ajustar redirects *********/
	input = redirect(input);
	// Validar NULL
	input = one_after_redirects(input);
	// Validar NULL
	return (input);
}

int	execute_one_command(char *input, char **coman, t_env *env, t_redirects fds)
{
	int pid = fork();

	if (pid == 0)
	{
		/************ Duplicar fds (caso necessário) ***********/
		int bkp_input = -1;
		int bkp_output = -1;
		if (fds.fd_input != 0)
		{
			bkp_input = dup(0);
			dup2(fds.fd_input, 0);
		}
		if (fds.fd_output != 1)
		{
			bkp_output = dup(1);
			dup2(fds.fd_output, 1);
		}

		if (!access(coman[0], X_OK))
		{
			char **temp = list_to_pointer(env);
			execve(coman[0], coman, temp);
			free_matrix((void **)temp);
		}
		
		// |--Check if command is a directory, or the full path of binary
		// |--executar comando
		// exit // case error
		
		if (bkp_input > 0)
		{
			dup2(bkp_input, 0);
			close(bkp_input);
		}
		if (bkp_output > 1)
		{
			dup2(bkp_output, 1);
			close(bkp_output);
		}
		if (fds.fd_output != 1)
		{
			close(fds.fd_output);
		}
		free(input);
		free_matrix((void **)coman);
		//free_list(&redir_data.outputs_redirects);
		free_child_list(&env);
		exit(0);
	}
	else
	{
		wait(NULL);
		//free_matrix((void **)coman);
	}
	return (0);
}

int	build_command(char *input, t_env *env)
{
	/************** Para cada comando, executar **************/
	char **coman = ft_split_set(input, IS_SPACE_SET);
	int i = 0;
	/********* Remove redirects from command *********/
	t_redirects redir_data;

	redir_data.inputs_redirects = get_redirects(coman, '<');
	redir_data.outputs_redirects = get_redirects(coman, '>');

	/********** Abrir redirects **********/
	set_input(&redir_data);
	if (redir_data.fd_input < 0)
		return (-1); // Mensagem de erro ao tentar abrir arquivo (Free no command e na lista)
	set_output(&redir_data);
	if (redir_data.fd_output < 0)
		return (-1);

	if (!coman[i])
		free(coman); // E retorna sem executar (comando somente com redirects) echo $? retorna 0
	while (coman[i])
	{
		coman[i] = make_expansions_and_remove_quotes(coman[i], env);
		i++;
	}

	/******* Ajustar fds (em caso de pipes) ***********/
	// Se não houver redirects, uso o fd do pipe (Múltiplos comandos)

	/********* Verificar se comando é builtin ********/
	// Mando os redirects como argumentos para que o write escreva onde eu solicitar
	//if (ft_is_builtin(command))
	{
		// funcao(command, input_fd, output_fd)	

		/**
		// Retornar um int com o código do "exit status"
				OU
		 * abrir um fork(), e fazer o filho dar um exit com o código do retorno da builtin 
		 * (pai espera com wait)
		 */
	}
	// else
	{
		/********** Verificar se o comando é caminho de arquivo *******/
		// Se não for, fazer união com PATH e deixar o caminho completo como primeiro argumento da string

		/******** Executar comando que não é builtin ************/
		// dup2
		// fork
		execute_one_command(input, coman, env, redir_data);
		free_matrix((void **)coman);
		free(input);
	}
	return (0);
}

int	flow_to_fix(char *input, t_env *env)
{
	input = treat_input(input);
	if (!input)
		return (ENOMEM);
	// split commands // Emojis
	char	**commands = split_commands(input);
	// split command // Emojis
	//char **coman = ft_split_set(input, IS_SPACE_SET);
	
	free(input);
	build_command(commands[0], env);
	
	free_matrix((void **)commands);
	return (1);
}

int	minishell(t_env *env)
{
	char	*input;
	char	*cwd;

	while (1)
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
			return (1);//continue ;
		}
		flow_to_fix(input, env);
	}
	//free_parent_list(&env);
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
