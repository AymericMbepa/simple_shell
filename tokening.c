#include "shell.h"

/**
 * split_line - split line of Input
 * @line: line of cmd to Parse
 *
 * Return:  Array of char
 */

char **split_line(char *line)
{
	char **tokens;
	int bufsize = 2;

	if (line == NULL)
		return (NULL);
	tokens =  malloc(sizeof(char *) * bufsize);
	if (!tokens)
	{
		perror("Error : Allocation error");
		return (NULL);
	}
	tokens[0] = line;
	tokens[1] = NULL;

	return (tokens);
}

