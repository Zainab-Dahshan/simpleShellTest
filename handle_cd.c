#include "shell.h"

/**
 * print_current_directory - main function to print current directory.
 * Return: 0 on success, otherwise -1 on failure.
 */
int print_current_directory(void)
{
char cwd[1024];

if (getcwd(cwd, sizeof(cwd)) != NULL)
{
write(STDOUT_FILENO, "Current directory: ", 20);
write(STDOUT_FILENO, cwd, strlen(cwd));
write(STDOUT_FILENO, "\n", 1);
return (0);
}
else
{
perror("getcwd");
return (-1);
}
}

/**
 * prompt_directory_path - main function to prompt user
 * for a directory path.
 * Return: An user input as a dynamic allocated string.
 */
char *prompt_directory_path(void)
{
char *path = NULL;
size_t size = 0;
ssize_t read = getline(&path, &size, stdin);
size_t len = strlen(path);

write(STDOUT_FILENO, "Enter directory path: ", 22);

if (read != -1)
{
if (len > 0 && path[len - 1] == '\n')
{
path[len - 1] = '\0';
}
}
else
{
perror("getline");
}
return (path);
}

/**
 * main - main ebtry point to make this program changes current
 * directory based on command-line argument or prompts user
 * for a directory path if no argument is provided. After
 * changing a directory, it prints current directory path.
 * @argc: Number of command-line arguments.
 * @argv: An array of strings contains command-line arguments.
 * Return: 0 on successful execution. Or -1 when an error occurs
 * during directory change or printing current directory.
 */
int main(int argc, char *argv[])
{
char *path = prompt_directory_path();

if (argc > 1)
{
if (chdir(argv[1]) != 0)
{
perror("chdir");
free(path);
return (-1);
}
}
else
{
if (path != NULL)
{
if (chdir(path) != 0)
{
perror("chdir");
free(path);
return (-1);
}
free(path);
}
}
if (print_current_directory() != 0)
{
return (-1);
}
return (0);
}
