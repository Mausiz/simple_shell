#include "shell.h"

/**
 * path_exec - executes commands in the path()
 * @command: command path
 * @info: pointer to var struct
 *
 * Return: 0 (success), 1 (failure)
 */
int path_exec(char *command, info_t *info)
{
	pid_t pid;

	if (access(command, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			print_err(info, NULL);
		if (pid == 0)
		{
			if (execve(command, info->av, info->environ) == -1)
				print_err(info, NULL);
		}
		else
		{
			wait(&info->status);
			if (WIFEXITED(info->status))
				info->status = WEXITSTATUS(info->status);
			else if (WIFSIGNALED(info->status) && WTERMSIG(info->status) == SIGINT)
				info->status = 130;
			return (0);
		}
		info->status = 127;
		return (1);
	}
	else
	{
		print_err(info, ": Permission denied\n");
		info->status = 126;
	}
	return (0);
}

/**
 * find_path -...
 * @env: arr of env vars
 *
 * Return: pointer to the node with PATH //NULL (1)
 */
char *find_path(char **environ)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != environ[i][j])
				break;
		if (j == 5)
			break;
	}
	return (environ[i]);
}

/**
 * check_for_path - checks if cmd is in path
 * @info: ...
 *
 * Return: void
 */
void check_for_path(info_t *info)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, k = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(info->av[0]))
		k = exec_cwd(info);
	else
	{
		path = find_path(info->environ);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], info->av[0]);
				if (stat(check, &buf) == 0)
				{
					k = path_exec(check, info);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				info->status = 127;
				new_exit(info);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_err(info, ": no var\n");
			info->status = 127;
		}
		free(path_tokens);
	}
	if (k == 1)
		new_exit(info);
}

/**
 * exec_cwd - execs cmd in cwd(current working dir)
 * @vars: ponter to struct of vars
 *
 * Return: 0 (success) || 1 (failure)
 */
int exec_cwd(info_t *info)
{
        pid_t pid;
        struct stat buf;

        if (stat(info->av[0], &buf) == 0)
        {
        	if (access(info->av[0], X_OK) == 0)
                {
                        pid = fork();
                        if (pid == -1)
                                print_err(info, NULL);
                        if (pid == 0)
                        {
				if (execve(info->av[0], info->av, info->environ) == -1)
					print_err(info, NULL);
			}
			else
			{
                                wait(&info->status);
				if (WIFEXITED(info->status))
					info->status = WEXITSTATUS
						(info->status);
                                else if (WIFSIGNALED(vars->status) && WTERMSIGNAL(info->status) == SIGINT)
					info->status = 130;
				return (0);

                        }
			info->status = 127;
			return (1);
                }
		else
		{
			print_err(info, ": Permission denied\n");
			info->status = 126;
		}
	return (0);
	}
	print_err(info, "not found\n");
	info->status = 127;
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

	for (j = 0; str[j]; j++)
	{
		if (str[j] == '/')
			return (1);
	}
	return (0);
}
