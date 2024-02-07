#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* load_file(char* filename);
int char_to_int(char c);
void word_to_num(char* line, char* word, int word_index);

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

  int num_valid_digits = 9;
  char *valid_digits[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
  };

  int sum = 0;
  while(fgets(line, MAX_LINE_LEN, file) != NULL)
  {
    size_t line_len = strlen(line);

    for (size_t i = 0; i < line_len; i++)
    {
      // test for words going forward ...
      for (int j = 0; j < num_valid_digits; j++)
      {
        if (line[i] != valid_digits[j][0])
        {
          continue;
        }

        word_to_num(line, valid_digits[j], j);
        break;
      }

      // ... and backwards
      // helps differentiate bet. digits like "two" and "three"
      for (int j = num_valid_digits - 1; j >= 0; j--)
      {
        if (line[i] != valid_digits[j][0])
        {
          continue;
        }
        
        word_to_num(line, valid_digits[j], j);
        break;
      }
    }

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

  printf("Sum: %d\n", sum);

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

void 
word_to_num(char* line, char* word, int word_index)
{
  char valid_nums[] = {'1','2','3','4','5','6','7','8','9'};

  char* p;
  while (1)
  {
    p = strstr(line, word);
    if (!p)
    {
      break;
    }
    p[0] = valid_nums[word_index];
  }
}
