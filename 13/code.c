#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_C 1000

typedef struct
{
   int x;
   int y;
   int a;
} c_t;

int main(int argc, char* argv[])
{
   c_t d[MAX_C], s = {0}, f = {0};
   int nofd = 0, b, nofdd, p = 1;

   char line[MAX_LINE], *next_row;
   for (next_row = fgets(line, MAX_LINE, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE, stdin))
   {
      for(char* tok = strtok(line, "=\n"); tok != NULL; tok = strtok(NULL, "=\n"))
      {
         if(tok[0] == 'f')
         {
            // Start folding
            f.x = f.y = 0;
            b = (tok[strlen(tok)-1] == 'x');
            tok = strtok(NULL, "=\n");
            if(b)
            {
               f.x = atoi(tok);
               f.y = s.y;
            }
            else
            {
               f.y = atoi(tok);
               f.x = s.x;
            }

            for(int i = 0; i < nofd; i++)
            {
               if(d[i].a)
               {
                  if(d[i].x > f.x)
                  {
                     d[i].x = f.x - (d[i].x - f.x);
                  }

                  if(d[i].y > f.y)
                  {
                     d[i].y = f.y - (d[i].y - f.y);
                  }

                  for(int j = 0; j < nofd; j++)
                  {
                     if(d[j].a && i != j)
                     {
                        if(d[i].x == d[j].x)
                        {
                           if(d[i].y == d[j].y)
                           {
                              d[i].a = 0;
                              nofdd--;
                           }
                        }
                     }
                  }
               }
            }

            if(p)
            {
               printf("%d\n", nofdd);
               p = 0;
            }
         }
         else
         {
            sscanf(tok, "%d%*c%d", &d[nofd].x, &d[nofd].y);
            d[nofd].a = 1;

            if(d[nofd].x > s.x)
            {
               s.x = d[nofd].x;
            }

            if(d[nofd].y > s.y)
            {
               s.y = d[nofd].y;
            }

            nofd++;
            nofdd = nofd;
         }
      }
   }

   // Done, print answer..
   s.x = s.y = 0;

   for(int i = 0; i < nofd; i++)
   {
      if(d[i].a)
      {
         if(d[i].x > s.x)
         {
            s.x = d[i].x;
         }

         if(d[i].y > s.y)
         {
            s.y = d[i].y;
         }
      }
   }

   for(int i = 0; i <= s.y; i++)
   {
      for(int j = 0; j <= s.x; j++)
      {
         for(int k = 0; k < nofd; k++)
         {
            if(d[k].a)
            {
               if(d[k].x == j && d[k].y == i)
               {
                  printf("x");
                  break;
               }
            }

            if(k == nofd-1)
            {
               printf(" ");
            }
         }
      }
      printf("\n");
   }

   return 0;
}
