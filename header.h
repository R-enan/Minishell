

#ifndef HEADER_H
# define HEADER_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "libft.h"

struct s_env
{
	char			*var;
	struct s_env	*next;
};

typedef struct s_env t_env;


#endif