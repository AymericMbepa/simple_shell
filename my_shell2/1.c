#include "hlsh.h"

char *lsh_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t line_len;

	line_len = getline(&line, &bufsize, stdin);
	if (line_len == -1)
	{
		if (feof(stdin))
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO,"\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else if (line_len == 1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		line[strlen(line)-1] = '\0';
	}
	return (line);
}
