#include "shell.h"
/**
 * handle_input_redirection - this is main functin that handles input
 * redirection by opening a specified input file and redirecte
 * it to standard input.
 * @command: Command to be executed.
 * @input_file: Name of an input file for redirection.
 */
void handle_input_redirection(char *command, char *input_file)
{
int stdout_fd = dup(STDOUT_FILENO);
FILE *file = fopen(input_file, "r");

if (file == NULL)
{
perror("fopen");
exit(1);
}
if (dup2(fileno(file), STDIN_FILENO) == -1)
{
perror("dup2");
exit(1);
}
write(STDOUT_FILENO, "Executing command: ", 20);
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, "\n", 1);

if (dup2(stdout_fd, STDIN_FILENO) == -1)
{
perror("dup2");
exit(1);
}
fclose(file);
}

/**
 * handle_output_redirection - this is main function that handles
 * output redirection by opening a specified output file
 * and redirecting standard output to it.
 * @command: Command to be executed.
 * @output_file: Name of an output file for redirection.
 */
void handle_output_redirection(char *command, char *output_file)
{
int stdout_fd = dup(STDOUT_FILENO);
FILE *file = fopen(output_file, "w");

if (file == NULL)
{
perror("fopen");
exit(1);
}
if (dup2(fileno(file), STDOUT_FILENO) == -1)
{
perror("dup2");
exit(1);
}
write(STDOUT_FILENO, "Executing command: ", 20);
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, "\n", 1);

if (dup2(stdout_fd, STDOUT_FILENO) == -1)
{
perror("dup2");
exit(1);
}
fclose(file);
}
/**
 * ourmain - This is main function of the shell program.
 * Return: Always 0 on success.
 */
int ourmain(void)
{
char input[MAXIMUM_COMMAND_LENGTH];
char *command;
char *input_file;
char *output_file;

while (1)
{
write(STDOUT_FILENO, "Shell> ", 7);
fgets(input, sizeof(input), stdin);
input[strcspn(input, "\n")] = '\0';

if (strcmp(input, "exit") == 0)
	break;
else if (strncmp(input, "cd", 2) == 0)
	write(STDOUT_FILENO, "Changing directory\n", 19);
else if (strcmp(input, "pwd") == 0)
	write(STDOUT_FILENO, "Printing current directory\n", 27);
else if (strcmp(input, "help") == 0)
	write(STDOUT_FILENO, "Displaying help information\n", 28);
else if (strstr(input, "<") != NULL)
{
command = strtok(input, "<");
input_file = strtok(NULL, "<");
handle_input_redirection(command, input_file);
}
else if (strstr(input, ">") != NULL)
{
command = strtok(input, ">");
output_file = strtok(NULL, ">");
handle_output_redirection(command, output_file);
}
else
system(input);
}
return (0);
}
