#include “shell.h”
/**
 * make_environ - make shell environ from environ passed to main
 * @environ: environ passed to main
 *
 * Return: pointer to the new environ
 */
char **make_environ(char **environ)
{
        char **newenviron = NULL;
        size_t i;

        for (i = 0; environ[i] != NULL; i++);
        newenviron = malloc(sizeof(char *) * (i + 1));
        if (newenviron == NULL)
        {
                perror("Fatal Error");
                exit(1);
        }
        for (i = 0; environ[i] != NULL; i++)
                newenviron[i] = _strdup(environ[i]);
        newenviron[i] = NULL;
        return (newenviron);
}
/**
 * free_environ - free shell environ
 * @environ: shell's environ
 *
 * Return: nada
 */
void free_environ(char **environ)
{
        unsigned int i;

        for (i = 0; environ[i] != NULL; i++)
                free(environ[i]);
        free(environ);
}

