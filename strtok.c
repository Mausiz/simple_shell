#include "shell.h"
/**
 * check_match - checks if k matches any in str
 * @k: character to check
 * @str: str to check
 *
 * Return: 1 (match), 0 (nada)
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}
/**
 * new_strtok - custom strtok
 * @str: str to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to nxt token|| NULL
 */
char *new_strtok(char *str, const char *delim)
{
	static char *tok_start;
	static char *nxt_tok;
	unsigned int c;

	if (str != NULL)
		nxt_tok = str;
	tok_start = nxt_tok;
	if (tok_start == NULL)
		return (NULL);
	for (i = 0; nxt_tok[i] != '\0'; i++)
	{
		if (check_match(nxt_tok[i], delim) == 0)
			break;
	}
	if (nxt_tok[i] == '\0' || nxt_tok[i] == '#')
	{
		nxt_tok = NULL;
		return (NULL);
	}
	tok_start = nxt_tok + i;
	nxt_tok = tok_start;
	for (i = 0; nxt_tok[i] != '\0'; i++)
	{
		if (check_match(nxt_tok[i], delim) == 1)
			break;
	}
	if (nxt_tok[i] == '\0')
		nxt_tok = NULL;
	else
	{
		mxt_tok[i] = '\0';
		nxt_tok = nxt_tok + i + 1;
		if (*nxt_tok == '\0')
			nxt_tok = NULL;
	}
	return (tok_start);
}
