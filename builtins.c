#include "shell.h"
#include "shell.h"

void (*check_for_builtins(info_t *info))(info_t *info)
{
    unsigned int k;
    builtins_t check[] =
    {
        {"exit", new_exit},
        {"environ", _environ},
        {"setenviron", new_setenviron},
        {"unsetenviron", new_unsetenviron},
        {NULL, NULL}
    };

    for (k = 0; check[k].f != NULL; k++)
    {
        if (_strcmp(info->av[0], check[k].type) == 0)
            break;
    }
    if (check[k].f != NULL)
        check[k].f(info);
    return check[k].f;
}

/**
 * new_exit - exit prog
 * @info: vars(exstatus = exit status)
 * 
 * Return: void
 */
void new_exit(info_t *info)
{
        int exstatus;
 
        if (_strcmp(info->av[0], "exit") == 0 &&
		       	info->av[1] != NULL)
	{
		exstatus = _atoi(info->av[1]);
		if (exstatus == -1)
		{
			info->status = 2;
			print_err(info, ": illegal number: ");
			_puts2(info->av[1]);
			_puts2("\n");
			free(info->commands);
			info->commands = NULL;
			return;
		}
		info->status = exstatus;
	}
	free(info->buffer);
	free(info->av);
	free(info->commands);
	free_environ(info->environ);
	exit(info->status);
}

/**
 * _environ - prints current environ
 * @info: struct of vars
 * 
 * Return: void
 */
void _environ(info_t *info)
{
	unsigned int i;

	for (i = 0; info->environ[i]; i++)
	{
		_puts(info->environ[i]);
		_puts("\n");
	}
	info->status = 0;
}

/**
 * new_setenviron - create new environ var or edit existing var
 * @info: pointer to struct of vars
 *
 * Return: void
 */
void new_setenviron(info_t *info)
{
	char **key;
	char *var;

	if (info->av[1] == NULL || info->av[2] == NULL)
	{
		print_err(info, ": Number of arguments do not match\n");
		info->status = 2;
		return;
	}
	key = find_key(info->environ, info->av[1]);
	if (key == NULL)
		add_key(info);
	else
	{
		var = add_value(info->av[1], info->av[2]);
		if (var == NULL)
		{
			print_err(info, NULL);
			free(info->buffer);
			free(info->commands);
			free(info->av);
			free_environ(info->environ);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	info->status = 0;
}
/**
 * new_unsetenviron - rm environ var
 * @info: pointer to a struct of var
 *
 * Return: void
 */
void new_unsetenviron(info_t *info)
{
        char **key, **newenviron;
        unsigned int i, j;

        if (info->av[1] == NULL)
        {
                print_err(info, ": Number of arguments do not match\n");
                info->status = 2;
                return;
        }
        key = find_key(info->environ, info->av[1]);
        if (key == NULL)
        {
                print_err(info, ": Variable not found");
                return;
        }
        for (i = 0; info->environ[i] != NULL; i++);
        newenviron = malloc(sizeof(char *) * i);
        if (newenviron == NULL)
        {
                print_err(info, NULL);
                info->status = 127;
                new_exit(info);
        }
        for (i = 0; info->environ[i] != *key; i++)
                newenviron[i] = info->environ[i];
        for (j = i + 1; info->environ[j] != NULL; j++, i++)
                newenviron[i] = info->environ[j];
        newenviron[i] = NULL;
        free(*key);
        free(info->environ);
        info->environ = newenviron;
	info->status = 0;
}
/**
 * info = vars
 * exstatus = status
 * environ = env
 */
