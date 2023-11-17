#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_ARG 50

char *readCommand(void);
int changeDirectory(char **var);
int checkexe(char **argsC, char **argv, char **env);
int _strlen(char *str);
int home(char **argv, char **env);
int prompt(void);
char *rightPath(char *arg);
int prints(char *str);
int built_in(char **var, char *buff, char **env);
char *Cstrcat(char *str1, char *str2);
char *_strcat(const char *str1, const char *str2);
char *getPATH(char **env);
int tokenize(char *command, char *argsC[]);
int exeCmd(char *argsC[], char **argv, char **env);
int _strcmp(const char *str1, const char *str2);
char *removeNC(char *str, int len);
bool is_space(char *buff);
int _isspace(int ch);

#endif
