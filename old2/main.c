#include "header.h"
int	single_command(char **command, t_env *env);
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

int	count_commands(char **commands)
{
	int	qtd;

	qtd = 0;
	if (!commands)
		return (qtd);
	while (commands[qtd])
		qtd++;
	return (qtd);
}

void	close_pipes(int *all_pipes, int index, int total_command)
{
	int	i;

	i = 0;
	while (i < total_command)
	{
		if (i != index )
		{
			if (all_pipes[i * 2])
				if (close(all_pipes[i * 2]))
					write(1, "1RUIM\n", 6);
			if (all_pipes[i * 2 + 3] != 1)
				if (close(all_pipes[i * 2 + 3]))
					write(1, "2RUIM\n", 6);
		}
		else //if (i == index)
		{
			if (all_pipes[i * 2])
			{
 				ft_putnbr_fd(all_pipes[i * 2], 1);
				ft_putstr_fd(" vira ", 1);
				ft_putnbr_fd(dup2(all_pipes[i * 2], 0), 1);
				ft_putstr_fd("\nO erro é: ",1);
				strerror(errno);ft_putnbr_fd(errno, 1);
				ft_putendl_fd("", 1); 
				/*if (dup2(all_pipes[i * 2], 0) != all_pipes[i * 2])
					write(1, "3RUIM\n", 6);*/
			}
			if (all_pipes[i * 2 + 3] != 1)
			{
/* 				ft_putnbr_fd(1, 1);
				ft_putstr_fd(" vira ", 1);
				ft_putnbr_fd(all_pipes[i * 2 + 3], 1);
				ft_putendl_fd("",1); */
				if (dup2(all_pipes[i * 2 + 3], 1) != 1/*all_pipes[i * 2 + 3]*/)
					write(1, "4RUIM\n", 6);
			}
			//close(all_pipes[i * 2]);
			//close(all_pipes[i * 2 + 3]);
		}
		i++;
	}
}

int	executes(char **commands, t_env *env, int *all_pipes)
{
	int		pid;
	int		id;
	char	**command;
	int		qtd = count_commands(commands);
	/* int i = 0;
	while (i < qtd * 2 + 2)
	{
		ft_putstr_fd("Posição: ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("\t Valor ", 1);
		ft_putnbr_fd(all_pipes[i++], 1);
		ft_putendl_fd("", 1);
	} */
	id = 0;
	while (commands[id])
	{
		// checar comando, se tudo estiver ok, fork
		pid = fork();
		if (pid == 0)
		{
			command = split_commands(commands[id]);
			close_pipes(all_pipes, id, qtd);
			return (single_command(command, env));
		}
		else
			// Se a criança retornar erro (wexit_status) sai do while
			wait(NULL);
		id++;
	}
	return (0);
}

int	multiple_commands(char **commands, t_env *env)
{
	// contar pipes (len_commands - 1)
	int	qtd_pipe = count_commands(commands);
	if (!qtd_pipe)
		return (1);
	//qtd_pipe--;
	/* ft_putnbr_fd(qtd_pipe * 2 + 2, 1);
	ft_putendl_fd(" ints alocados", 1);
	ft_putnbr_fd(qtd_pipe, 1);
	ft_putendl_fd(" comandos contados", 1); */
	int	*all_pipes = malloc((qtd_pipe * 2 + 2) * sizeof(int));
	if (!all_pipes)
		return (1);
	int i = 0;
	//all_pipes = (int *){0};
	while (i < qtd_pipe * 2 + 2)
		all_pipes[i++] = 0;
	all_pipes[qtd_pipe * 2 + 1] = 1;
/* 	i = 0;
	while (i < qtd_pipe * 2 + 2)
	{
		ft_putstr_fd("Posição: ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("\t Valor ", 1);
		ft_putnbr_fd(all_pipes[i++], 1);
		ft_putendl_fd("", 1);
	} */
	i = 2;
	while (i < qtd_pipe * 2)
	{
		if (pipe(&all_pipes[i]) == -1)
		{
			//pipe_error();
			//close all pipes opened until now
			free_matrix((void **)all_pipes);
			return (1);
		}
		i += 2;
	}
	int pid = fork();
	if (pid == 0)
		exit (executes(commands, env, all_pipes));
	else
		waitpid(0, &pid, 0);
	i = 2;
	while (i < qtd_pipe * 2)
	{
		if (close(all_pipes[i]) == -1)
		{
			//pipe_error();
			//close all pipes opened until now
			free_matrix((void **)all_pipes);
			return (1);
		}
		i++;
	}
	free_matrix((void **)all_pipes);
	// criar pipes
	// alterar fds
	// comunicar os bangs
	// executar em forks separados ????????????
	return (0);
}

