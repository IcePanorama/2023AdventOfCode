#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* load_file(char* filename);
int char_to_int(char c);

int
main (int argc, char** argv)
{
  if (argc < 2)
  {
    puts("Error! Improper usage. Run this program by writing: ./main [some_input].txt");
    exit(EXIT_FAILURE);
  }

  char *filename = argv[1];
  FILE* file = load_file(filename);

  const int MAX_LINE_LEN = 100;
  char line[MAX_LINE_LEN];

  int sum = 0;
  while(fgets(line, MAX_LINE_LEN, file) != NULL)
  {
    size_t line_len = strlen(line);

    size_t start = 0;
    size_t end = line_len - 1;

    while (!(line[start] >= '0' && line[start] <= '9'))
    {
      start++;
    }

    while (!(line[end] >= '0' && line[end] <= '9'))
    {
      end--;
    }

    char new_num[] = { line[start], line[end], '\0'};

    sum += atoi(new_num);
  }

  printf("%d\n", sum);

  fclose(file);
  return 0;
}

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

int 
char_to_int(char c)
{
  return c - '0';
}
