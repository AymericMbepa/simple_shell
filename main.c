#include "shell.h"

/**
 * main - emplement other version of shell
 *
 * return: always 0
 */

int main()
{
	char *av[512];
	char *buf;
	size_t n = 10;

	buf = (char *)malloc(sizeof(char) * n);
	for(;;)
	{
		printf("#cisfun$ ");
		if (getline(&buf, &n, stdin) == -1)
			perror("Error");
		parse(buf, av);
		execute(av[0], av);
	}
	return (0);
}
