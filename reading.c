#include "shell.h"

/**
 * read_line - Read the input by the User From stdin
 *
 * Return: Input
 */

char *read_line()
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t len;

	len = getline(&line, &bufsize, stdin);
	if (len == -1)
	{
		if (feof(stdin))
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else if (len == 1)
  {
    free(line);
  }
  else
  {
    line[strlen(line)-1] = '\0';
  }

	return (line);
}
