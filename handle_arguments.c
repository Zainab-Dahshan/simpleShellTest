#include "shell.h"
/**
 * handle_command - this is main function that executes
 * given command by tokenizing it into separate arguments.
 * @command: An executed command.
 * Return: void
 */
void handle_command(char *command)
{
char *args[100];
int arg_count = 0;
char *token = strtok(command, " ");
int status;
int exit_status = WEXITSTATUS(status);
char exit_status_str[10];
int signal_number = WTERMSIG(status);
char signal_number_str[10];
int z = 0;

while (token != NULL)
	args[arg_count] = strdup(token);
	arg_count++;
	token = strtok(NULL, " ");
args[arg_count] = NULL;
pid_t pid = fork();

if (pid < 0)
	perror("Fork failed");
	exit(1);
else if (pid == 0)
	execve(args[0], args, NULL);
	perror("Execve failed");
	exit(1);
else
	waitpid(pid, &status, 0);
if (WIFEXITED(status))
	sprintf(exit_status_str, "%d", exit_status);
	write(STDOUT_FILENO, "Child process exited with status: ",
		strlen("Child process exited with status: "));
	write(STDOUT_FILENO, exit_status_str, strlen(exit_status_str));
	write(STDOUT_FILENO, "\n", 1);
else if (WIFSIGNALED(status))
	sprintf(signal_number_str, "%d", signal_number);
	write(STDOUT_FILENO, "Child process terminated by signal: ",
		strlen("Child process terminated by signal: "));
	write(STDOUT_FILENO, signal_number_str, strlen(signal_number_str));
	write(STDOUT_FILENO, "\n", 1);
for (z = 0; z < arg_count; z++)
	free(args[z]);
}
/**
 * ourmain - This is main function of our shell program.
 * It prompts user to enter a command, reads it from standard
 * input, removes newline character, and call handle_command
 * function to execute a command.
 * Return: 0 on successful execution.
 */
int ourmain(void)
{
char command[100];

write(STDOUT_FILENO, "Enter a command: ",
	strlen("Enter a command: "));
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';
handle_command(command);
return (0);
}
