#include "shell.h"
/**
 * parse - main function that parses user input into
 * command and parameters.
 * @command: User input command.
 * @parameters: Array to store parsed parameters.
 */
void parse(char *command, char **parameters)
{
char *token = strtok(command, " ");
int z = 0;

while (token != NULL)
{
parameters[z] = token;
z++;
token = strtok(NULL, " ");
}
parameters[z] = NULL;
}
/**
 * print_prompt - main function that prints shell prompt.
 */
void print_prompt(void)
{
write(STDOUT_FILENO, "$ ", 2);
}
/**
 * main - this is main entry point to our shell program.
 * @argc: number of command-line arguments.
 * @argv: Array of strings contains list of arguments.
 * Return: 0 on successful execution.
 */
int main(int argc, char *argv[])
{
int interactive = isatty(STDIN_FILENO);
char command[MAXIMUM_COMMANDS];
char *parameters[MAXIMUM_COMMANDS];

do {
if (interactive)
{
print_prompt();
}
if (fgets(command, sizeof(command), stdin) == NULL)
{
if (interactive)
{
write(1, "\n", 1);
}
exit(EXIT_SUCCESS);
}
command[strcspn(command, "\n")] = 0;
parse(command, parameters);
pid_t pid = fork();

if (pid < 0)
{
write(1, "Error occurred.\n", 15);
exit(EXIT_FAILURE);
}
if (pid == 0)
{
if (execvp(parameters[0], parameters) == -1)
{
write(1, "Command not found.\n", 18);
exit(EXIT_FAILURE);
}
}
else
	wait(NULL);
} while (interactive);
return (0);
}
