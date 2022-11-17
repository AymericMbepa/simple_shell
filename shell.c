#include "shell.h"


/**
 * main - Simple shell enter point
 * @argc: Argument count
 * @argv: arguments list
 * Return: Exit value by status
 */

int main(int argc __attribute__((unused)), char *argv[])
{
	char *buffer; 
	char *check_exit = "exit";
	pid_t pid;
	int status, counter = 0;

	/*Use getline to accept commmands*/
	while (1)
	{
		counter++;
		if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2);
		buffer = read_line ();
		if (strcmp(buffer, check_exit) == 0)                                                                                          
		{                                                                                                                              
			free(buffer);                                                                                                          
			return (0);                                                                                                            
		}                                                                                                                              
		pid = fork();                                                                                                                  
		if (pid == -1)                                                                                                                 
		{                                                                                                                              

			free(buffer);                                                                                                         
			return (-1);                                                                                                           
		}                                                                                                                              
		if (pid == 0)                                                                                                                  
			execute_program(buffer, argv);                                                                                         
		else                                                                                                                           
			wait(&status);
	}
	free(buffer);
	return (0);
}


/**
 * execute_program - Execute simple shell command
 * @buffer: Input command
 * @argv: list of args
 */

void execute_program(char *buffer, char *argv[])
{
	int i, number_of_words = 1, value;
	char **argvec, **divided_string;

	/*Use strtok to split the buffer with space as separator*/
	for (i = 0; i < (int)strlen(buffer); i++)
	{
		if (buffer[i] == ' ')
			number_of_words++;
	}
	divided_string = malloc(sizeof(char *) * number_of_words);
	if (divided_string == NULL)
		exit(1);
	/*Put the split string inside argv array*/
	argvec = split_string(buffer, divided_string);
	/*Run execve on the command*/
	value = execvp(argvec[0], argvec);
	if (value == -1)
	{
		free(divided_string);
		perror(argv[0]);
		printf("$ ");
	}
	free(buffer);
}


/**
 * split_strings - split line of Input
 * @string: line of cmd to Parse
 * @divided_string: split
 * Return:  Array of char
 */

char **split_string(char *string, char **divided_string)
{
	/*create divided_string variable*/
	/*char *splits;*/
	/*char *sep;*/
	/*int i = 0;*/

	/*sep = " ";*/
	/*use strtok to get first token*/
	/*splits = strtok(string, sep);*/
	/*while token isn't equal to NULL*/
	divided_string[0] = string;
	divided_string[1] = NULL;

	return (divided_string);
}


/**
 * read_line - Read the input by the User From stdin
 *
 * Return: Input
 */

char *read_line(void)
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
		line[strlen(line) - 1] = '\0';
	}

	return (line);
}

