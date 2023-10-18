#include "shell.h"
/**
 * ourexec_command - the main function that executes a single command.
 * @command: Command to execute.
 */
void ourexec_command(char *command)
{
char *arguments[MAXIMUM_ARGUMENTS + 1];
int number_arguments = 0;
char *token;

token = strtok(command, " ");

while (token != NULL && number_arguments < MAXIMUM_ARGUMENTS)
{
arguments[number_arguments++] = token;

token = strtok(NULL, " ");
}
arguments[number_arguments] = NULL;
execve(arguments[0], arguments, NULL);
perror("execve");
exit(1);
}

/**
 * handle_piping - this is main function that
 * handles piping of multiple commands.
 * @commands: An array of commands to execute.
 * @number_commands: Number of commands in an array.
 */
void handle_piping(char **commands, int number_commands)
{
int z;
int pipefd[2];
pid_t pid;

for (z = 0; z < number_commands - 1; z++)
{
if (pipe(pipefd) == -1)
{
perror("pipe");
exit(1);
}
pid = fork();

if (pid == 0)
{
dup2(pipefd[1], STDOUT_FILENO);
close(pipefd[0]);
close(pipefd[1]);

ourexec_command(commands[z]);

exit(0);
}
else if (pid > 0)
{
dup2(pipefd[0], STDIN_FILENO);
close(pipefd[0]);
close(pipefd[1]);
}
else
{
perror("fork");
exit(1);
}
}
ourexec_command(commands[z]);
}
/**
 * ourmain - this is a main entry point to the program.
 * Return: Always 0 on success.
 */
int ourmain(void)
{
char input[MAXIMUM_COMMAND_LENGTH];
char *commands[MAXIMUM_ARGUMENTS];
int number_commands;
char *token;

while (1)
{
write(STDOUT_FILENO, "Shell> ", 8);
fgets(input, sizeof(input), stdin);

input[strcspn(input, "\n")] = '\0';

if (strcmp(input, "exit") == 0)
{
exit(0);
}
else if (strstr(input, "|") != NULL)
{
number_commands = 0;
token = strtok(input, "|");

while (token != NULL && number_commands < MAXIMUM_ARGUMENTS)
{
token++;
if (token[strlen(token) - 1] == ' ')
token[strlen(token) - 1] = '\0';

commands[number_commands++] = token;
token = strtok(NULL, "|");
}
handle_piping(commands, number_commands);
}
}
return (0);
}
