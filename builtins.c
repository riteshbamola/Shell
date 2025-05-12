// builtins.c - Implementation of built-in shell commands
// Author: Ritesh Bamola and Team

#include "shell.h"
#include "builtins.h"

// Making built-in "echo" command
void executeECHO(char **tokens)
{
  int i = 1;
  int j = 0;
  char input[1000006];

  int flag1 = 0;
  int flag2 = 0;

  // checking for inverted commas
  while (tokens[i] != NULL)
  {
    int k;
    for (k = 0; tokens[i][k] != '\0'; k++)
    {
      if (flag1 == 1)
      {
        if (tokens[i][k] == '\"')
          flag1 = 0;
        else
          input[j++] = tokens[i][k];
      }
      else if (flag2 == 1)
      {
        if (tokens[i][k] == '\'')
          flag2 = 0;
        else
          input[j++] = tokens[i][k];
      }
      else
      {
        if (tokens[i][k] == '\"')
          flag1 = 1;
        else if (tokens[i][k] == '\'')
          flag2 = 1;
        else
          input[j++] = tokens[i][k];
      }
    }
    i++;
  }
  input[j] = '\0';

  // Checking if a inverted comma is left open
  if (flag1 == 0 && flag2 == 0)
    printf("%s\n", input);
  else
    printf("Error: Wrong Input\n");
}

// Making built-in "cd" command
void executeCD(char **tokens)
{
  char home[1000];

  strcpy(home, execdir);

  int i;
  int len = strlen(execdir);

  // If command is 'cd' , change to ~
  // Changing ~ to home directory of executable
  // Then using chdir to change directory
  if (tokens[1] == NULL)
    chdir(execdir);
  else if (tokens[1][0] == '~')
  {
    for (i = 1; tokens[1][i] != '\0'; i++)
    {
      home[i + len - 1] = tokens[1][i];
    }
    home[i + len - 1] = '\0';
    if (chdir(home) != 0)
      perror("Error");
  }
  else if (chdir(tokens[1]) != 0)
    perror("Error");
}

// Making built-in "pwd" command
void executePWD()
{
  char home[1000];
  getcwd(home, 1000);
  printf("%s\n", home);
}

// Making "pinfo" user-defined command
void executePINFO(char **tokens)
{
  char status[10000] = "cat /proc/";
  int j = strlen(status);

  // Checking if pid is given or not
  if (tokens[1] == NULL)
  {
    char buff[1000] = "";
    readlink("/proc/self/exe", buff, sizeof(buff) - 1);
    printf("Executable Path -- %s\n", buff);

    char a[20] = "self/status";
    int i;

    for (i = 0; a[i] != '\0'; i++)
      status[j++] = a[i];
  }
  else
  {
    int i;
    char b[10] = "/status";

    char a[1000] = "/proc/";
    char c[10] = "/exe";

    int k = 6;

    for (i = 0; tokens[1][i] != '\0'; i++)
      a[k++] = tokens[1][i];
    for (i = 0; c[i] != '\0'; i++)
      a[k++] = c[i];

    char buff[1000] = "";
    readlink("/proc/self/exe", a, sizeof(buff) - 1);
    printf("Executable Path -- %s\n", buff);

    for (i = 0; tokens[1][i] != '\0'; i++)
      status[j++] = tokens[1][i];
    for (i = 0; b[i] != '\0'; i++)
      status[j++] = b[i];
  }

  // Seperating commands and arguments
  char *final[1000] = {NULL};
  parse(status, final, " ");

  // Forking to run cat /proc/[pid]/status
  pid_t pid;
  int flag;

  pid = fork();
  if (pid < 0)
  {
    perror("Forking Error ");
  }
  else if (pid == 0)
  {
    if (execvp(*final, final) < 0)
    {
      perror("Error ");
      exit(0);
    }
  }
  else
  {
    wait(&flag);
  }
}