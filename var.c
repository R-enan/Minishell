#include "header.h"

int	main()
{
	if (chdir(getenv("HOME")))
		perror("Deu ruim");
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

/* 
COMO ASSIM ISSO SÃO DOIS ERROS DIFERENTES??????!?!?!!!1111111111

cat < gasjkgbuagbuia | ls > gfiahghaiga
ASS: Andrey
*/