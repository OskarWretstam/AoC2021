#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOF 10000000


int main(int argc, char* argv[])
{
   int c;
   char *a = realloc(NULL, MAX_NOF*sizeof(char));
   if(a == NULL)
   {
      printf("Error 1\n");
      return 1;
   }

   long long unsigned nof = 0;

   while ((c = getchar()) != EOF)
   {
      if(c != ',' && c != '\n')
      {
         a[nof++] = c-48;
      }
   }


   int to_add;
   int allocs = 1;
   for(int i = 0; i < 256; i++)
   {
      to_add = 0;
      for(int j = 0; j < nof; j++)
      {
         if(a[j] != 0)
         {
            a[j]--;
         }
         else
         {
            a[j] = 6;
            to_add++;
         }
      }

      for(int j = 0; j < to_add; j++)
      {
         if(nof == MAX_NOF)
         {
            printf("Realloc\n");
            allocs++;
            char *a = realloc(a, allocs*MAX_NOF*sizeof(char));

            if(a == NULL)
            {
               printf("Error 2\n");
               return 1;
            }
         }

         a[nof++] = 8;
      }
   }

   printf("%llu\n", nof);
}
