#include "shell.h"

/**
 * parse - function that separate commande line
 * @buf: command line to separate
 * @av: array of string that contain all arguments passed to the programm
 *
 * Return: void
 */

void parse(char *buf, char *av[512])
{
	int i = 0;
	char *token;

	token = strtok(buf, " ");
	for (; i < 512; i++)
		av[i] = NULL;

	i = 0;
	while (token != NULL)
	{
		av[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
}
