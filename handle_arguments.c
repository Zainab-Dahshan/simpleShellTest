#include "shell.h"
/**
 * resolve_command_path - main functions to search full
 * path of command in PATH environment variable.
 * @command: Command to search full path.
 * Return: Full path of a command if found,
 * otherwise NULL if not found.
 */
char *resolve_command_path(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *token = strtok(path_copy, ":");
char *possible_path = NULL;
char *temp_path = NULL;

while (token != NULL)
{
temp_path = malloc(strlen(token) + strlen(command) + 2);
strcpy(temp_path, token);
strcat(temp_path, "/");
strcat(temp_path, command);

if (access(temp_path, X_OK) == 0)
{
free(path_copy);
if (possible_path != NULL)
{
free(possible_path);
}
return (temp_path);
}
if (possible_path != NULL)
{
free(possible_path);
}
possible_path = temp_path;
token = strtok(NULL, ":");
}
free(path_copy);
return (NULL);
}
/**
 * execute_command - main function to execute a command with
 * arguments, input/output redirection, and background flags.
 * @command: Command`s full path.
 * @arguments: Arguments passes to command.
 * @background: A Flag indicates command.
 * @input_file: A file to use as input command.
 * @output_file: A file to use as output command.
 * Return: 0 on success, otherwise -1 on failure.
 */
int execute_command(char *command, char **arguments, int background,
		char *input_file, char *output_file)
{
int input_fd = -1;
int output_fd = -1;
int status;
char *envp[] = { NULL };
pid_t pid = fork();

if (pid < 0)
{
perror("fork");
return (-1);
}
else if (pid == 0)
{
if (input_file != NULL)
{
input_fd = open(input_file, O_RDONLY);
if (input_fd < 0)
{
perror("open");
exit(EXIT_FAILURE);
}
dup2(input_fd, STDIN_FILENO);
close(input_fd);
}
if (output_file != NULL)
{
output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (output_fd < 0)
{
perror("open");
exit(EXIT_FAILURE);
}
dup2(output_fd, STDOUT_FILENO);
close(output_fd);
}
if (execve(command, arguments, envp) < 0)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
if (!background)
{
waitpid(pid, &status, 0);
}
}
return (status);
}
/**
 * Signal_handler - main function to handle SIGINT,
 * SIGTSTP, and SIGTERM signals.
 * @signal: Signal number.
 */
void handle_signal(int signal)
{
const char *textmessage;
switch (signal)
{
case SIGINT:
	textmessage = "Received SIGINT signal (Ctrl+C).\n";
	break;
case SIGTSTP:
	textmessage = "Received SIGTSTP signal (Ctrl+Z).\n";
	break;
case SIGTERM:
	textmessage = "Received SIGTERM signal.\n";
	break;
default:
	textmessage = "Received unknown signal.\n";
	break;
}
write(STDERR_FILENO, textmessage, strlen(textmessage));
}
/**
 * ourmain - The main function of the shell program.
 * Return: Always 0 on success, otherwise non-zero on failure.
 */
int ourmain(void)
{
char command[MAXIMUM_COMMAND_LENGTH];
char *arguments[MAXIMUM_ARGUMENTS];
char *token;
int background = 0;
char *input_file = NULL;
char *output_file = NULL;
int x = 0;
char *full_path = resolve_command_path(arguments[0]);
int y = 0;

signal(SIGINT, handle_signal);
signal(SIGTSTP, handle_signal);
signal(SIGTERM, handle_signal);

while (1)
{
write(STDOUT_FILENO, "shell> ", 7);
fflush(stdout);
if (fgets(command, sizeof(command), stdin) == NULL)
{
break;
}
command[strcspn(command, "\n")] = '\0';

if (command[strlen(command) - 1] == '&')
{
background = 1;
command[strlen(command) - 1] = '\0';
}
else
{
background = 0;
}
token = strtok(command, " ");
x = 0;
while (token != NULL)
{
arguments[x++] = token;
token = strtok(NULL, " ");
}
arguments[x] = NULL;
        
for (y = 0; arguments[y] != NULL; y++)
{
if (strcmp(arguments[y], "<") == 0)
{
input_file = arguments[y + 1];
arguments[y] = NULL;
}
else if (strcmp(arguments[y], ">") == 0)
{
output_file = arguments[y + 1];
arguments[y] = NULL;
}
}
if (strcmp(arguments[0], "cd") == 0)
{
if (arguments[1] != NULL)
{
if (chdir(arguments[1]) < 0)
{
perror("chdir");
}
}
continue;
}
else if (strcmp(arguments[0], "exit") == 0)
{
break;
}

if (full_path != NULL)
{
execute_command(full_path, arguments, background, input_file, output_file);
free(full_path);
}
else
{
write(STDOUT_FILENO, "Command not found\n", 18);
}
input_file = NULL;
output_file = NULL;
}
return (0);
}
