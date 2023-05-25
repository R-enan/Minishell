#include "header.h"

int	ft_error_message(char *message, int code)
{
	ft_putendl_fd(message, 2);
	return (code);
}
