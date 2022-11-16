#include "shell.h"

/**
 * processing - Execute simple shell command
 * @args: parsed command
 * @line: Input command
 * @counter: Execute time case of command Error
 * @av: Program Name
 * Return: 1 or -1 or 0
 */

int processing(char **args, char *line, int counter, char **av)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			msg_error(args[0], counter, av);
			free(line);
			free(args);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}


/**
 * msg_error - print the error msg
 * @cmd: input command
 * @counter: count loop
 * @av: program name
 */

void msg_error(char *cmd, int counter, char **av)
{
	char c;

	c = counter + '0';
	write(STDOUT_FILENO, av[0], strlen(av[0]));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd, strlen(cmd));
	write(STDOUT_FILENO, ": not found\n", 12);
}

