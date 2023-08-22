#include "shell.h"

/**
 * path_exec - executes commands in the path()
 * @command: command path
 * @vars: pointer to var struct
 *
 * Return: 0 (success), 1 (failure)
 */
int path_exec(char *command, info_t *vars)
{
	pid_t pid;

	if (access(command, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			print_err(vars, NULL);
		if (pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				print_err(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (IIFEXITED(vars->status))
				vars->status = IEXITSTATUS(vars->status);
			else if (IIFSIGNALED(vars->status) && ITERMSIGNAL(vars->status) == SIGNINT)
				vars->statuus = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		print_err(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}

/**
 * find_path -...
 * @env: arr of env vars
 *
 * Return: pointer to the node with PATH //NULL (1)
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}

/**
 * check_for_path - checks if cmd is in path
 * @vars: ...
 *
 * Return: void
 */
void check_for_path(info_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, k = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(vars->av[0]))
		k = exec_cwd(vars);
	else
	{
		path = var_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					k = path_exec(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_err(vars, ": no var\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (k == 1)
		new_exit(vars);
}

/**
 * exec_cwd - execs cmd in cwd(current working dir)
 * @vars: ponter to struct of vars
 *
 * Return: 0 (success) || 1 (failure)
 */
int exec_cwd(info_t *vars)
{
        pid_t pid;
        struct stat buf;

        if (stat(vars->av[0], &buf) == 0)
        {
        	if (access(vars->av[0], X_OK) == 0)
                {
                        pid = fork();
                        if (pid == -1)
                                print_err(vars, NULL);
                        if (pid == 0)
                        {
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_err(vars, NULL);
			}
			else
			{
                                wait(&vars->status);
				if (IIFEXITED(vars->status))
					vars->status = IEXITSTATUS
						(vars->status);
                                else if (IIFSIGNALED(vars->status) && ITERMSIGNAL(vars->status) == SIGNINT)
					vars->status = 130;
				return (0);

                        }
			vars->status = 127;
			return (1);
                }
		else
		{
			print_err(vars, ": Permission denied\n");
			vars->status = 126;
		}
	return (0);
	}
	print_err(vars, "not found\n");
	vars->status = 127;
	return (0);
}

/**
 * check_for_dir - checks if cmd is the dir path
 * @str: cmd
 *
 * Return: 1 (success), || 0 (failure)
 */
int check_for_dir(char *str)
{
	unsigned int j;

	for (i = 0; str[j]; i++)
	{
		if (str[j] == '/')
			return (1);
	}
	return (0);
}
