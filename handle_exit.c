#include "shell.h"
/**
 * exit_shell - this is the main entry point to exit the shell program.
 * Return: Always 0 on success.
 */
void exit_shell(void)
{
exit(0);
}
/**
 * ourexec_command - this is main function that executes command by
 * parsing a command string and using execve.
 * @command: Command string to execute.
 */
void ourexec_command(char *command)
{
char *arguments[MAXIMUM_COMMANDS];
int z = 0;
char *token = strtok(command, " ");

while (token != NULL)
{
arguments[z++] = token;
token = strtok(NULL, " ");
}
arguments[z] = NULL;
if (execve(arguments[0], arguments, NULL) == -1)
{
perror("execve");
exit(1);
}
}
/**
 * execute_background_command - this is the main function that
 * executes a command in background by forking a child process
 * and executing the command in it.
 * @command: Command string to execute.
 */
void execute_background_command(char *command)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(1);
}
else if (pid == 0)
{
ourexec_command(command);
exit(0);
}
else if (pid > 0)
{
waitpid(pid, NULL, WNOHANG);
}
}
/**
 * print_help - this is main function to print help text message with
 * information about the shell and its supported commands.
 */
void print_help(void)
{
write(STDOUT_FILENO, "Shell commands:\n", 16);
write(STDOUT_FILENO, "- exit: Exit our shell program\n", 24);
write(STDOUT_FILENO, "- Pwd: Print The present Working Directory\n", 35);
write(STDOUT_FILENO, "- Help: display a Help message\n", 34);
}
/**
 * ourmain - This main function of the shell program.
 * Return: Always 0 on success.
 */
int ourmain(void)
{
char input[MAXIMUM_COMMAND_LENGTH];
char *directory;
char *command;
char *input_file;

while (1)
{
write(STDOUT_FILENO, "shell> ", 7);
fgets(input, MAXIMUM_COMMAND_LENGTH, stdin);
input[strcspn(input, "\n")] = '\0';
if (strcmp(input, "exit") == 0)
{
exit_shell();
}
if (strcmp(input, "help") == 0)
{
print_help();
continue;
}
if (input[strlen(input) - 1] == '&')
{
execute_background_command(input);
continue;
}
command = strtok(input, "<");
input_file = strtok(NULL, " ");
ourexec_command(command);
}
return (0);
}
