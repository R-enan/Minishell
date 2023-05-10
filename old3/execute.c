#include "header.h"

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
	//commands[line] = expand_variables(commands[line], env);
	clean_inner_spaces(commands[line]);
	if (has_pipe(input))
	{
		// Multiple commands
		while (commands[line])
		{
			//commands[line] = expand_variables(commands[line], env);
			clean_inner_spaces(commands[line]);
			line++;
		}
		free(input);
		multiple_commands(commands, env);
	}
	else
	{
		free(input);
		single_command(commands, env);
	}
	// função que vai fazer as coisas mesmo
}

int	single_command(char **command, t_env *env)
{
	char	**splitted;
	char	**paths;
	char	**envp;
	char	*path;
	int		pid;

if (!command || !*command || !**command) // Existe a possibilidade de "$> $KKKK"
{
	write(2, "Command not found!\n", 19);
	return(1);
}
	//adjust_redirects(&*command);
	splitted = ft_split(*command, ' ');
	if (!splitted)
		return (ENOMEM);
	if (!*splitted)
		return (0); // No ecxiste comando!
	free_matrix((void **)command);
	command = splitted;
	while (*command)
		restore_inner_spaces(*command++);
	// Eliminar redirects
	command = splitted;
	while (*splitted)
		remove_quotes(*splitted++);
	splitted = command; // Fazer a expansão de variáveis aqui...
	//while (*splitted)
	if (is_builtin(*command))
	{
		if (!ft_strncmp(*command, "exit", 5))
		{
			free_list(&env);
			ft_exit(command);
		}
		if (!ft_strncmp(*command, "echo", 5))
		{
			ft_echo(command);
			return (0);
		}
		if (!ft_strncmp(*command, "pwd", 4))
		{
			ft_pwd(command);
			return (0);
		}
		if (!ft_strncmp(*command, "cd", 3))
		{
			ft_cd(command);
			return (0);
		}
		if (!ft_strncmp(*command, "env", 4))
		{
			ft_env(command, env);
			return (0);
		}
	}
	//else
	{
		pid = fork();
		if (pid == 0)
		{
			envp = list_to_pointer(env);
			paths = ft_split(get_value_of_var("PATH", env), ':');
			if (!paths)
				return (1); // Não allocou, ou não existe PATH
			while (paths[pid])
			{
				path = join_path(paths[pid], command[0]);
				if (!path)
					return (ENOMEM);
				if (access(path, X_OK) == 0)
				{
					free_matrix((void**) paths);
					if (execve(path, command, envp) == -1)
					{
						// execve error
						free(path);
						free_matrix((void **)command);
						free_matrix((void **)paths);
						free_matrix((void **)envp);
						exit(2);
					}
				}
				free(path);
				path = NULL;
				pid++;
			}
			write(2, "Command not found!\n", 19);
			free_matrix((void **)command);
			free_matrix((void **)paths);
			exit(127);
		}
		else
			wait(NULL);
	}
	free_matrix((void **)command);
	return (0);
}

int	multiple_commands(char **command, t_env *env)
{
	int		index;
	int		pid;
	char	**s_command;

	if (!command)
		return (1);
	index = 0;
	while (command[index])
	{
		pid = fork();
		if (pid == 0)
		{
			s_command = split_commands(command[index]);
			exit(single_command(s_command, env));
		}
		else
			wait(NULL);
		index++;
	}
	free(command);
	return (0);
}
