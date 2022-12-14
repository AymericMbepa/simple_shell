#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSH_BUFSIZE 1024
#define LSH_TOK_DELIM " \t\r\n\a"

char *lsh_read_line()
{
	int bufsize = LSH_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char)*bufsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "lsh allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "lsh allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **lsh_spilt_line(char *line)
{
	/*int bufsize = LSH_BUFSIZE;
	position = 0;*/
	char **tokens = malloc(2 * sizeof(char*));
	/*char *token;*/

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	tokens[0] = line;
	tokens[1] = NULL;
	/*token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
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
		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;*/
	return tokens;
}

int lsh_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process*/
		if (execve(args[0], args, NULL) == -1)
		{
			perror("./shell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		/* Error forking*/
		perror("./shell");
	}
	else
	{
		/* Parent process*/
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_execute(char **args)
{

	if (args[0] == NULL)
	{
		/* An empty command was entered.*/
		return 1;
	}
	return lsh_launch(args);
}

void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("#cisfun$ ");
		line = lsh_read_line();
		args = lsh_spilt_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while(status);
}

/**
 * main - execute programme
 */
int main(__attribute__((unused))int argc, __attribute__((unused))
	 char const *argv[])
{
	lsh_loop();
	return EXIT_SUCCESS;
}
