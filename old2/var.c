#include "header.h"

/**
 * @param input The input command to check
 * @brief Checks if the input has a variable name to expand. 
 * @return The pointer where begins the var name.
 * @returns NULL, otherwise
 */
char	*find_var(char *input)
{
	if (!input)
		return (NULL);
	while (*input)
	{
		if (*input == '\'')
			input = ft_strchr(input + 1, *input);
		if (*input == '"')
		{
			while (*++input != '"')
			{
				if (*input == '$')
					return (input + 1);
			}
		}
		if (*input == '$')
			return (input + 1);
		input++;
	}
	return (NULL);
}

/**
 * @param start The pointer where begin the name of var
 * @brief Allocate with malloc the name of the var that begins with the pointer send as argument, return NULL in case of error
 */
char	*get_var_name(char *start)
{
	char	*var;
	char	*end;

	if (!start)
		return (NULL);
	end = start;
	while (ft_isalpha(*end) || *end == '_')
		end++;
	var = ft_substr(start, 0, end - start);
	if (!var)
		return (NULL);
	return (var);
}

/**
 * @param var Var name to check if it's in list
 * @param env List of vars
 * @brief Checks if the env list has a value of var 
 * @returns A pointer to the value of var in list or NULL if not find the var name.
 */
char	*get_value_of_var(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->var, var, ft_strlen(var) + 1) == '=')
			return (env->var + ft_strlen(var) + 1);
		env = env->next;
	}
	return (NULL);
}

/**
 * @param input The input string with the command
 * @param env The list of ambient variables
 * @brief Function that expand variables in the input command that must be expanded and frees the old input.
 * @return The new allocated string with the new values after the expansion.
 */
char	*expand_variables(char *input, t_env *env)
{
	char	*var_start;
	char	*var_name;
	char	*value;
	char	*temp;

	var_start = find_var(input);
	if (!var_start)
		return (input);
	var_name = get_var_name(var_start);
	if (!var_name)
		return (input);
	value = get_value_of_var(var_name, env);
	if (!value)
	{
		ft_memmove(var_start - 1, var_start + ft_strlen(var_name), ft_strlen(var_start + ft_strlen(var_name)) + 1);
		return (expand_variables(input, env));
	}
	temp = malloc(var_start - input + \
		ft_strlen(value) + (ft_strlen(var_start) - ft_strlen(var_name)));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, input, var_start - input);
	ft_strlcpy(temp + ft_strlen(temp), value, ft_strlen(value) + 1);
	ft_strlcpy(temp + ft_strlen(temp), var_start + ft_strlen(var_name), \
			ft_strlen(var_start + ft_strlen(var_name)) + 1);
	write(1, temp, ft_strlen(temp));
	write(1, "AQUI\n", 5);
	free(input);
	input = temp;
	return (expand_variables(temp, env));
}
