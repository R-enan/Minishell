#include "header.h"

int	is_builtin(char *command)
{
	return (!ft_strncmp("echo", command, 5)
			|| !ft_strncmp("cd", command, 3)
			|| !ft_strncmp("pwd", command, 4)
			|| !ft_strncmp("env", command, 4)
			|| !ft_strncmp("export", command, 7)
			|| !ft_strncmp("exit", command, 5)
			|| !ft_strncmp("unset", command, 6));
}

/*-------------- exit ----------------*/
long	ft_atoll(char *s)
{
	long	numb;
	int		sign;

	if (!s)
		return (0);
	numb = 0;
	while (ft_isspace(*s))
		s++;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (ft_isdigit(*s))
		numb = numb * 10 + *s++ - '0';
	return (numb * sign);
}

int	numb_fits_max_long(char *numb_begin, int sign)
{
	int		index;
	char	*big_long;

	if (sign == 1)
		big_long = "9223372036854775807";
	else
		big_long = "9223372036854775808";
	// Percorrer os números que são iguais {while(big_long[index] == numb_begin[index]) index++;}
	// Verificar se não estou no index 0 if (numb_begin[index] > big_long[index]) return 0
	// Checar se o dígito atual é maior do que o limite permitido àquele dígito -- se sim, return (0)
	while (big_long[index] && numb_begin[index] == big_long[index])
		index++;
	if (big_long[index] && numb_begin[index] > big_long[index])
		return (0);
	return (1);
}

int	is_valid_number(char *s)
{
	char	*numb_begin;
	int		len;
	int		sign;

	if (!s)
		return (1);
	while (ft_isspace(*s))
		s++;
	len = 0;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (*s == '0')
		s++;
	numb_begin = s;
	while (ft_isdigit(*s))
	{
		if (++len > 19)
			return (0);
		s++;
	}
	while (*s == ' ' || *s == '\t')
		s++;
	if (len == 19 && numb_fits_max_long(numb_begin, sign) == 0)
		return (0);
	return (!*s);
}

void ft_exit(char **args)
{
	if (!args)
		exit(0);
	if (args[1] != NULL)
	{
		// Many arguments
	}
	else if (is_valid_number(*args))
		exit(ft_atoll(*args));
	else
	{
		// Invalid number
	}
	exit(2);
}

/*-------------- cd ----------------*/
/*-------------- echo ----------------*/
/*-------------- pwd ----------------*/
/*-------------- env ----------------*/
void	ft_env(t_env *env)
{
	while (env)
	{
		write(1, env->var, ft_strlen(env->var));
		env = env->next;
	}
}

/*-------------- export ----------------*/
int	is_valid_var(char **input)
{
	//
	return (0);
}

void	ft_export(char **input, t_env **env)
{
	t_env	*node;

	if (is_valid_var(input))
	{
		node = new_node(*input);
		if (!node)
		{
			// allocation error
			return ;
		}
		add_back(env, node);
	}
}

/*-------------- unset ----------------*/

void	ft_unset(char **input, t_env **env)
{
	/*if ()
	{

	}*/
}