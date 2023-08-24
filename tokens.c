#include "shell.h"
/**
 * tokenz - tokenizes a buffer with a delimiter
 * @buffer: buffer to tokenize
 * @delimit: delimiter to tokenize along
 *
 * Return: pointer to an arr of pointers to the tokens
 */
char **tokenz(char *buffer, char *delimit)
{
        char **tokens = NULL;
        size_t i = 0, tcount = 10;

        if (buffer == NULL)
                return (NULL);
        tokens = malloc(sizeof(char *) * tcount);
        if (tokens == NULL)
        {
                perror("Fatal Error!");
                return (NULL);
        }
        while ((tokens[i] = new_strtok(buffer, delimit)) != NULL)
        {
                i++;
                if (i == tcount)
                {
                        tokens = _realloc(tokens, &tcount);
                        if (tokens == NULL)
                        {
                                perror("Fatal Error!");
                                return (NULL);
                        }
                }
                buffer = NULL;
        }
        return (tokens);
}

