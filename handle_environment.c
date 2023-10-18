#include "shell.h"

/**
 * handle_environment - this is main function that handles 'env' command
 * to print all environment variables.
 */
void handle_environment(void)
{
char **current = environ;

while (*current != NULL)
{
write(STDOUT_FILENO, *current, strlen(*current));
write(STDOUT_FILENO, "\n", 1);
current++;
}
}
/**
 * main - this is main entry point of my own shell program.
 * @argc: number of command-line arguments.
 * @argv: Array of strings contains list of arguments.
 * Return: Always 0 on success.
 */
int main(int argc, char *argv[])
{
char input[100];
char *prompt = "Shell $ ";
size_t prompt_len = strlen(prompt);
size_t input_len;
char *command;
char *unknown_command = "Unknown command: ";
char *newline = "\n";
size_t unknown_command_len = strlen(unknown_command);
size_t command_len;
size_t newline_len = strlen(newline);

while (1)
{
write(STDOUT_FILENO, prompt, prompt_len);

if (fgets(input, sizeof(input), stdin) == NULL)
	write(STDOUT_FILENO, "\n", 1);
	break;
input_len = strlen(input);
if (input[input_len - 1] == '\n')
	input[input_len - 1] = '\0';
	input_len--;
command = strtok(input, " ");
if (command == NULL)
	continue;
command_len = strlen(command);
if (strcmp(command, "env") == 0)
	handle_environment();
else if (strcmp(command, "exit") == 0)
	break;
else
	write(STDERR_FILENO, unknown_command, unknown_command_len);
	write(STDERR_FILENO, command, command_len);
	write(STDERR_FILENO, newline, newline_len);
}
return (EXIT_SUCCESS);
}
