#include "shell.h"
/**
 * free_memory - main function that frees memory
 * allocated for an array of strings.
 * @arguments: An array of strings to free
 */
void free_memory(char **arguments)
{
int z = 0;

while (arguments[z] != NULL)
{
free(arguments[z]);
z++;
}
free(arguments);
}
