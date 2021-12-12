#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 150

int main(int argc, char* argv[])
{
   int x = 0;
   char line[MAX_LINE], *next_row;
   for (next_row = fgets(line, MAX_LINE, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE, stdin))
   {
      for(char* tok = strtok(line, "|"); tok != NULL; tok = strtok(NULL, "| \n"))
      {
         if(strlen(tok) == 2 ||
            strlen(tok) == 4 ||
            strlen(tok) == 3 ||
            strlen(tok) == 7)
         {
            x++;
         }
      }
   }

   printf("%d\n", x);


   return 0;
}
