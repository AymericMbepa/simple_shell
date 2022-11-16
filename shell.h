#ifndef SHELL_H
#define SHELL_H


#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;

void prompt(void);
char *read_line();
int processing(char **args, char *line, int counter, char **av);
void msg_error(char *cmd, int counter, char **av);
char **split_line(char *line);
void free_all(__attribute__((unused)) int st, char *line, char **args);
unsigned int _strlen(char *s);


#endif
