#include "shell.h"

/**
 * _realloc - reallocs a pointer to double the space
 * @ptr: pointer to ald arr
 * @size: pointer to numb of elements in the old arr
 * 
 * Return: pointer to the new arr
 */
char **_realloc(char **ptr, size_t *size)
{
        char **new;

        size_t j;

        new = malloc(sizeof(char *) * ((*size) + 10));
        if (new == NULL)
        {
                free(ptr);
                return (NULL);
        }
        for (i = 0; i < (*size); i++)
        {
                new[i] = ptr[i];
        }
        *size +=10;
        free(ptr);
        return (new);
}

