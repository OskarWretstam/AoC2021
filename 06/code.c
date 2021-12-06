#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOF 1000000
#define AGE_CLASSES 9


int main(int argc, char* argv[])
{
   int c;
   char a[MAX_NOF], b[MAX_NOF];
   long long unsigned nofa = 0, nofb = 0;

   while ((c = getchar()) != EOF)
   {
      if(c != ',' && c != '\n')
      {
         a[nofa++] = c-48;
         b[nofb++] = c-48;
      }
   }

   int to_add;
   for(int i = 0; i < 80; i++)
   {
      to_add = 0;
      for(int j = 0; j < nofa; j++)
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
         if(nofa == MAX_NOF)
         {
            printf("Error\n");
            return 1;
         }

         a[nofa++] = 8;
      }
   }

   printf("%lld\n", nofa);

   long long int x[AGE_CLASSES];
   long long int to_add_long;
   memset(x, 0, AGE_CLASSES*sizeof(long long int));

   for(int i = 0; i < nofb; i++)
   {
      x[b[i]]++;
   }

   for(int i = 0; i < 256; i++)
   {
      to_add_long = x[0];

      for(int j = 0; j < AGE_CLASSES-1; j++)
      {
         x[j] = x[j+1];
      }

      x[6] += to_add_long;
      x[8] = to_add_long;
   }

   nofb = 0;
   for(int i = 0; i < AGE_CLASSES; i++)
   {
      nofb += x[i];
   }

   printf("%lld\n", nofb);

}
