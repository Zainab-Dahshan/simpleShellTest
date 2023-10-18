#include "shell.h"

char commandHistory[MAXIMUM_HISTORY_SIZE][MAXIMUM_COMMAND_LENGTH];
int historyCount = 0;

/**
 * add_To_History - main function that adds command to command history.
 * Description: a function that adds command to command history array.
 * when the maximum history size has been reached, oldest command is
 * removed from the history to make room for the new one.
 * @command: Command added to history.
 */
void add_To_History(const char *command)
{
int z = 1;

if (historyCount < MAXIMUM_HISTORY_SIZE)
{
strcpy(commandHistory[historyCount], command);
historyCount++;
}
else
{
for (z = 1; z < MAXIMUM_HISTORY_SIZE; z++)
{
strcpy(commandHistory[z - 1], commandHistory[z]);
}
strcpy(commandHistory[MAXIMUM_HISTORY_SIZE - 1], command);
}
}
/**
 * display_History - main function that displays command
 * history to the console.
 * Description: The function displays command history to
 * the console, with each command preceded by its index
 * in the history. The index starts at 1 for the most recent
 * command and increments for each older command.
 */
void display_History(void)
{
int z = 0;
char buffer[1050];

for (z = 0; z < historyCount; z++)
{
snprintf(buffer, sizeof(buffer), "%d: %s\n", z + 1, commandHistory[z]);
write(STDOUT_FILENO, buffer, strlen(buffer));
}
}
/**
 * clear_History - main function that clears command history and
 * frees the allocated memory.
 * Description: The function clears command history array and
 * frees memory allocated for each command. After calling
 * this function, then history count will be 0
 * and all elements of command history array will be empty.
 */
void clear_History(void)
{
memset(commandHistory, 0, sizeof(commandHistory));
historyCount = 0;
}
/**
 * ourmain - main function of the shell program.
 * Description: The function is a main entry point of a shell program.
 * It reads commands from console, adds them to command history, and
 * executes them. If user enters "history", command history is displayed.
 * If user enters "clear_History", command history is cleared.
 *
 * Return: The exit code of our program.
 */
int ourmain(void)
{
char command[MAXIMUM_COMMAND_LENGTH];

while (1)
{
write(STDOUT_FILENO, "Enter a command: ", 17);
fgets(command, sizeof(command), stdin);
command[strcspn(command, "\n")] = '\0';

add_To_History(command);

if (strcmp(command, "history") == 0)
{
display_History();
}
else if (strcmp(command, "clearhistory") == 0)
{
clear_History();
}
else
{
/*Handle other commands*/
}
}
return (0);
}
