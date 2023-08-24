#include "shell.h"
/**
 * print_err - prints error msg to std error
 * @info: pointer to struct of vars
 * @msg: msg to print
 *
 * Return: void
 */
void print_err(info_t *info, char *msg)
{
        char *count;

        _puts2(info->argv[0]);
        _puts2(": ");
        count = _uitoa(info->count);
        _puts2(count);
        free(count);
        _puts2(": ");
        _puts2(info->av[0]);
        if (msg)
        {
                _puts2(msg);
        }
        else
                perror("");
}
/**
 * _puts2 - prints a str to std error
 * @str: str to print
 *
 * Return: nada
 */
void _puts2(char *str)
{
        ssize_t numb, len;

        numb = strlen(str);
	len = write(STDERR_FILENO, str, numb);
	if (len != numb)
	{
		perror("Fatal Error");
		exit(1);
	}
}
/**
 * _uitoa - converts unsigned int to str
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted str
 */
char *_uitoa(unsigned int count)
{
	char *numbstr;
	unsigned int tmp, xters;

	tmp = count;
	for (xters = 0; tmp != 0; xters++)
		tmp /= 10;
	numbstr = malloc(sizeof(char) * (xters + 1));
	if (numbstr == NULL)
	{
		perror("Fatal Error!(1)");
		exit(127);
	}
	numbstr[xters] = '\0';
	for (--xters; count; --xters)
	{
		numbstr[xters] = (count % 10) + '0';
		count /= 10;
	}
	return (numbstr);
}



















