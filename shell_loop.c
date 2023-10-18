#include "shell.h"
/**
 * split_Line - this is main function that splits a string
 * into separated tokens using space as the delimiter.
 * @line: Splitted string.
 * @arguments: An array of strings to store the tokens.
 */
void split_Line(char *line, char **arguments)
{
char *token;
int z = 0;

token = strtok(line, " ");

while (token != NULL && z < MAXIMUM_ARGUMENTS - 1)
{
arguments[z] = strdup(token);
z++;
token = strtok(NULL, " ");
}
arguments[z] = NULL;
}

/**
 * read_line - this is main function that reads
 * a line of input from the user
 * @path: the PATH environment variable
 * Return: a string containing the user's input,
 * or NULL on failure
 */
char *read_line(char *path)
{
char buffer[MAXIMUM_COMMANDS];
int pos = 0;
int len = 0;
char c = getchar();
char *line = strdup(buffer);

while (1)
{
if (c == EOF || c == '\n')
{
buffer[pos] = '\0';
len = pos;
break;
}
if (pos >= MAXIMUM_COMMANDS)
{
pos = MAXIMUM_COMMANDS - 1;
}
}
if (len == 0)
	return (NULL);

if (line == NULL)
	return (NULL);

return (line);
}
/**
 * shell_Loop - This is main loop of shell program that reads input
 * from stdin, splits it into tokens, and executes command(s).
 */
void shell_Loop(void)
{
char line[MAXIMUM_COMMANDS];
char *arguments[MAXIMUM_ARGUMENTS];
char *input = read_line(NULL);
int status;
int z = 0;

do {
write(STDOUT_FILENO, "> ", 2);
if (input == NULL)
{
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_SUCCESS);
}
strncpy(line, input, MAXIMUM_COMMANDS);
free(input);

for (z = 0; arguments[z] != NULL; z++)
{
free(arguments[z]);
arguments[z] = NULL;
}
} while (status);
}
/**
 * exec_command - this main function that executes
 * command with the given arguments
 * @arguments: Array of arguments
 * Return: void
 */
int execu_command(char **arguments)
{
int status;
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(arguments[0], arguments, NULL);
perror("execve");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
return (status);
}
}
/**
 * ourmain - main entry point of the program.
 * Return: 0 on success.
 */
int ourmain(void)
{
shell_Loop();
return (0);
}
