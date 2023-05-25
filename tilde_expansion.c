#include "header.h"

int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

int	ft_check_before_tilde(char *input, char *start)
{
	if (!input || input == start)
		return (0);
	if (input < start)
		return (1);
	if (*input == '=')
	{
		if (ft_isalpha(*start) || *start == '_')
		{
			start++;
			while (ft_isalnum(*start) || *start == '_')
				start++;
		}
		else
			return (0);
	// checar variável à partir de start (O retorno deve chegar ao endereço de input)
	// "get_value_of_var" retorna ~
		if (start == input)
			return (1);
	}
	return (0);
}

int	ft_check_after_tilde(char *input)
{
	if (!input)
		return (0);
	if (!*input)
		return (1);
	/*if (ft_isalpha(*input) || *input == '_')
	{
		// check and expands USERNAME
	}
	else */if (*input == '/' || *input == ':')
	{
		return (1);
	}
	return (0);
}

char	*make_string(char *start, char *tilde_position, t_env *env)
{
	char	*string;
	char	*expansion;

	expansion = get_value_of_var("HOME", env);
	if (!expansion)
		return (start);
	/*if (start == tilde_position)
	{
		string = malloc(ft_strlen(expansion) + ft_strlen(start + 1) + 1);
		if (!string)
		ft_strlcpy(string, expansion, ft_strlen(expansion) + 1);
		ft_strlcpy(string + ft_strlen(string), tilde_position + 1, ft_strlen(tilde_position));
	}
	else*/
	{
		string = malloc(tilde_position - start + ft_strlen(expansion) + ft_strlen(tilde_position) + 1);
		if (!string)
			return (start); // Or return start?
		ft_strlcpy(string, start, tilde_position - start + 1);
		ft_strlcpy(string + ft_strlen(string), expansion, ft_strlen(expansion) + 1);
		ft_strlcpy(string + ft_strlen(string), tilde_position + 1, ft_strlen(tilde_position));
	}
	free(start);
	return (string);
}

/**
 * @param input The string that contais the input from user
 * @brief This function handles the tilde (~) expansion by mallocating a new string and frees the old
 * @return A new string mallocated with the tilde expansion completed; NULL if the allocation fails
 */
char	*tilde_expansion(char *input, t_env *env)
{
	char	*current;

	if (!input)
		return (NULL);
	current = input;
	while (*current)
	{
		if (*current == '\'' || *current == '"')
			current = ft_strchr(current + 1, *current);
		if (*current == '~') 
		{
			/** opções: 
			 * ~								(Home)
			 * ~USERNAME						(Pega o caminho para USERNAME que está em /etc/passwd)
			 * ~:balblabla						(Concatena a expansão com : e o resto)
			 * ~/blablabla						(Concatena a expansão com / e o resto)
			 * N0me_VAR_v471d0_=~				(Concatena o texto antes do igual com a expansão)
			 * N0me_VAR_v471d0_=~:blablabla		(Concatena o texto com a expansão)
			 * N0me_VAR_v471d0_=~/blablabla		(Concatena o texto com a expansão)
			 */
			//check_before_tilde
			//check_after_tilde
			// soma ambos os retornos e executa o comportamento correto
			if (ft_check_before_tilde(&current[-1], input)
				&& ft_check_after_tilde(&current[1]))
				return (make_string(input, current, env));
			else
				break;
				//return (NULL);
		}
		current++;
	}
	return (input);
}
