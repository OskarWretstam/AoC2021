#include <stdio.h>


#define MAX_LINE_LENGTH 20

int main(int argc, char* argv[])
{
   int a = 0, b = 0, ix = 0, current_number, prev_b, to_remove[3], c;
   int steps = 0, steps_filtered = 0;
   char line[MAX_LINE_LENGTH], *next_row;
	for (next_row = fgets(line, MAX_LINE_LENGTH, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE_LENGTH, stdin))
   {
      sscanf(line, "%d", &current_number);

      if(ix < 3)
      {
         b += current_number;
         to_remove[ix] = current_number;
      }
      else
      {
         prev_b = b;
         b += current_number;
         b -= to_remove[0];

         if(b > prev_b)
         {
            steps_filtered++;
         }

         to_remove[0] = to_remove[1];
         to_remove[1] = to_remove[2];
         to_remove[2] = current_number;
      }

      if(ix > 0 && current_number > a)
      {
         steps++;
      }

      a = current_number;

      ix++;
   }

   printf("Part 1: %d\n", steps);
   printf("Part 2: %d\n", steps_filtered);
}
