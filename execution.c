#include "header.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*int	ft_command_is_with_path(char *command)
{
	if (!command)
		return (0);
	if (ft_strchr(command, '/'))
		return (1);
	return (0);
}

int	ft_command_is_directory(char *command)
{

}
*/
int	main()
{
	char text[101] = "Texto qualquer digitado\n";

	int fd = open("search.c", O_RDONLY);
	int fd2 = open("saida", O_CREAT | O_WRONLY, 0644);
	int bkp_input = dup(0);
	int bkp_output = dup(1);
	
	
	dup2(fd, 0);
	dup2(fd2, 1);

	close(fd);
	close(fd2);

	read(0, text, 100);
	write(1, text, 24);

	dup2(bkp_input, 0);
	dup2(bkp_output, 1);


	close (bkp_input);
	close(bkp_output);


	write(1, "BATATA\n", 7);

	close(0);
	close(1);
}