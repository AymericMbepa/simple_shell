#include "main.h"

/**
 * main - create a super simple shell
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char *argv[])
{
        char *buffer, *check_exit = "exit";
        size_t buffer_size = 0;
        pid_t pid;

        buffer = malloc(sizeof(char) * buffer_size);
        if (buffer == NULL)
                exit(1);
        printf("$ ");
        /*Use getline to accept commmands*/
        while (getline(&buffer, &buffer_size, stdin) != -1)
        {
                buffer[strcspn(buffer, "\n")] = 0;
                if (strcmp(buffer, check_exit) == 0)
                {
                        free(buffer);
                        return(0);
                }
                pid = fork();
                if (pid == -1)
                {
                        free(buffer);
                        return (-1);
                }
                if (pid == 0)
                {
                    execute_program(buffer, argv);
                }
                else
                {
                        wait(NULL);
                        free(buffer);
                        buffer = malloc(sizeof(char) * buffer_size);
                        if(buffer == NULL)
                                exit(1);
                        printf("$ ");
                }
        }
        free(buffer);
        return (0);
}

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
}

char **split_string(char *string, char **divided_string)
{
        /*create divided_string variable*/
        char *splits;
        char *sep;
        int i = 0;

        sep = " ";
        /*use strtok to get first token*/
        splits = strtok(string, sep);
        /*while token isn't equal to NULL*/
        while (splits != NULL)
        {
                /*assign divided string array to token*/
                divided_string[i] = splits;
                /*strtok(NULL)*/
                splits = strtok(NULL, sep);
                i++;
        }
        /*return array*/
        return (divided_string);
}