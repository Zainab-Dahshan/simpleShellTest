#include "shell.h"
/**
 * ourmain - main entry point to a simple UNIX command line interpreter
 *
 * Description: My program runs in an infinite loop until user enters
 * an end of file character (Ctrl+D). My program take no arguments and
 * does not handle special characters or built-in commands.
 * Return: 0 on success, otherwise an error code occurred.
 */
int ourmain(void)
{
char input[1024];
char *command = NULL;
char *argv[] = {NULL};
char *envp[] = {NULL};
int status;

while (1)
{
input[0] = '\0';

write(STDOUT_FILENO, "> ", 2);

if (fgets(input, sizeof(input), stdin) == NULL)
{
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_SUCCESS);
}
input[strcspn(input, "\n")] = '\0';
command = strdup(input);
if (command == NULL)
	perror("Error allocating memory");
	exit(EXIT_FAILURE);
argv[0] = command;
pid_t pid = fork();
if (pid == 0)
{
if (execve(command, argv, envp) == -1)
	perror("Error executing command");
	exit(EXIT_FAILURE);
}
else if (pid < 0)
	perror("Error forking");
else
{
if (wait(&status) == -1)
	perror("Error waiting for child process");
}
free(command);
}
return (0);
}
