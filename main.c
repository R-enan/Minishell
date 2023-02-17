
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

void	execute(char *input, t_env *env)
{
	char	**command;
	char	**splited_path;
	char	*path;
	char	*aux_char;
	int		line;

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
		execve(splited_path[line], command, NULL);
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

	input = read_input("Digite o comando > ");
	if (has_unclosed_quotes(input))
		print_error();
	// Dividir por pipes
	clean_inner_spaces(input);
	remove_quotes(input);
	env = build_env_list(envp);
	execute(input, env);
	free(input);
	return (0);
}
