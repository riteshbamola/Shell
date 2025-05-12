// jobs.h - Header for job management
// Author: Ritesh Bamola and Team

#ifndef JOBS_H
#define JOBS_H

// Job management functions
void executeJOBS();
void executeKJOB(char **tokens);
void executeOVERKILL();
void executeFG(char **tokens);
int backgroundCheck(char **tokens);

#endif