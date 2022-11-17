#include "shell.h"

/**
 * execute - execute command passed to parameter
 * @cmp: command name
 * @av: an array of strings that contain argument
 *
 * Return: void
 */

void execute(char *cmd, char *av[])
{
	pid_t pid;
	int statut;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, av, NULL);
		fprintf(stderr, "%s: not found\n", cmd);
		exit(1);
	}
	while (wait(&statut) != pid);
}
