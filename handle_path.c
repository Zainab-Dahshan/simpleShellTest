#include "shell.h"
/**
 * split_command - main function that splits a command
 * string into individual arguments.
 * @command: Command string to split.
 * @arguments: Array to store resulted arguments.
 * Return: Number of arguments in the array.
 */
int split_command(char *command, char *arguments[])
{
int count = 0;
char *token = strtok(command, " ");

while (token != NULL && count < MAXIMUM_ARGUMENTS - 1)
{
arguments[count++] = token;
token = strtok(NULL, " ");
}
arguments[count] = NULL;
return (count);
}
/**
 * search_path - main function that searches for a command.
 * @command: Command to search for.
 * @path: Buffer to store a full path to a command.
 * Return: 1 if the command is found, 0 otherwise.
 */
int search_path(char *command, char *path)
{
char *path_env = getenv("PATH");
char *path_env_copy = strdup(path_env);
char *dir = strtok(path_env_copy, ":");

if (path_env == NULL)
{
perror("getenv");
exit(1);
}
while (dir != NULL)
{
snprintf(path, MAXIMUM_PATH_SIZE, "%s/%s", dir, command);

if (access(path, X_OK) == 0)
{
free(path_env_copy);
return (1);
}
dir = strtok(NULL, ":");
}
free(path_env_copy);
return (0);
}
/**
 * exec_command - main function that executes a command
 * with a given arguments as a child process.
 * @command: Command to be executed.
 * @arguments: Array of arguments for the command.
 */
void exec_command(char *command, char *arguments[])
{
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
exit(1);
}
else if (pid == 0)
{
execve(command, arguments, NULL);
perror("execve");
exit(1);
}
else
{
waitpid(pid, NULL, 0);
}
}
/**
 * main - main entry point of my program.
 * @argc: Numb. of arguments passes to program.
 * @argv: Array of strings contain arguments passed to program.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
char path[MAXIMUM_PATH_SIZE];
char *command = NULL;
char *arguments[MAXIMUM_ARGUMENTS];

while (1)
{
size_t command_size = 0;
ssize_t read_size = getline(&command, &command_size, stdin);
int count = split_command(command, arguments);

write(1, "shell> ", 7);

if (read_size == -1)
{
perror("getline");
exit(1);
}
command[read_size - 1] = '\0';
if (count == 0)
{
continue;
}
if (search_path(arguments[0], path))
{
exec_command(path, arguments);
}
else
{
write(1, "Command not found: ", 19);
write(1, arguments[0], strlen(arguments[0]));
write(1, "\n", 1);
}
}
free(command);
return (0);
}
