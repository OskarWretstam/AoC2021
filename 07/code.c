#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE 5000

int main(int argc, char* argv[])
{
   int x[MAX_LINE];
   int nofx = 0;

   char line[MAX_LINE], *next_row;
   for (next_row = fgets(line, MAX_LINE, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE, stdin))
   {
      for(char* tok = strtok(line, ",\n"); tok != NULL; tok = strtok(NULL, ",\n"))
      {
         sscanf(tok, "%d", &x[nofx]);
         nofx++;
      }
   }


   int i = -10000;
   long long unsigned min = 1000000000;
   long long unsigned cost = 0;
   long long unsigned accum_cost = 0;

   while(i < 10000)
   {
      int sum = 0;
      for(int i = 0; i < nofx; i++)
      {
         sum += x[i];
      }
      double mean = sum/((double)nofx);
      long long int mean_int = round(mean)+i;
      printf("T: %llu ", mean_int);

      cost = 0;
      for(int i = 0; i < nofx; i++)
      {
         accum_cost = 1;
         for(int j = 0; j < abs(x[i]-mean_int); j++)
         {
            cost += accum_cost;
            accum_cost += 1;
         }
      }
      printf("C: %llu\n", cost);

      if(cost < min)
      {
         min = cost;
      }
      i++;
   }

   printf("%llu\n", min);


   return 0;
}
