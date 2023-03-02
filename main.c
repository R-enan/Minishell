
#include "header.h"

void	restore_inner_spaces(char **command)
{
	int	line;
	int col;

	if (command)
	{
		line = 0;
		while (command[line])
		{
			col = 0;
			while (command[line][col])
			{
				if (command[line][col] == -1)
					command[line][col] = ' ';
				col++;
			}
			line++;
		}
	}
}

char	*return_path(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (!strncmp(aux->var, "PATH", 4))
			return (aux->var);
		aux = aux->next;
	}
	return (NULL);
}

void	building_command_path(char **splited_path, char *command)
{
	int		line;
	char	*aux;

	line = 0;
	while(splited_path[line])
	{
		aux = ft_strjoin(splited_path[line], "/");
		free(splited_path[line]);
		splited_path[line] = aux;
		aux = ft_strjoin(splited_path[line], command);
		free(splited_path[line]);
		splited_path[line] = aux;
		line++;
	}
}

int	check_execute_file(char **list_files)
{
	int	line;

	line = 0;
	while(list_files[line])
	{
		if (!access(list_files[line], X_OK))
			return (line);
		line++;
	}
	return (-1);
}

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

void	clean_inner_spaces(char *input)
{
	while (*input)
	{
		if (*input == '\'' && *++input)
		{
			while (*input != '\'')
			{
				if (*input == ' ')
					*input = -1;
				input++;
			}
		}
		else if (*input == '"' && *++input)
		{
			while (*input != '"')
			{
				if (*input == ' ')
					*input = -1;
				input++;
			}
		}
		input++;
	}
}

char	*read_input(char *terminal)
{
	return (readline(terminal));
}

void	add_back(char *item, t_env **list)
{
	t_env	*new;
	t_env	*aux;

	if (!list)
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	new->var = item;
	new->next = NULL;
	if (list[0] == NULL)
	{
		*list = new;
		return ;
	}
	aux = *list;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;
}

t_env	*build_env_list(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			add_back(envp[i], &env);
			i++;
		}
		return (env);
	}
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
