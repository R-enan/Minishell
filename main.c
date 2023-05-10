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

<<<<<<< Updated upstream
size_t	len_of_env(t_env *env)
{
	size_t	len;
	t_env	*aux;

	len = 0;
	aux = env;
	while (aux)
	{
		len++;
		aux = aux->next;
	}
	return (len);
}

char	**t_env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*aux;
	size_t	index;

	envp = (char **) malloc(len_of_env(env) * sizeof(char *) + 1);
	if (envp == NULL)
		return (NULL);
	aux = env;
	index = 0;
	while (aux)
	{
		envp[index] = ft_strdup(aux->var);
		aux = aux->next;
		index++;
	}
	envp[index] = NULL;
	return (envp);
}

char	*get_index(int index, t_env *command)
{
	while (command && index)
	{
		index--;
		command = command->next;
	}
	if (command)
		return command->var;
	return (NULL);
}

<<<<<<< HEAD
void	execute_multiple(char *input, t_env *env)
=======
size_t	len_of_env(t_env *env)
{
	size_t	len;
	t_env	*aux;

	len = 0;
	aux = env;
	while (aux)
	{
		len++;
		aux = aux->next;
	}
	return (len);
}

char	**t_env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*aux;
	size_t	index;

	envp = (char **) malloc(len_of_env(env) * sizeof(char *) + 1);
	if (envp == NULL)
		return (NULL);
	aux = env;
	index = 0;
	while (aux)
	{
		envp[index] = ft_strdup(aux->var);
		aux = aux->next;
		index++;
	}
	envp[index] = NULL;
	return (envp);
}

char	*get_index(int index, t_env *command)
{
	while (command && index)
	{
		index--;
		command = command->next;
	}
	if (command)
		return command->var;
	return (NULL);
}

void	execute_multiple(char *input, t_env *env)
{
	t_env	*comandos;
	size_t	qtd_comandos;
	char	**command;
	char	*path;
	char	**splited_path;
	int		line;
	char 	**teste = t_env_to_envp(env);

	comandos = multiple_commands(input);
	qtd_comandos = len_of_env(comandos);
	printf("Variável PATH=%s\n", getenv("PATH"));
	if (qtd_comandos == 2)
	{
		int fds[2];

		if (pipe(fds) == -1) {puts("DEU RUIM"); return ;}
		int pid = fork();
		if (pid == 0)
		{
			int neto = fork();
			if (neto == 0)
			{
				// executa 1º ls
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
				remove_quotes(get_index(0, comandos));
				command = ft_split(get_index(0, comandos), ' ');
				restore_inner_spaces(command);
				path = return_path(env);
				if (path == NULL)
					return ;
				splited_path = ft_split(path + 5, ':');
				building_command_path(splited_path, command[0]);
				line = check_execute_file(splited_path);
				if (line == -1)
					printf("Command not found!\n");
				else
				{
					execve(splited_path[line], command, teste);
				}
				exit(127);
				execve("/usr/bin/ls", (char *[]){"ls", NULL}, NULL);
			}
			else
			{
				// executa 2º ls
				dup2(fds[0], STDIN_FILENO);
				close(fds[1]);
				close(fds[0]);
				remove_quotes(get_index(1, comandos));
				command = ft_split(get_index(1, comandos), ' ');
				restore_inner_spaces(command);
				path = return_path(env);
				if (path == NULL)
					return ;
				splited_path = ft_split(path + 5, ':');
				building_command_path(splited_path, command[0]);
				line = check_execute_file(splited_path);
				if (line == -1)
					printf("Command not found!\n");
				else
				{
					execve(splited_path[line], command, teste);
				}
				exit(127);
				execve("/usr/bin/cat", (char *[]){"cat", NULL}, NULL);
			}
			waitpid(neto, NULL, 0);
		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid, NULL, 0);
			//waitpid(pid, NULL, 0);
		}
	}
	else while (comandos)
	{
		printf("Comando: %s \n", comandos->var);
		comandos = comandos->next;
	}
}

