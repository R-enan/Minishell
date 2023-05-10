#include "header.h"

char	**list_to_pointer(t_env *list)
{
	char	**pointer;
	size_t	index;

	index = list_size(list);
	if (index == 0)
		return (NULL);
	pointer = (char **)malloc(sizeof(char *) * (index + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (list)
	{
		pointer[index] = list->var;
		list = list->next;
		index++;
	}
	pointer[index] = NULL;
	return (pointer);
}
/*
char	*find_var(char *var_name, t_env *env)
{
	while (env)
	{
		if(ft_strncmp(env->var, var_name, ft_strlen(var_name) + 1) == '=')
			return (env->var + ft_strlen(var_name));
		env = env->next;
	}
	return (NULL);
}
*/
void	expand_variables(char **command, t_env *env)
{
	char	*tmp;
	char	*var;
	char	*aux;
	char	*line;

	if (command == NULL || *command == NULL)
		return ;
	tmp = command;
	while(command)
	{
		while (*tmp)
		{
			if (*tmp == '\'')
				tmp = ft_strchr(tmp + 1, '\'');
			if (*tmp == '$')
			{
				var = tmp + 1;
				while (ft_isalpha(*var) || *var == '_')
					var++;
				var = ft_substr(tmp + 1, 0, var - tmp);
				aux = find_var(var, env);
				line = malloc(tmp);
			}
			tmp++;
		}
		command++;
	}
}
/*
void	expand_variable(char **command, size_t index, t_env *env)
{
	char	*tmp;
	char	*var_name;
	char	*new_input;
	char	*value;

	tmp = command[index];
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp + 1, '\'');
		if (*tmp == '$')
		{
			var_name = ++tmp;
			while (ft_isalpha(*var_name) || *var_name == '_') // Verificar nomes do tipo NOME_DE_VAR'mais texto qualquer
				var_name++;
			var_name = ft_substr(tmp, 0, var_name - tmp + 1);
			// pegar valor da variável
			value = find_var(var_name, env);
			// start | onde começa $ | Valor da variável | onde termina o nome da variável
			// 1 - mallocar uma string grandona (original + size da variável)
			new_input = (char *)malloc(ft_strlen(command[index]) - (ft_strlen(var_name) + 1) + ft_strlen(value) + 1);
			free(var_name);
			// 2 - copia normal a original (até antes do $)
			ft_memmove(new_input, command[index], tmp - command[index] - 1);
			new_input[tmp - command[index] - 1] = 0;
			// 3 - memmove variável
			ft_memmove(new_input + ft_strlen(new_input), value, ft_strlen(value) + 1);
			// 4 - memmove no resto da string
			while (ft_isalpha(*tmp) || *var_name == '_')
				tmp++;
			if (*tmp)
				ft_memmove(new_input + ft_strlen(new_input), tmp, ft_strlen(tmp) + 1);
			// 5 - free
			free(command[index]);
			command[index] = new_input;
		}
		tmp++;
	}
}
*/


char	*find_var(char *var_name_start, char *var_name_end, t_env *env)
{
	while (env)
	{
		if(ft_strncmp(env->var, var_name_start, var_name_end - var_name_start + 1) == '=')
			return (env->var + (var_name_end - var_name_start));
		env = env->next;
	}
	return (NULL);
}

void	expand_variable(char **command, t_env *env)
{
	char	*tmp;
	char	*var_name_start;
	char	*var_name_end;
	char	*new_input;
	char	*value;

	tmp = *command;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = ft_strchr(tmp + 1, '\'');
		if (*tmp == '$')
		{
			var_name_start = tmp + 1;
			var_name_end = var_name_start;
			while (ft_isalpha(*var_name_end) || *var_name_end == '_') // Verificar nomes do tipo NOME_DE_VAR'mais texto qualquer
				var_name_end++;
			// pegar valor da variável
			value = find_var(var_name_start, var_name_end, env);
			// start | onde começa $ | Valor da variável | onde termina o nome da variável
			// 1 - mallocar uma string grandona (original + size da variável)
			new_input = (char *)malloc(tmp - *command + ft_strlen(value) + ft_strlen(var_name_end) + 1);
			// 2 - copia normal a original (até antes do $)
			ft_memmove(new_input, *command, tmp - *command);
			new_input[tmp - *command] = 0;
			// 3 - memmove variável
			if (value)
				ft_memmove(new_input + ft_strlen(new_input), value, ft_strlen(value) + 1);
			// 4 - memmove no resto da string
			if (*var_name_end)
				ft_memmove(new_input + ft_strlen(new_input), var_name_end, ft_strlen(var_name_end) + 1);
			// 5 - free
			free(*command);
			*command = new_input;
			tmp = *command;
		}
		tmp++;
	}
}


void	only_command(char *input, t_env *env)
{
	char	**command;
	char	**path;
	char	*tmp;
	size_t	index;

	if (input == NULL)
		return ;
	command = ft_split(input, ' ');
	if (command == NULL)
		return ;
	index = 0;
	// expandir variáveis (se necessário)
	while (command[index])
	{
		expand_variable(&command[index], env);
		ft_restore_inner
		index++;
	}

	remove_quotes(input);
	// Restaurar espaços

	execve(path, command, list_to_pointer(env));
}

int	minishell(t_env	*env)
{
	char	*input;

	env = NULL;
	while (1)
	{
		input = readline("Digite o comando> ");
		if (has_unclosed_quotes(input))
			print_error();
		clean_inner_spaces(input);
		if (has_pipe(input))
		{
			if (has_invalid_pipe(input))
			{
				write(1, "syntax error near unexpected token `|'\n", 39);
			}
			else
			{
				// Multiple commands
			}
		}
		else
		{
			// Only command
		}
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
