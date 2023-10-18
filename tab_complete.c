#include "shell.h"
/**
 * tab_complete - main function that performs
 * tab completion for a given input.
 * @input: An input string to perform tab completion on.
 */
void tab_complete(char *input)
{
char *lastSpace = strrchr(input, ' ');
char *prefix = lastSpace ? lastSpace + 1 : input;
char *completions[MAXIMUM_COMMANDS] = {0};
int number_completions = 0, z = 0;
DIR *dir;
struct dirent *entry;

dir = opendir(".");
if (dir != NULL)
{
while ((entry = readdir(dir))
	!= NULL && number_completions < MAXIMUM_COMMANDS)
{
if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0)
{
completions[number_completions++] = strdup(entry->d_name);
}
}
closedir(dir);
}
else
	perror("Error opening directory");
	return;
if (number_completions == 1)
{
strncpy(lastSpace ? lastSpace + 1 : input, completions[0],
	MAXIMUM_COMMAND_LENGTH - (prefix - input) - 1);
write(STDOUT_FILENO, input + strlen(input), strlen(input) - (prefix - input));
}
else if (number_completions > 1)
	write(STDOUT_FILENO, "\n", 1);
for (z = 0; z < number_completions; z++)
{
write(STDOUT_FILENO, completions[z], strlen(completions[z]));
write(STDOUT_FILENO, " ", 1);
}
write(STDOUT_FILENO, "\nEnter a command: ", 18);
write(STDOUT_FILENO, input, strlen(input));
for (z = 0; z < number_completions; z++)
	free(completions[z]);
}
/**
 * main - This is  main function that reads user
 * input and performs tab completion.
 * Return: 0 on success.
 */
int ourmain(void)
{
char input[MAXIMUM_COMMAND_LENGTH];
ssize_t bytesRead = read(STDIN_FILENO, input, sizeof(input) - 1);

while (1)
{
write(STDOUT_FILENO, "Enter a command: ", 17);

if (bytesRead == -1)
{
perror("Error reading input");
return (1);
}
input[bytesRead - 1] = '\0';
tab_complete(input);
}
return (0);
}
