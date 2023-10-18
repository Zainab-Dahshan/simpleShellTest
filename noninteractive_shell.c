#include "shell.h"

/**
 * ourexec_command - this is main function that executes
 * a command using the shell.
 * @command: Command to execute.
 */
void ourexec_command(char *command)
{
char **argv = malloc(4 * sizeof(char *));
char *envp[] = { NULL };
int status;
pid_t pid;
pid = fork();

if (pid < 0)
{
perror("Forking error");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
argv[0] = "/bin/sh";
argv[1] = "-c";
argv[2] = command;
argv[3] = NULL;

execve("/bin/sh", argv, envp);
perror("Execution error");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}
}
/**
 * run_shell_non_interactive - main function that runs shell
 * program in non-interactive mode.
 * @filename: Name of a file contains commands.
 */
void run_shell_non_interactive(const char *filename)
{
int file = open(filename, O_RDONLY);
char *command = NULL;
size_t command_size = 0;
ssize_t bytesRead;

if (file == -1)
{
perror("File opening error");
return;
}
while ((bytesRead = getline(&command, &command_size, fdopen(file, "r"))) != -1)
{
command[strcspn(command, "\n")] = '\0';
if (strlen(command) > 0)
{
ourexec_command(command);
}
}
if (bytesRead == -1)
{
perror("File reading error");
}
close(file);
free(command);
}
/**
 * main - This is the main entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: An array of strings contains command-line arguments.
 * Description: The first argument is the program name, and the second
 * argument should be name of a file contains commands.
 * Return: 0 on success, otherwise non-zero value on failure.
 */
int main(int argc, char *argv[])
{
if (argc < 2)
{
write(STDERR_FILENO, "Usage: ", 7);
write(STDERR_FILENO, argv[0], strlen(argv[0]));
write(STDERR_FILENO, " <filename>\n", 12);
return (1);
}
run_shell_non_interactive(argv[1]);
return (0);
}