int	single_command(char **command, t_env *env)
{
	char	**formatted_commad;
	char	**envp;
	char	*path;
	char	**all_paths;
	int		pid;

if (!command || !*command || !**command) // Existe a possibilidade de "$> $KKKK"
{
	write(2, "Command not found!\n", 19);
	return(1);
}
	formatted_commad = ft_split(*command, ' ');
	if (!formatted_commad)
		return (1);
	free_matrix((void **)command);
	command = formatted_commad;
	while (*formatted_commad)
		restore_inner_spaces(*formatted_commad++);
	if (is_builtin(*command))
	{
		ft_exit(command + 1);
	}
	pid = fork();
	if (pid == 0)
	{
		envp = list_to_pointer(env);
		all_paths = ft_split(get_value_of_var("PATH", env), ':');
		if (!all_paths)
			return (1);
		while (all_paths[pid])
		{
			path = join_path(all_paths[pid], command[0]);
			if (access(path, X_OK) == 0)
			{
				free_matrix((void **)all_paths);
				execve(path, command, envp);
			}
			free(path);
			path = NULL;
			pid++;
		}
		write(2, "Command not found!\n", 19);
		free_matrix((void **)all_paths);
		free_matrix((void **)command);
		exit(2);
	}
	else
		wait(NULL);
	//write(1, "Entrei aqui\n", 12);
	free_matrix((void **)command);
	return (0);
}

/**
 * Chegando aqui, temos um porém: A string está com -1 nos espaços internos e ainda segue como uma única string.
 * 
 * A solução inicial é separar por pipes em uma matriz.
 * 
 * Logo após, trabalhar cada comando de forma individual em seu próprio fork. 
 * Cada comando segue a estrutura: <<arquivo comando flags argumentos>>arquivo (Isso no já com o pior caso de escrita)
 * 
 * Após o tratamento em cada fork, executar.
 * 
 * 
 **/

void	execute_command(char *input, t_env *env)
{
	char	**commands;
	int		line;

	commands = split_commands(input);
	if (commands == NULL)
	{
		// erro ao mallocar
		return ;
	}
	line = 0;
	commands[line] = expand_variables(commands[line], env);
	clean_inner_spaces(commands[line]);
	if (has_pipe(input))
	{
		// Multiple commands
		while (commands[line])
		{
			commands[line] = expand_variables(commands[line], env);
			clean_inner_spaces(commands[line]);
			line++;
		}
		multiple_commands(commands, env);
	}
	else
		single_command(commands, env);
	// função que vai fazer as coisas mesmo
}

int validate_input(char *input)
{
	if (!input)
	{
		//print_error(); // Erro de readline
		return (1);
	}
	if (has_unclosed_quotes(input))
	{
		//print_error();
		return (1);
	}
	if (has_invalid_pipe(input))
	{
		write(1, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	return (0);
}

int	minishell(t_env	*env)
{
	char	*input;

	while (1)
	{
		input = readline("Digite o comando> ");
		if (validate_input(input))
		{
			free(input);
			continue ;
		}
		execute_command(input, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		// Error (many arguments)
		return (127);
	}
	return (minishell(env_build(envp)));
}
