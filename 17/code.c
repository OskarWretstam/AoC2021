#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 50

static int interv[4];

typedef struct
{
   int x;
   int y;
} c_t;


int f(c_t vel, int *y_max)
{
   c_t pos = {0, 0};
   *y_max = 0;

   while(pos.x < interv[1] && pos.y > interv[2])
   {
      pos.x += vel.x;
      pos.y += vel.y;

      if((pos.x >= interv[0]) && (pos.x <= interv[1]) && (pos.y >=  interv[2]) && (pos.y <= interv[3]))
      {
         return 1;
      }

      if(pos.y > *y_max)
      {
         *y_max = pos.y;
      }

      if(vel.x > 0)
      {
         vel.x--;
      }
      else if(vel.x < 0)
      {
         vel.x++;
      }

      vel.y--;
   }

   return 0;
}

int main(int argc, char* argv[])
{
   char line[LINE], *next_row;
   int tmp, a = 0;
   for (next_row = fgets(line, LINE, stdin); next_row!=NULL; next_row=fgets(line, LINE, stdin))
   {
      for(char* tok = strtok(line, "=\n., y"); tok != NULL; tok = strtok(NULL, "=\n., y"))
      {
         if(sscanf(tok, "%d", &tmp))
         {
            interv[a++] = tmp;
         }
      }
   }

   c_t v0;
   int y_max, ym = 0;
   int cnt = 0;

   for(int x = 0; x <= interv[1]; x++)
   {
      for(int y = interv[2]; y <= 150; y++)
      {
         v0.x = x;
         v0.y = y;

         if(f(v0, &y_max))
         {
            cnt++;
            if(y_max > ym)
            {
               ym = y_max;
            }
         }
      }
   }

   printf("%d\n", ym);
   printf("%d\n", cnt);

   return 0;
}
