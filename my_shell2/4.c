#include "hlsh.h"

void lsh_loop(int ac, char **av, char **env) {
  char *line;
  char **args;
  int status;
  const char *delim = LSH_TOK_DELIM;

  do {
    prompt();
    line = lsh_read_line();
    args = lsh_spilt_line(line, delim);

    if (strcmp(args[0], "exit") == 0)
      hsh_exit(args);
    else
      status = lsh_execute(args, ac, av, env);

    free(line);
    free(args);
  } while(status);
}


void prompt(void) {
  char *str = {"#cisfun$ "};
  int len = strlen(str);

  if (isatty(STDIN_FILENO)) {
    write(STDOUT_FILENO, str, len);
  }
}
