#include "shell.h"

/**
 * add_key - create new environ var
 * @info: pointer of struct of vars
 *
 * Return: nada
 */
void add_key(info_t *info)
{
        unsigned int i;
        char **newenviron;

        for (i = 0; info->environ[i] != NULL; i++);
        newenviron = malloc(sizeof(char *) * (i + 2));
        if (newenviron == NULL)
        {
                print_err(info, NULL);
                info->status = 127;
                new_exit(info);
        }
        for (i = 0; info->environ[i] != NULL; i++)
                newenviron[i] = info->environ[i];
        newenviron[i] = add_value(info->av[1], info->av[2]);
        if (newenviron[i] == NULL)
        {
                print_err(info, NULL);
                free(info->buffer);
                free(info->commands);
                free(info->av);
                free_environ(info->environ);
                free(newenviron);
                exit(127);
        }
        newenviron[i + 1] = NULL;
        free(info->environ);
}
/**
 * find_key - finds an environ var
 * @environ: arr of environ vars
 * @key: environ var to find
 *
 * Return: pointer to address of the environ var
 */
char **find_key(char **environ, char *key)
{
        unsigned int i, j, len;

        len= strlen(key);

        for (i = 0; environ[i] != NULL; i++)
        {
                for (j = 0; j < len; j++)
                        if (key[j] != environ[i][j])
                                break;
                if (j == len && environ[i][j] == '=')
                        return (&environ[i]);
        }
        return (NULL);
}
/**
 * add_val - create new environ var
 * @key: var name
 * @val: var value
 * Return: pointer to the new str
 */
char *add_val(char *key, char *val)
{
        unsigned int len1, len2, i, j;
        char *new;

        len1 = _strlen(key);
        len2 = _strlen(val);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
        if (new == NULL)
                return (NULL);
        for (i = 0; key[i] != '\0'; i++)
                new[i] = key[i];
        new[i] = '=';
        for (j = 0; val[j] != '\0'; j++)
                new[i + 1 + j] = val[j];
        new[i + 1 + j] = '\0';
        return (new);
}

/**
 * _atoi - converts str to int
 * @str: str to convert
 *
 * Return: the int val, or error (-1)
 */
int _atoi(char *str)
{
        unsigned int i, digits;
        int num = 0, num_test;

        num_test = INT_MAX;
        for (digits = 0; num_test != 0; digits++)
                num_test /= 10;
        for (i = 0; str[i] != '\0' && i < digits; i++)
        {
                num *= 10;
                if (str[i] < '0' || str[i] > '9')
                        return (-1);
                if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
                        return (-1);
                if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
                        return (-1);
                num += str[i] - '0';
                if ((i == digits - 2) && (str[i + 1] != '\0')
                                && (num > INT_MAX / 10))
                        return (-1);
        }
        if (i > digits)
                return (-1);
        return (num);
}
