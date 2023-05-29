#include "header.h"

// Alternativo é retornar um ponteiro de função que marca a função que irei executar
int	ft_is_builtin(char **command)
{
	return (!ft_strncmp(command[0], "echo", 5)
			|| !ft_strncmp(command[0], "cd", 3)
			|| !ft_strncmp(command[0], "pwd", 4)
			|| !ft_strncmp(command[0], "export", 7)
			|| !ft_strncmp(command[0], "unset", 6)
			|| !ft_strncmp(command[0], "env", 4)
			|| !ft_strncmp(command[0], "exit", 5));
}

/**
 * int (*f)(char**, int)
 * (inputs, caso sejam arquivos, são ignorados)
 */
/*
void	*ft_set_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(command[0], "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(command[0], "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(command[0], "export", 7))
		return (ft_export);
	if (!ft_strncmp(command[0], "unset", 6))
		return (ft_unset);
	if (!ft_strncmp(command[0], "env", 4))
		return (ft_env);
	if (!ft_strncmp(command[0], "exit", 5))
		return (ft_exit);
	return (NULL); // Is not a builtin command
}
*/
ft_echo(char **command, int input_fd, int output_fd)
{

}