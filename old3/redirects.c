/*******
 * Para separar os redirects:
 * - Achei um, verifica se o próximo é um redirect igual. (Caso de << ou >>)
 * - Separo por espaços. ("<file" vira "< file")
 * - Insiro um -1 entre o redirect e o espaço ("< file" vira "<�file")
 * - Insiro um espaço, caso necessário
 */



/***
 * A ideia inicial é fazer write(fd, string, strlen);
 * fd vai ser:
 * - 0 (input padrão): se nenhum outro for especificado
 * - 1 (output padrão): se nenhum outro for especificado
 * - 2 (Erro padrão): Não vejo o porquê de mudar por qualquer motivo
 * - fd_input: caso ocorra a necessidade de abrir algum file descriptor
 * - fd_output: caso ocorra a necessidade de abrir algum file descriptor
 * 
 * uma função será usada pra verificar os redirects contidos na string e retirá-los do comando
 * Após isso, filtragem de aspas e enviar o comando para ser executado.
 * 
 * fd_input recebe 0, ou o fd necessário
 * fd_output recebe 1, ou o fd necessário
 * 
 * Leio e escrevo nos fds apropriados e fecho eles, caso sejam diferentes dos valores padrão
 */
#include "header.h"

void	adjust_redirects(char **command)
{
	char	*start;

	if (!command)
		return ;
	start = *command;
	while (start && *start)
	{
		if (*start == '\'' || start == '"')
			start = ft_strchr(start + 1, *start);
		if (*start == '<' && start[1] == '<')
		{
			if (start[2] != ' ')
		}
		start++;
	}
	if (start && *start)
		adjust_redirects(command);
}

int	set_input_fd(char **command)
{
	int		fd;
	char	*start;
	char	*end;

	if (!command)
		return (-1); // error
	fd = 0;
	while (*command)
	{
		if (command[0][0] == '<' && command[0][1] != '<')
		{
			// Achei um redirect
			start = &command[0][1];
			if (*start == '\0')
				start = ++command;
			end = start;
			// <infile>outfile || <infile<infile (tudo juntinho e coladinho conforme o exemplo)
			if (*end == '\'' || *end == '"')
				end = ft_strchr(end + 1, *end);
			else
				while (*end == '>' || *end == '<' || *end == '\0')
					end++;
			if (fd)
				close(fd);
			start = ft_substr(start, 0, end - start);
			if (!start)
				return (ENOMEM);
			// Verificar se o arquivo existe
			fd = open(start, O_RDONLY);
			if (fd < 0)
				return (2); // File no exziste

		}
		else if (command[0][0] == '<' && command[0][1] == '<')
		{
			// Heredoc aqui?
		}
		command++;
	}
}

int	set_output_fd(char **command)
{
	if (!command)
		return (-1); // error
	while (*command)
	{
		if (command[0][0] == '<')
		command++;	
	}
}