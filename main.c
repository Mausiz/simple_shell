#include "shell.h"

/**
 * sign_handler - handles c signal interrupt
 * @unvar: unsused var for signal func proto..
 *
 * Return: void
 */
unsigned int sign_flag;

static void sign_handler(int unvar)
{
	(void) unvar;
	if (sign_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - ...
 * @argc: no of args passed to main
 * @argv: arr of args pased to main
 * @environ: arr of environ vars
 *
 * Return: 0, exit status, ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environ)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	info_t info = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	info.argv = argv;
	info.environ = make_environ(environ);
	signal(SIGNINT, sign_handler);
	if (!isatty(STDIN_FILENUMB))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sign_flag = 0;
	while (getline(&(info.buffer), &len_buffer, stdin) != -1)
	{
		sign_flag = 1;
		info.count++;
		info.commands = tokenz(info.buffer, ";");
		for (i = 0; info.commands && info.commands[i] != NULL; i++)
		{
			vars.av = tokenz(info.commands[i], "\n \t \r");
			if (info.av && info.av[0])
				if (check_for_builtins(&info) == NULL)
					check_for_path(&info);
		}
		free(info.av);
		free(info.buffer);
		free(info.commands);
		sign_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		info.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_environ(info.environ);
	free(info.buffer);
	exit(info.status);
}
