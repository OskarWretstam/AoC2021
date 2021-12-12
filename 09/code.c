#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COL 100
#define ROW 100
#define SIZE COL*ROW

typedef struct
{
   int ix;
   int val;
} min_t;

int main(int argc, char* argv[])
{
   int a[SIZE], nof = 0;
   char c;

   min_t min[SIZE];

   while ((c = getchar()) != EOF)
   {
      if(c != '\n')
      {
         if(nof == SIZE)
         {
            printf("Error\n");
            return 1;
         }
         a[nof++] = c-48;
      }
   }

   int b = 0, ix, nofm = 0;
   for(int i = 0; i < COL; i++)
   {
      for(int j = 0; j < ROW; j++)
      {
         ix = i*ROW+j;

         if(j-1 >= 0)
         {
            if(a[ix] >= a[ix-1])
            {
               continue;
            }
         }

         if(j+1 < ROW)
         {
            if(a[ix] >= a[ix+1])
            {
               continue;
            }
         }

         if(i-1 >= 0)
         {
            if(a[ix] >= a[ix-ROW])
            {
               continue;
            }
         }

         if(i+1 < COL)
         {
            if(a[ix] >= a[ix+COL])
            {
               continue;
            }
         }

         b += (a[ix]+1);
         min[nofm].ix = ix;
         min[nofm].val = a[ix];
         nofm++;
      }
   }

   printf("%d\n", b);

   for(int i = 0; i < nofm; i++)
   {

   }



   return 0;
}
