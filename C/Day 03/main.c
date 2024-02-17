#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advent_of_code.h"

int get_line_width(FILE* file);
char **create_2d_array(int num_rows, int num_cols);
void free_2d_array(char** arr, int num_rows);
int load_array_from_file(FILE* file, char* arr[static 1]);
bool is_valid(char* arr[static 1], int num_rows, int num_cols, int i, int j);

int 
main (int argc, char **argv)
{
  if (argc < 2)
  {
    puts("Error: Invalid Usage. Correct usage: ./main [some_file].txt");
    exit(EXIT_FAILURE);
  }
  char *filename = argv[1];
  FILE* file = load_file(filename);

  int line_width = get_line_width(file);
  // still need to rewind with getline()
  rewind(file);

  char **input = create_2d_array(MAX_LINE_LEN, line_width);
  int num_rows = load_array_from_file(file, input);

  int ans = 0;
  for (int i = 0; i <= num_rows; i++)
  {
    printf("%s\n", input[i]);
    int j = 0;
    while (j < line_width)
    {
      int start = j;
      char num_str[line_width];
      int num_pos = 0;
      while (j < line_width && isdigit(input[i][j]))
      {
        num_str[num_pos] = input[i][j];
        num_pos++;
        j++;
      }
      num_str[num_pos] = '\0';
      if (strlen(num_str) == 0)
      {
        j++;
        continue;
      }

      int num = atoi(num_str);

      if (is_valid(input, num_rows, line_width, i, start - 1) || is_valid(input, num_rows, line_width, i, j))
      {
        ans += num;
        continue;
      }

      for (int k = start - 1; k < (j + 1); k++)
      {
        if (is_valid(input, num_rows, line_width, i - 1, k) || is_valid(input, num_rows, line_width, i + 1, k))
        {
          ans += num;
          break;
        }
      }
    }
  } 

  printf("answer: %d\n", ans);

  free_2d_array(input, MAX_LINE_LEN);
  fclose(file);
  return 0;
}

int 
get_line_width(FILE* file)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  nread = getline(&line, &len, file);
  line[nread - 1] = '\0';
  int line_width = strlen(line);
  free(line);
  return line_width;

}

char**
create_2d_array(int num_rows, int num_cols)
{
  char **input = malloc(sizeof(char *) * num_rows);
  for (int i = 0; i < num_rows; i++)
  {
    // + 1 to account for \0
    input[i] = calloc(num_cols, sizeof(char) + 1);
  }

  return input;
}

int 
load_array_from_file(FILE* file, char* arr[static 1])
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  int line_num = 0;
  while((nread = getline(&line, &len, file)) != -1)
  {
    strncpy(arr[line_num], line, nread);
    arr[line_num][nread - 1] = '\0';
    line_num++;
  }
  free(line);
  return line_num;
}

void 
free_2d_array(char** arr, int num_rows)
{
  for (int i = 0; i < num_rows; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

bool 
is_valid(char* arr[static 1], int num_rows, int num_cols, int i, int j)
{
  if (!(0 <= i  && i < num_rows && 0 <= j && j < num_cols))
  {
    return false;
  }
  return arr[i][j] != '.' && arr[i][j] != '\0' && arr[i][j] != '\n' && !(isdigit(arr[i][j]));
}

