#ifndef HLSH_H
#define HLSH_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define LSH_BUFSIZE 1024
#define LSH_TOK_DELIM " \t\r\n\a"

void lsh_loop(int ac, char **av, char **env);
char *lsh_read_line();
char **lsh_spilt_line(char *line, const char *DELIM);
int lsh_launch(char **args, char **av, char **env);
int lsh_execute(char **args, int ac, char **av, char **env);
void prompt(void);
void hsh_exit(char **args);
void hsh_env(char **env);
void processing(char **args, char **av, char **env);
char **_path(char **env);


#endif
