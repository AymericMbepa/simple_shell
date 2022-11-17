#include "hlsh.h"


char **lsh_spilt_line(char *line, const char *DELIM)
{
	int bufsize = LSH_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize*sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
    	/*write(STDOUT_FILENO, tokens[position], strlen(tokens[position]));
    write(STDOUT_FILENO, "\n", 1);*/
		position ++;

		if (position >= LSH_BUFSIZE)
		{
			bufsize += LSH_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}
