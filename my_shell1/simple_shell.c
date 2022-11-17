#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	char *buf = NULL;
	char *argv[] = {NULL, "-l", NULL};
	size_t n = 10;

	printf("#cisfun ");
	getline(&buf, &n, stdin);
	argv[0] = buf;
	printf("%s\n", argv[0]);
	if (execve(argv[0], argv, NULL) == -1)
		printf("Erreur ca ne marche pas\n");
	free(buf);
	return (0);
}
