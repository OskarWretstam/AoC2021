#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 200
#define LINES 100

int cmpfunc (const void * a, const void * b) {
   if(*(long long int*)b > *(long long int*)a)
   {
      return -1;
   }
   else if(*(long long int*)b < *(long long int*)a)
   {
      return 1;
   }

   return 0;
}

int main(int argc, char* argv[])
{
   char c, a[LINE];
   memset(a, 0, LINE);
   int nof = 0, err = 0, nofs = 0;
   long long int d = 0, s[LINES];
   memset(s, 0, LINES*sizeof(long long int));


   while ((c = getchar()) != EOF)
   {
      if(err == 0 && c != '\n')
      {
         if (c == ')' ||
             c == ']' ||
             c == '}' ||
             c == '>')
         {
            if(a[nof-1] != c)
            {
               err = 1;

               if (c == ')')
               {
                  d += 3;
               }
               else if (c == '}')
               {
                  d += 1197;
               }
               else if (c == ']')
               {
                  d += 57;
               }
               else if (c == '>')
               {
                  d += 25137;
               }
               else
               {
                  printf("Unexpected character: %d\n", c);
                  return 1;
               }
            }

            nof--;
         }
         else if (c == '(')
         {
            a[nof++] = ')';
         }
         else if (c == '{')
         {
            a[nof++] = '}';
         }
         else if (c == '[')
         {
            a[nof++] = ']';
         }
         else if (c == '<')
         {
            a[nof++] = '>';
         }
         else
         {
            printf("Unexpected character: %d\n", c);
            return 1;
         }
      }
      else
      {
         if(c == '\n')
         {
            if(err == 0)
            {
               for(int i = nof-1; i >= 0; i--)
               {
                  s[nofs] *= 5;
                  if(a[i] == ')')
                  {
                     s[nofs] += 1;
                  }
                  else if(a[i] == ']')
                  {
                     s[nofs] += 2;
                  }
                  else if(a[i] == '}')
                  {
                     s[nofs] += 3;
                  }
                  else if(a[i] == '>')
                  {
                     s[nofs] += 4;
                  }
                  else
                  {
                     printf("Unexpected character: %d\n", a[i]);
                     return 1;
                  }
               }

               nofs++;

            }
            nof = 0;
            memset(a, 0, LINE);
            err = 0;
         }
      }
   }

   printf("%lld\n", d);

   qsort(s, nofs, sizeof(long long int), cmpfunc);

   printf("%lld\n\n\n", s[nofs/2]);

   return 0;
}
