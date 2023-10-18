#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAXIMUM_PATH_SIZE 1024
#define MAXIMUM_COMMAND_LENGTH 1024
#define MAXIMUM_ARGUMENTS 100
#define MAXIMUM_COMMANDS 100
#define MAXIMUM_ARGUMENTS 100
#define MAXIMUM_HISTORY_SIZE 100

extern char **environ;

void handle_ChangeDirectory(char *directory);
void handle_pwd(void);
void handle_echo(char *textmessage);
void handle_ls(void);
int main(int argc, char *argv[]);
void split_Line(char *line, char **arguments);
int is_end_of_line(char c);
char *read_line();
int ourexecute_command(char **arguments);
void shell_Loop(void);
int ourmain(void);
char *resolve_command_path(char *command);
int execute_command(char *command, char **arguments,int background,
		char *input_file, char *output_file);
void handle_signal(int signal);
int print_current_directory(void);
char *prompt_directory_path(void);
void handle_environment(void);
void exit_shell(void);
void execute_background_command(char *command);
void print_help(void);
void add_To_History(const char *command);
void display_History(void);
void clear_History(void);
int split_command(char *command, char *arguments[]);
int search_path(char *command, char *path);
void exec_command(char *command, char **arguments);
void handle_piping(char **commands, int number_commands);
void handle_input_redirection(char *command, char *input_file);
void handle_output_redirection(char *command, char *output_file);
void parse(char *command, char **parameters);
void print_prompt(void);
void run_shell_non_interactive(const char *filename);
void split_Line(char *line, char **arguments);
void shell_Loop(void);
void ourexec_command(char *command);
int execu_command(char **arguments);
void handle_command(char *command);

#endif
