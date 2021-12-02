#include <stdio.h>
#include  <string.h>

#define MAX_LINE_LENGTH 100

typedef struct
{
   int x;
   int y;
   int aim;
} pos_t;

int main(int argc, char* argv[])
{
   char line[MAX_LINE_LENGTH], *next_row;
   char direction[MAX_LINE_LENGTH];
   int steps;
   pos_t pos1 = {0, 0, 0};
   pos_t pos2 = {0, 0, 0};


	for (next_row = fgets(line, MAX_LINE_LENGTH, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE_LENGTH, stdin))
   {
      sscanf(line, "%s %d\n", direction, &steps);

      if(strcmp(direction, "forward") == 0)
      {
         pos1.x += steps;
         pos2.x += steps;
         pos2.y += (pos2.aim*steps);
      }
      else if(strcmp(direction, "up") == 0)
      {
         pos1.y -= steps;
         pos2.aim -= steps;
      }
      else if(strcmp(direction, "down") == 0)
      {
         pos1.y += steps;
         pos2.aim += steps;
      }
      else
      {
         return 1;
      }
   }

   printf("Part1: %d\n", pos1.x*pos1.y);
   printf("Part2: %d\n", pos2.x*pos2.y);
}
