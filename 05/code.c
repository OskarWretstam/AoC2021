#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_CORDS 500000

typedef struct
{
   int point[2];
   int x;
} p_tv; // ;)

int max_abs(
   int a,
   int b
   )
{
   a = abs(a);
   b = abs(b);

   if(a > b)
   {
      return a;
   }
   else if(b > a)
   {
      return b;
   }

   return a;
}

int main(
   int argc,
   char* argv[]
   )
{
   p_tv line_cords[2], cords[MAX_CORDS];
   int line_no = 0, point_ix, dim = 0, nof_cords = 0;

   int del_y, del_x, x, y;

   int overlaps = 0, found_overlap;

   memset(cords, 0, MAX_CORDS*sizeof(p_tv));

   char line[MAX_LINE], *next_row;
   for (next_row = fgets(line, MAX_LINE, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE, stdin))
   {
      line_no++;
      point_ix = 0;

      for(char* tok = strtok(line, ", ->\n"); tok != NULL; tok = strtok(NULL, ", ->\n"))
      {
         sscanf(tok, "%d", &line_cords[point_ix].point[dim]);

         point_ix = (point_ix+dim);
         dim = (dim+1)%2;
      }

      // if(line_cords[0].point[0] == line_cords[1].point[0] ||
      //    line_cords[0].point[1] == line_cords[1].point[1])
      // {
         del_x = line_cords[0].point[0] - line_cords[1].point[0];
         del_y = line_cords[0].point[1] - line_cords[1].point[1];
         x = line_cords[0].point[0];
         y = line_cords[0].point[1];

         for(int i = 0; i <= max_abs(del_x, del_y); i++)
         {
            found_overlap = 0;
            for(int j = 0; j < nof_cords; j++)
            {
               if(cords[j].point[0] == x &&
                  cords[j].point[1] == y)
               {
                  cords[j].x++;
                  if(cords[j].x == 1)
                  {
                     overlaps++;
                  }
                  found_overlap = 1;
               }
            }

            if(!found_overlap)
            {
               cords[nof_cords].point[0] = x;
               cords[nof_cords].point[1] = y;
               nof_cords++;
               if(nof_cords == MAX_CORDS)
               {
                  printf("\n\n Max coordinates\n");
                  return 1;
               }
            }

            if(del_x < 0)
            {
               x++;
            }
            else if(del_x)
            {
               x--;
            }

            if(del_y < 0)
            {
               y++;
            }
            else if(del_y)
            {
               y--;
            }
         // }
      }
   }

   printf("Overlaps: %d\n", overlaps);
}
