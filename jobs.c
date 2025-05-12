// jobs.c - Implementation of job management functions
// Author: Ritesh Bamola and Team

#include "shell.h"
#include "jobs.h"

void deleteJob(int jobpid)
{
  int i;
  int flag = 0;
  for (i = 1; i < JOBCTR; i++)
  {
    if (job[i].pid == jobpid)
      flag = 1;

    if (flag == 1)
      job[i] = job[i + 1];
  }
}

void executeJOBS()
{
  int i;
  if (JOBCTR == 1)
    printf("No background processes running\n");
  for (i = 1; i < JOBCTR; i++)
    printf("[%d] %s [%d]\n", i, job[i].name, job[i].pid);
}

void executeKJOB(char **tokens)
{
  if (tokens[2] == NULL)
    printf("Less number of arguments given\n");
  else
  {
    if (atoi(tokens[1]) > JOBCTR)
      printf("Job number does not exist.");
    else
    {
      kill(job[atoi(tokens[1])].pid, atoi(tokens[2]));
      if (atoi(tokens[2]) == 9)
      {
        deleteJob(job[atoi(tokens[1])].pid);
        JOBCTR--;
      }
    }
  }
}

void executeOVERKILL()
{
  int i;

  if (JOBCTR > 1)
    for (i = JOBCTR - 1; i > 0; i--)
    {
      kill(job[i].pid, 9);
      signal(SIGCHLD, sig_handler);
    }
  else
    printf("No Background Jobs detected.\n");
  JOBCTR = 1;
}

void executeFG(char **tokens)
{
  if (tokens[1] == NULL)
    printf("Job number not specified\n");
  else
  {
    int jobno = atoi(tokens[1]);
    if (jobno < JOBCTR)
    {
      kill(job[jobno].pid, SIGCONT);
      JOBCTR--;
      deleteJob(job[jobno].pid);
      int status;
      wait(&status);
    }
    else
      printf("Job number does not exist\n");
  }
}

int backgroundCheck(char **tokens)
{
  int i = 0;
  while (tokens[i] != NULL)
  {
    if (strcmp(tokens[i], "&") == 0)
    {
      tokens[i] = NULL;
      return 1;
    }
    i++;
  }
  return 0;
}