#include "header.h"

int	has_redirect_error(char *input)
{
	while (input && *input)
	{
		if (*input == '<' || *input == '>')
		{
			input++;
			if (*input == input[-1])
				input++;
			while (ft_is_in_set(*input, IS_SPACE_SET))
				input++;
			if (*input == '<' || *input == '>' || *input == '|' || *input == 0)
				return (1);
		}
		else
		{
			if (*input == '\'' || *input == '"')
				input = ft_strchr(input + 1, *input);
			if (input)
				input++;
		}
	}
	return (0);
}

int	count_redirects(char **command, char redirect)
{
	int	redirects_qtd;

	redirects_qtd = 0;
	while (command && *command)
	{
		if (**command == redirect)
			redirects_qtd++;
		command++;
	}
	return (redirects_qtd);
}

t_env	*get_redirects(char **command, char redirect)
{
	char	**temp;
	t_env	*inputs;
	t_env	*aux;

	if (!command)
		return (NULL);
	inputs = NULL;
	while (*command)
	{
		if(**command == redirect)
		{
			aux = new_node(*command);
			if (!aux)
			{
				free_list(&inputs);
				return (NULL);
			}
			add_back(&inputs, aux);
			temp = command + 1;
			free(*command);
			*command = NULL;
			command = temp;
			while (*temp)
			{
				temp = temp + 1;
				temp++;
			}
		}
		else
			command++;
	}
	return (inputs);
}

void	set_input(t_redirects *redirects)
{
	t_env	*aux;
	int		fd;

	aux = redirects->inputs_redirects;
	fd = 0;
	while (aux)
	{
		// Verificar se é Heredoc
		if (*aux->var == '<' && aux->var[1] == '<')
		{
			// Open Heredoc
			// fd = o conteúdo do heredoc // putendl
		}
		else
		{
			fd = open(aux->var + 2, O_RDONLY);
			if (fd < 0)
			{
				perror(aux->var + 2);
				break ;
			}
		}
		if (!aux->next)
			break ;
		close(fd);
		aux = aux->next;
	}
	free_list(&redirects->inputs_redirects);
	redirects->fd_input = fd;
}

void	set_output(t_redirects *redirects)
{
	t_env	*aux;
	int		fd;

	aux = redirects->outputs_redirects;
	fd = 1;
	while (aux)
	{
		// Verificar se é Append
		if (*aux->var == '>' && aux->var[1] == '>')
			fd = open(aux->var + 3, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
		{
			fd = open(aux->var + 2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			ft_putstr_fd("Entrei aqui. FD = ", 1);
			ft_putnbr_fd(fd, 1);
		}
		if (fd < 0)
		{
			perror(aux->var + 2 + (aux->var[1] == '>'));
			break ;
		}
		if (!aux->next)
			break ;
		close(fd);
		aux = aux->next;
	}
	free_list(&redirects->outputs_redirects);
	redirects->fd_output = fd;
}


/*****
 * Em ASCII '<' == 60 e '>' == 62
 * access expande ..
 * .. É '..: comando not found!'
 * ../ É '../: Is a directory'
 * path/file_that_not_execute 'Permission denied'
 */
/*
int	count_redirects(char **command)
{
	int	redirects;

	redirects = 0;
	while (command && *command)
	{
		if (**command == '<' || **command == '>')
			redirects++;
		command++;
	}
	return (redirects);
}




void	remove_redirects(char **command, char **redirects)
{
	int	index;
	int	adjust;

	if (!command || !redirects)
		return ;
	index = 0;
	while (command[index])
	{
		if (*command[index] == '<' || *command[index] == '>')
		{
			*redirects++ = command[index];
			adjust = index;
			while (command[adjust])
			{
				command[adjust] = command[adjust + 1];
				adjust++;
			}
		}
		else
			index++;
	}
}
void	remove_redirects(char **command, char **redirect_matrix, char redirect)
{
	int	index;
	int	adjust;

	if (!command || !redirect_matrix)
		return ;
	index = 0;
	while (command[index])
	{
		if (*command[index] == redirect)
		{
			*redirect_matrix++ = command[index];
			adjust = index;
			while (command[adjust])
			{
				command[adjust] = command[adjust + 1];
				adjust++;
			}
		}
		else
			index++;
	}
}



void	adjust_redirects_matrix(char **redirects)
{
	int		index;
	int		adjust;
	char	*temp;

	if (!redirects)
		return ;
	index = 0;
	while (redirects[index] && redirects[index + 1])
	{
		if (redirects[index] > redirects[index + 1])
		{
			adjust = index;
			while (adjust >= 0)
			{
				temp = redirects[adjust + 1];
				redirects[adjust + 1] = redirects[adjust];
				redirects[adjust] = temp;
				adjust--;
				if (adjust >= 0 && redirects[adjust] <= redirects[adjust + 1])
					break ;
			}
		}
		else
			index++;
	}
}
*/