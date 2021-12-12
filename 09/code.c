#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDE 100
#define SIZE SIDE*SIDE

typedef struct
{
   int row;
   int col;
} min_t;

int count(int* a, int b, int c)
{
   if(a[b*SIDE+c] == 9)
   {
      return 0;
   }

   a[b*SIDE+c] = 9;
   int ret = 1;

   if(c-1 >= 0)
   {
      ret += count(a, b, c-1);
   }

   if(c+1 < SIDE)
   {
      ret += count(a, b, c+1);
   }

   if(b-1 >= 0)
   {
      ret += count(a, b-1, c);
   }

   if(b+1 < SIDE)
   {
      ret += count(a, b+1, c);
   }

   return ret;
}

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
   for(int i = 0; i < SIDE; i++)
   {
      for(int j = 0; j < SIDE; j++)
      {
         ix = i*SIDE+j;

         if(j-1 >= 0)
         {
            if(a[ix] >= a[ix-1])
            {
               continue;
            }
         }

         if(j+1 < SIDE)
         {
            if(a[ix] >= a[ix+1])
            {
               continue;
            }
         }

         if(i-1 >= 0)
         {
            if(a[ix] >= a[ix-SIDE])
            {
               continue;
            }
         }

         if(i+1 < SIDE)
         {
            if(a[ix] >= a[ix+SIDE])
            {
               continue;
            }
         }

         b += (a[ix]+1);
         min[nofm].row = i;
         min[nofm].col = j;
         nofm++;
      }
   }

   printf("%d\n", b);

   int d[4] = {0}, l, tmp;
   for(int i = 0; i < nofm; i++)
   {
      d[3] = count(a, min[i].row, min[i].col);

      l = 3;
      while(l > 0 && d[l-1] < d[l])
      {
         tmp = d[l-1];
         d[l-1] = d[l];
         d[l] = tmp;
         l--;
      }
   }

   printf("%lld\n", d[0]*d[1]*d[2]);

   return 0;
}
