#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

char **split_string(char *string, char **divided_string);
void execute_program(char *buffer, char *argv[]);
char *read_line(void);

#endif
