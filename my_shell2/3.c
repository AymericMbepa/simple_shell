#include "hlsh.h"

int lsh_launch(char **args, char **av, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process*/
		processing(args, av, env);
		/*if (execve(args[0], args, NULL) == -1) {
		  perror("lsh");
		  exit(EXIT_FAILURE);
		  }*/

	} else if (pid < 0)
	{
		/*Error forking*/
		perror("lsh");
	} else
	{
    // Parent process
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_execute(char **args, int ac, char **av, char **env)
{

	if (args[0] == NULL)
	{
		return 1;
	}

	return lsh_launch(args, av, env);
}

void hsh_exit(char **args)
{
	if (args[1] == NULL)
	{
		free(args);
		exit(EXIT_SUCCESS);
	}
}

void processing(char **args, char **av, char **env)
{
	char **pathways = NULL;
	char  *full_path = NULL;
	char *token = NULL;
	struct stat st;
	int i = 0;

	if (strcmp(args[0], "env") == 0)
		hsh_env(env);

	if (stat(args[0], &st) == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("lsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pathways = _path(env);
		while (pathways[i])
		{

			token = malloc(sizeof(char*)* strlen(pathways[i]));
			strcpy(token, pathways[i]);
			full_path = strcat(token, "/");
			full_path = strcat(full_path, args[0]);

			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, args, env) ==-1) {
					perror("lsls");
          exit(EXIT_FAILURE);
        }
      }

      i++;
    }
  }
}

void hsh_env(char **env)
{
	size_t i = 0;
	int len = 0;

	while (env[i])
	{
		len = strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

char **_path(char **env)
{
	char *pathvalue = NULL;
	char ** pathways = NULL;
	int i = 0;

	pathvalue = strtok(env[i], "=");
	while (env[i] != NULL)
	{
		if (strcmp(pathvalue, "PATH") == 0)
		{
			pathvalue = strtok(NULL, "");
			pathways = lsh_spilt_line(pathvalue, ":");
			return (pathways);
		}
		i++;
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}
