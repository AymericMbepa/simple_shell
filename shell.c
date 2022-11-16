#include "shell.h"

/**
 * main - Simple shell enter point
 * @ac: Argument count
 * @av: arguments list
 * @env: list of environment variables
 * Return: Exit value by status
 */

int main(__attribute__((unused)) int ac, char **av, char **env)
{
	char *line;
	char **args;
	int counter = 0, status = 1, st = 0;

	while (status)
	{
		counter++;
		prompt();
		line = read_line();
		if (line[0] == '\0')
			continue;
		args = split_line(line);
		st = processing(args, line, counter, av);
		free_all(st, line, args);
	}

	return (0);
}


/**
 * prompt - display the simple shell prompt
 *
 */

void prompt(void)
{
	char *str = {"#cisfun$ "};
	int len = strlen(str);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, str, len);
	}
}

/**
 * free_all - free allocated memory
 * @st: unused
 * @line: input command
 * @args: parsed command
 *
 */

void free_all(__attribute__((unused)) int st, char *line, char **args)
{
	free(line);
	free(args);
}
