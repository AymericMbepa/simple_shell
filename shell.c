#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define _GNU_SOURCE

/**
 * main - entry point
 *
 * Return: always 0 succeed
 */

int main()
{
	extern char **environ;
	char **av = malloc(2 * sizeof(char*));
	pid_t pid;
	int statut;
	char *line = NULL;
	size_t size = 0;
	av[0] = line;
	av[1] = NULL;

	while(1)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("#cisfun$ ");
			if (getline(&line, &size, stdin) < 0)
			{
				fprintf(stderr, "fail to get command line");
				exit(1);
			}
			if (execve(av[0], av, environ) == -1)
				perror("./shell");
		}
		else
			wait(&statut);
	}
	return(0);
}