void	execute(char *input, t_env *env)
>>>>>>> 711d8bc9ba635aa730878fda7f34c98ca9727569
{
	t_env	*comandos;
	size_t	qtd_comandos;
	char	**command;
	char	*path;
	char	**splited_path;
	int		line;
	char 	**teste = t_env_to_envp(env);

<<<<<<< HEAD
	comandos = multiple_commands(input);
	qtd_comandos = len_of_env(comandos);
	printf("Variável PATH=%s\n", getenv("PATH"));
	if (qtd_comandos == 2)
=======
	//puts("RETORNO:");
	char **teste = t_env_to_envp(env);
	/* for (int i = 0; teste[i]; i++)
		printf("linha %d: %s\n", i+1, teste[i]);
	puts("AQUI");  */

	int pid = fork();
	if (pid == 0)
	{
		command = ft_split(input, ' ');
		restore_inner_spaces(command);
		path = return_path(env);
		if (path == NULL)
			return ;
		splited_path = ft_split(path + 5, ':');
		building_command_path(splited_path, command[0]);
		line = check_execute_file(splited_path);
		if (line == -1)
			printf("Command not found!\n");
		else
		{
			execve(splited_path[line], command, teste);
		}
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}

void	clean_inner_spaces(char *input)
{
	while (*input)
>>>>>>> 711d8bc9ba635aa730878fda7f34c98ca9727569
	{
		int fds[2];

		if (pipe(fds) == -1) {puts("DEU RUIM"); return ;}
		int pid = fork();
		if (pid == 0)
		{
			int neto = fork();
			if (neto == 0)
			{
				// executa 1º ls
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
				remove_quotes(get_index(0, comandos));
				command = ft_split(get_index(0, comandos), ' ');
				restore_inner_spaces(command);
				path = return_path(env);
				if (path == NULL)
					return ;
				splited_path = ft_split(path + 5, ':');
				building_command_path(splited_path, command[0]);
				line = check_execute_file(splited_path);
				if (line == -1)
					printf("Command not found!\n");
				else
				{
					execve(splited_path[line], command, teste);
				}
				exit(127);
				execve("/usr/bin/ls", (char *[]){"ls", NULL}, NULL);
			}
			else
			{
				// executa 2º ls
				dup2(fds[0], STDIN_FILENO);
				close(fds[1]);
				close(fds[0]);
				remove_quotes(get_index(1, comandos));
				command = ft_split(get_index(1, comandos), ' ');
				restore_inner_spaces(command);
				path = return_path(env);
				if (path == NULL)
					return ;
				splited_path = ft_split(path + 5, ':');
				building_command_path(splited_path, command[0]);
				line = check_execute_file(splited_path);
				if (line == -1)
					printf("Command not found!\n");
				else
				{
					execve(splited_path[line], command, teste);
				}
				exit(127);
				execve("/usr/bin/cat", (char *[]){"cat", NULL}, NULL);
			}
			waitpid(neto, NULL, 0);
		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(pid, NULL, 0);
			//waitpid(pid, NULL, 0);
		}
	}
	else while (comandos)
	{
		printf("Comando: %s \n", comandos->var);
		comandos = comandos->next;
	}
}

void	execute(char *input, t_env *env)
{
	char	**command;
	char	**splited_path;
	char	*path;
	char	*aux_char;
	int		line;

	//puts("RETORNO:");
	char **teste = t_env_to_envp(env);
	/* for (int i = 0; teste[i]; i++)
		printf("linha %d: %s\n", i+1, teste[i]);
	puts("AQUI");  */

	int pid = fork();
	if (pid == 0)
	{
		command = ft_split(input, ' ');
		restore_inner_spaces(command);
		path = return_path(env);
		if (path == NULL)
			return ;
		splited_path = ft_split(path + 5, ':');
		building_command_path(splited_path, command[0]);
		line = check_execute_file(splited_path);
		if (line == -1)
			printf("Command not found!\n");
		else
		{
			execve(splited_path[line], command, teste);
		}
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}
=======
int	minishell(t_env *env)
{
	char	*input;
	char	cwd[4096];
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	env = build_env_list(envp);
	envp = NULL;
	printf("%p\n", envp);
	while (1)
	{
		input = read_input("Digite o comando > ");
		if (has_unclosed_quotes(input))
			print_error();
		// Dividir por pipes
		clean_inner_spaces(input);
		
	/* 	puts("Lista INICIAL:");
		for (t_env *aux = env; aux; aux = aux->next)
			printf("%s\n", aux->var);  */
		if (has_pipe(input))
			execute_multiple(input, env);
		else
		{
			remove_quotes(input);
			execute(input, env);
		}
		free(input);
	}
	return (0);
}
=======
	return (minishell(list));
}
>>>>>>> Stashed changes
