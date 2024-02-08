#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advent_of_code.h"

int
main (int argc, char **argv)
{
  if (argc < 2)
  {
    puts("Error: Improper Usage. Run using: ./main [some_file].txt");
    exit(EXIT_FAILURE);
  }

  char* filename = argv[1];
  FILE* file = load_file(filename);

  char line[MAX_LINE_LEN];

  int total = 0;
  while(fgets(line, MAX_LINE_LEN, file) != NULL)
  {
    if (line[0] == '\n')
    {
      break;
    }

    int red = 12;
    int green = 13;
    int blue = 14;

    char *game = strtok(line, ":");

    char *cnt_str = strtok(NULL, ", ");
    
    bool is_impossible = false;
    while (cnt_str != NULL)
    {
      int cnt = atoi(cnt_str);

      char *color = strtok(NULL, ", ");

      if (strncmp(color, "red", 3) == 0)
      {
        red -= cnt;
        if (red < 0)
        {
          is_impossible = true;
        }
      }
      else if (strncmp(color, "green", 5) == 0)
      {
        green -= cnt;
        if (green < 0)
        {
          is_impossible = true;
        }
      }
      else if (strncmp(color, "blue", 4) == 0)
      {
        blue -= cnt;
        if (blue < 0)
        {
          is_impossible = true;
        }
      }

      if (color[strlen(color) - 1] == ';')
      {
        red = 12;
        green = 13;
        blue = 14;
      }
      cnt_str = strtok(NULL, ", ");
    }

    game = strtok(game, " ");
    int game_id = atoi(strtok(NULL, " "));

    if (is_impossible)
    {
      is_impossible = false;
    }
    else
    {
      total += game_id;
    }
  }

  printf("Total: %d\n", total);

  fclose(file);

  return 0;
}
