#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDE 10
#define SIZE 100

typedef struct
{
   int val;
   int flashed;
} type_t;

int main(int argc, char* argv[])
{
   type_t a[SIZE];
   memset(a, 0, SIZE*sizeof(type_t));
   int nof = 0;
   char c;

   while ((c = getchar()) != EOF)
   {
      if(c != '\n')
      {
         if(nof == SIZE)
         {
            printf("Error\n");
            return 1;
         }

         a[nof].val = c-48;
         nof++;
      }
   }

   int go;
   long long int tot = 0;
   int i = 0, flash_cnt;
   while(1)
   {
      for(int j = 0; j < nof; j++)
      {
         a[j].val++;
      }

      do
      {
         go = 0;

         for(int j = 0; j < SIDE; j++)
         {
            for(int k = 0; k < SIDE; k++)
            {
               if(a[j*SIDE+k].flashed == 0 && a[j*SIDE+k].val > 9)
               {
                  a[j*SIDE+k].flashed = 1;
                  tot++;
                  go = 1;

                  if(j-1 >= 0)
                  {
                     a[(j-1)*SIDE+k].val++;
                  }

                  if(j+1 < SIDE)
                  {
                     a[(j+1)*SIDE+k].val++;
                  }

                  if(k-1 >= 0)
                  {
                     a[j*SIDE+(k-1)].val++;
                  }

                  if(k+1 < SIDE)
                  {
                     a[j*SIDE+(k+1)].val++;
                  }

                  if(j-1 >= 0 && k-1 >= 0)
                  {
                     a[(j-1)*SIDE+(k-1)].val++;
                  }

                  if(j+1 < SIDE && k+1 < SIDE)
                  {
                     a[(j+1)*SIDE+(k+1)].val++;
                  }

                  if(j-1 >= 0 && k+1 < SIDE)
                  {
                     a[(j-1)*SIDE+(k+1)].val++;
                  }

                  if(j+1 < SIDE && k-1 >= 0)
                  {
                     a[(j+1)*SIDE+(k-1)].val++;
                  }
               }
            }
         }
      }
      while(go);

      flash_cnt = 0;
      for(int j = 0; j < nof; j++)
      {
         if(a[j].flashed == 1)
         {
            flash_cnt++;
            a[j].val = 0;
            a[j].flashed = 0;
         }
      }

      i++;

      if(i == 100)
      {
         printf("%lld\n", tot);
      }

      if(flash_cnt == 100)
      {
         printf("%d\n", i);
         return 0;
      }
   }

   return 0;
}
