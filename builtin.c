#include "shell.h"

/**
 * handle_ChangeDirectory - this is main function to change current directory.
 * @directory: A directory path to be changed.
 * An error message printed, when an error occured.
 */
void handle_ChangeDirectory(char *directory)
{
char *textmessage = "cd: The directory does`nt exist\n";

struct stat st = { 0 };

if (directory == NULL)
{
write(STDERR_FILENO, textmessage, strlen(textmessage));
return;
}
if (stat(directory, &st) == -1)
{
write(STDERR_FILENO, textmessage, strlen(textmessage));
return;
}
if (chdir(directory) != 0)
{
perror("cd");
}
}

/**
 * handle_pwd - this is main function to print current working directory.
 * An error message printed, when an error occured
 */
void handle_pwd(void)
{
char cwd[1024];
char *newline = "\n";

if (getcwd(cwd, sizeof(cwd)) == NULL)
{
perror("pwd");
return;
}
write(STDOUT_FILENO, cwd, strlen(cwd));
write(STDOUT_FILENO, newline, strlen(newline));
}

/**
 * handle_echo - this is main function to print a message.
 * @textmessage: Message to be printed.
 * When message is NULL or an empty string, nothing is printed.
 */
void handle_echo(char *textmessage)
{
char *newline = "\n";
if (textmessage == NULL || strlen(textmessage) == 0)
{
return;
}
write(STDOUT_FILENO, textmessage, strlen(textmessage));
write(STDOUT_FILENO, newline, strlen(newline));
}

/**
 * handle_ls - this is main function to list all files.
 * An error message printed, when an error occured
 */
void handle_ls(void)
{
DIR *d;
struct dirent *dir;
d = opendir(".");

if (d)
{
while ((dir = readdir(d)) != NULL)
{
write(STDOUT_FILENO, dir->d_name, strlen(dir->d_name));
write(STDOUT_FILENO, "\n", sizeof("\n") - 1);
}
closedir(d);
}
else
{
perror("ls");
}
}

/**
 * main - this is main entry point of my own shell program.
 * @argc: number of command-line arguments.
 * @argv: Array of strings contains list of arguments.
 * Return: Always returns 0.
 */
int main(int argc, char *argv[])
{
char input[100];
char *prompt = "Shell $ ";
char *textmessage = "Input is too long\n";
char *command, *argument;
char *unknown_command = "Unknown command: ";
char *newline = "\n";

while (1)
{
write(STDOUT_FILENO, prompt, strlen(prompt));
fgets(input, sizeof(input), stdin);

if (strlen(input) >= sizeof(input) - 1)
	write(STDERR_FILENO, textmessage, strlen(textmessage));
	continue;

input[strcspn(input, "\n")] = '\0';
command = strtok(input, " ");
argument = strtok(NULL, " ");

if (command == NULL)
	continue;
if (strcmp(command, "cd") == 0)
	handle_ChangeDirectory(argument);
else if (strcmp(command, "pwd") == 0)
	handle_pwd();
else if (strcmp(command, "echo") == 0)
	handle_echo(argument);
else if (strcmp(command, "ls") == 0)
	handle_ls();
else if (strcmp(command, "exit") == 0)
	exit(0);
else
	write(STDERR_FILENO, newline, strlen(newline));
	write(STDERR_FILENO, unknown_command, strlen(unknown_command));
	write(STDERR_FILENO, command, strlen(command));
}
return (0);
}
