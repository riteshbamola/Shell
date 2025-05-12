// shell.h - Main header file for the shell implementation
// Author: Ritesh Bamola and Team

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

// Global variables
extern char host[1000];
extern char user[1000];
extern char homedir[1010];
extern char line[1000006];
extern char execpath[1000];
extern char execdir[1000];

extern int INFILE;
extern int OUTFILE;
extern int JOBCTR;
extern int PIPEIN;
extern pid_t SHELLPID;

// Job structure to track background processes
typedef struct jobs
{
  char name[100];
  pid_t pid;
} jobs;

extern jobs job[1000];

// Function prototypes
void parse(char *line, char **tokens, char *delim);
void invokeShell();
void sig_handler(int signum);
int spaceCheck();
void executeCommand();
void launch_new_shell();
void deleteJob(int jobpid);

#endif