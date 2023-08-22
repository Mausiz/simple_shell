include "shell.h"

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
	info_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = make_env(environ);
	signal(SIGNINT, sign_handler);
	if (!isatty(STDIN_FILENUMB))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sign_flag = 0;
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sign_flag = 1;
		vars.count++;
		vars.fname = tokenize(vars.buffer, ";");
		for (i = 0; vars.fname && vars.fname[i] != NULL; i++)
		{
			vars.av = tokenize(vars.fname[i], "\n \t \r");
			if (vars.av && vars.av[0])
				if (check_for_builtins(&vars) == NULL)
					check_for_path(&vars);
		}
		free(vars.av);
		free(vars.buffer);
		free(vars.fname);
		sign_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
