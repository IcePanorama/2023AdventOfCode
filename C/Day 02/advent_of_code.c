#include <stdlib.h>

#include "advent_of_code.h"

const int MAX_LINE_LEN = 1024;

FILE* 
load_file(char* filename)
{
  FILE *file;
  file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Error loading file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  return file;
}
