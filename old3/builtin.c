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
	long	num;

	if (!args || !args[1])
	{
		free_matrix((void **)args);
		exit(0);
	}
	if (args[2] != NULL)
	{
		// Many arguments
	}
	else if (is_valid_number(args[1]))
	{
		num = ft_atoll(args[1]);
		free_matrix((void **)args);
		exit(num);
	}
	else
	{
		// Invalid number
	}
	free_matrix((void **)args);
	exit(2);
}

/*-------------- cd ----------------*/
void	ft_cd(char **args)
{
	if (!args)
		return ;
	if (!args[1])
	{
		// Ir pra HOME (if HOME unseted, doesn't work)
		return ;
	}
	if (args[2])
	{
		// Too many arguments
		return ;
	}
	//if (args[1][0] == '~') // Vai pra HOME de um jeito ou de outro (SEMPRE FUNCIONA)
	//if (args[1][0] == '-') // Ir pra OLDPWD (if OLDPWD unseted, doesn't work)
	if (chdir(args[1]))
	{
		// deu erro
	}
}

/*-------------- echo ----------------*/
void	ft_echo(char **args)
{
	int	index;
	int	line_feed;
	int	validate;

	if (!args)
		return ;
	index = 0;
	validate = index;
	if (args[1] && args[1][0] == '-')
		while (args[1] && args[1][++index] == 'n')
			validate = 1;
	line_feed = 1;
	if (args[1] && !args[1][index] && validate)
		line_feed++;
	args += line_feed;
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		if (args[1])
			write(1, " ", 1);
		args++;
	}
	if (line_feed - validate == 0 || validate == 0)
		write(1, "\n", 1);
}

/*-------------- pwd ----------------*/
void	ft_pwd(char **args)
{
	char	cwd[4096];

	if (!args)
		return ;
	args++;
	if (*args)
	{
		while (*args)
		{
			if (args[0][0] == '-')
				break;
			args++;
		}
		if (!*args)
			ft_putendl_fd("pwd: ignoring non-option arguments", 1);
	}
	if (!*args)
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else
	{
		ft_putendl_fd("Is really hard try to read the pdf. I understand..", 1);
		ft_putstr_fd("YOU maybe, work with options. I don't!", 1);
		ft_putendl_fd(" (ง•̀ _´•̀)ง (╬≖_≖)", 1);
	}
	//PATH_MAX
}

/*-------------- env ----------------*/
void	ft_env(char **args, t_env *env)
{
	if (!args)
		return ;
	if (args[1] != NULL)
	{
		ft_putstr_fd("YOU JUST HAVE ONE JOB! Read The F*@# PDF!!!", 1);
		ft_putendl_fd("⸨◣_◢⸩", 1);
		ft_putstr_fd("He explicit says that we DON'T have to implement ", 1);
		ft_putstr_fd("env with some options or arguments. Respect that!", 1);
		ft_putendl_fd("\nGODAMIT!!!┌∩┐(◣_◢)┌∩┐\n\n"\
		"Have a nice day! (｡^‿^｡) ٩(◕‿◕)۶", 1);
		return ;
	}
	while (env)
	{
		if (ft_strchr(env->var, '='))
			ft_putendl_fd(env->var, 1);
		env = env->next;
	}
}

/*-------------- export ----------------*/
void	ft_export(char **args, t_env **env)
{
	char *name;
	char *var;
	char **replace;
	t_env *aux;

	while (args[1])
	{
		name = get_var_name(args[1]);
		if (get_value_of_var(name, *env))
		{
			var = find_var(name);
			free(var);
			replace = &var;
			*replace = ft_strdup(args[1]);
		}
		else
		{
			//if (check_valid_var_name(name))
			{
				aux = new_node(args[1]);
				if (!aux)
					return ;// (ENOMEM);
				add_back(env, aux);
			}
		}
		args++;
	}
}

/*-------------- unset ----------------*/
void	ft_unset(char **args, t_env **env)
{

}
