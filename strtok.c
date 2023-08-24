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
	unsigned int j;

	if (str != NULL)
		nxt_tok = str;
	tok_start = nxt_tok;
	if (tok_start == NULL)
		return (NULL);
	for (j = 0; nxt_tok[j] != '\0'; j++)
	{
		if (check_match(nxt_tok[j], delim) == 0)
			break;
	}
	if (nxt_tok[j] == '\0' || nxt_tok[j] == '#')
	{
		nxt_tok = NULL;
		return (NULL);
	}
	tok_start = nxt_tok + j;
	nxt_tok = tok_start;
	for (j = 0; nxt_tok[j] != '\0'; j++)
	{
		if (check_match(nxt_tok[j], delim) == 1)
			break;
	}
	if (nxt_tok[j] == '\0')
		nxt_tok = NULL;
	else
	{
		nxt_tok[j] = '\0';
		nxt_tok = nxt_tok + j + 1;
		if (*nxt_tok == '\0')
			nxt_tok = NULL;
	}
	return (tok_start);
}
