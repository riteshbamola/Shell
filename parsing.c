// parsing.c - Implementation of parsing functions
// Author: Ritesh Bamola and Team

#include "shell.h"
#include "parsing.h"

// Used to tokenize lines into commands
void parse(char *line, char **tokens, char *delim)
{
  char *temp;

  // Splitting line by delim and saving it into temp
  temp = strtok(line, delim);
  int i = 0;
  while (temp != NULL)
  {
    tokens[i++] = temp;
    temp = strtok(NULL, delim);
  }
}

void checkInfile(char *tokens)
{
  char *temp[100] = {NULL};

  parse(tokens, temp, "<");

  if (temp[1] != NULL)
  {
    char *temp1[100] = {NULL};
    parse(temp[1], temp1, " ");

    INFILE = open(temp1[0], O_RDONLY);
  }
}

void checkOutfile(char *tokens)
{
  char *temp[100] = {NULL};

  parse(tokens, temp, ">");

  if (temp[1] != NULL)
  {
    char *temp1[100] = {NULL};
    parse(temp[1], temp1, " ");

    OUTFILE = open(temp1[0], O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
  }
  else
    OUTFILE = 1;
}

int spaceCheck()
{
  int i = 0;
  while (line[i] != '\0')
  {
    if (line[i] != ' ' && line[i] != '\t')
      return 0;
    i++;
  }
  return 1;
}