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
				if (*input == '$' && \
				(ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
					return (input + 1);
		}
		if (*input == '$'
			&& (ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
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
	char	*name;
	char	*end;

	if (!start)
		return (NULL);
	end = start;
	if (*end == '?')
		end++;
	else
		while (ft_isalnum(*end) || *end == '_')
			end++;
	name = ft_substr(start, 0, end - start);
	if (!name)
		return (NULL);
	return (name);
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
/*char	*expand_variables(char *input, t_env *env)
{
	char	*name;
	char	*value;
	char	*temp;
	char	*new;

	temp = find_var(input);
	if (!temp)
		return (input);
	name = get_var_name(temp);
	if (!name)
		return (input);// Return NULL????
	value = get_value_of_var(name, env);
	new = malloc(temp - input + ft_strlen(value) + ft_strlen(temp + ft_strlen(name)));
	if (!new)
		return (NULL);
	ft_strlcpy(new, input, temp - input);
	ft_strlcpy(new + ft_strlen(new), value, ft_strlen(value) + !(value == NULL));
	ft_strlcpy(new + ft_strlen(new), temp + ft_strlen(name), ft_strlen(temp + ft_strlen(name)) + 1);
	free(input);
	input = new;
	free(name);
	return (expand_variables(input, env));
}*/

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
	temp = malloc(var_start - input + (!value) +\
		ft_strlen(value) + (ft_strlen(var_start) - ft_strlen(var_name)));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, input, var_start - input);
	ft_strlcpy(temp + ft_strlen(temp), value, ft_strlen(value) + 1);
	ft_strlcpy(temp + ft_strlen(temp), var_start + ft_strlen(var_name), \
			ft_strlen(var_start + ft_strlen(var_name)) + 1);
	free(input);
	free(var_name);
	input = temp;
	return (expand_variables(input, env));
}

/*char	*expand_variables(char *input, t_env *env)
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
	/ *if (!value)
		ft_memmove(var_start - 1, var_start + ft_strlen(var_name), ft_strlen(var_start + ft_strlen(var_name)) + 1);
	else//	return (expand_variables(input, env));* /
	temp = malloc(var_start - input + (!value) +\
		ft_strlen(value) + (ft_strlen(var_start) - ft_strlen(var_name)));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, input, var_start - input);
	ft_strlcpy(temp + ft_strlen(temp), value, ft_strlen(value) + 1);
	ft_strlcpy(temp + ft_strlen(temp), var_start + ft_strlen(var_name), \
			ft_strlen(var_start + ft_strlen(var_name)) + 1);
	free(input);
	input = temp;
	return (expand_variables(input, env));
}
*/
/* // Erro com "   $INEXISTENTE"
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
	free(input);
	return (expand_variables(temp, env));
}
*/