<<<<<<< HEAD
#ifndef _SIMPLE_SHELL_
#define _SIMPLE_SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute(char *cmd, char *av[]);
void parse(char *buf, char *av[512]);
=======
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

>>>>>>> 129eaa111361f18da3e24b91996b68b64c6d606e
#endif
