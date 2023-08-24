#include "shell.h"

/**
 * _puts - writess str to a std output.
 * @str: str written
 *
 * Return: number of printed chars||1 (failure)
 */
ssize_t _puts(char *str)
{
	ssize_t numb, len;

	numb = strlen(str);
	len = write(STDOUT_FILENO, str, numb);
	if (len != numb)
	{
		perror("Fatal errr!");
		return (-1);
	}
	return (len);
}
/**
 * _strdup - returns pointer to new mem alloc
 * space which contains copy
 * @strtodup: str to duplicate
 * 
 * Return: pointer to the dup str
 */
char *_strdup(char *strtodup)
{
	char *copy;
	int len, i;

	if (strtodup == 0)
		return (NULL);
	for (len = 0; strtodup[len]; len++);
	copy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		copy[i] = strtodup[i];

	return (copy);
}
/**
 * _strcmp - compares 2 str
 * @strcmp1: first str to compare
 * @strcmp2: ...
 *
 * Return: 0 (success)
 */
int _strcmp(char *strcmp1, char *strcmp2)
{
	int i = 0;

	while (strcmp1[i] == strcmp2[i])
	{
		if (strcmp1[i] == '\0')
			return (0);
		i++;
	}
	return (strcmp1[i] - strcmp2[i]);
}
/**
 * _strcat - concatanates 2 str
 * @strc1: ...
 * @strc2: ...
 *
 * Return: pointer
 */
char *_strcat(char *strc1, char *strc2)
{
	char *newstr;
	unsigned int len1, len2, newlen, i, j;

	len1 = 0;
	len2 = 0;
	if (strc1 == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; strc1[len1]; len1++);
	}
	if (strc2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; strc2[len2]; len2++);
	}
	newlen = len1 + len2 + 2;
	newstr = malloc(newlen + sizeof(char));
	if (newstr == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		newstr[i] = strc1[i];
	newstr[i] = '/';
	for (j = 0; j < len2; j++)
		newstr[len1 + len2 + 1] = '\0';
	return (newstr);
}
/**
 * _strlen - returns len of a str
 * @str: str measured
 *
 * Return: len of str
 */
unsigned int _strlen(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++);
	return (len);
}
