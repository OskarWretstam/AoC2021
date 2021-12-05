#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 20
#define LINES 1000
#define CHARS 12

int main(int argc, char *argv[])
{
   int nof_lines = 0;
   int nof_elem = 0;
   int sum_of_column[CHARS];
   char dat[LINES*CHARS];
   memset(sum_of_column, 0, CHARS*sizeof(int));

   char line[MAX_LINE_LENGTH], *next_row;
	for (next_row = fgets(line, MAX_LINE_LENGTH, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE_LENGTH, stdin))
   {
      strncpy(&dat[nof_lines*CHARS], line, CHARS);
      nof_lines++;
      for(int i = 0; i < CHARS; i++)
      {
         if(line[i] == '1')
         {
            sum_of_column[i]++;
         }
      }
   }

   // Printout binary first numbers
   for(int i = 0; i < CHARS; i++)
   {
      if(sum_of_column[i] > (nof_lines/2))
      {
         printf("1");
      }
      else
      {
         printf("0");
      }
   }
   printf("\n");

   for(int i = 0; i < CHARS; i++)
   {
      if(sum_of_column[i] > (nof_lines/2))
      {
         printf("0");
      }
      else
      {
         printf("1");
      }
   }
   printf("\n");


   int remaining_lines[LINES];
   for(int i = 0; i < LINES; i++)
   {
      remaining_lines[i] = 1;
   }
   int nof_remaining_lines = LINES;
   int column_sum;
   int column_pos = 0;
   int to_keep;

   while(nof_remaining_lines > 1)
   {
      column_sum = 0;
      to_keep = 0;

      for(int i = 0; i < LINES; i++)
      {
         if(remaining_lines[i] == 1)
         {
            column_sum += dat[CHARS*i + column_pos] - 48;
         }
      }

      if(column_sum*2 >= nof_remaining_lines)
      {
         to_keep = 1;
      }

      for(int i = 0; i < LINES; i++)
      {
         if(remaining_lines[i] == 1)
         {
            if(dat[CHARS*i + column_pos] - 48 != to_keep)
            {
               remaining_lines[i] = 0;
               nof_remaining_lines--;
            }
         }
      }

      column_pos++;
   }

   for(int i = 0; i < LINES; i++)
   {
      if(remaining_lines[i] == 1)
      {
         for(int j = 0; j < CHARS; j++)
         {
            printf("%c", dat[CHARS*i + j]);
         }
         printf("\n");
      }
   }

   for(int i = 0; i < LINES; i++)
   {
      remaining_lines[i] = 1;
   }
   nof_remaining_lines = LINES;
   column_pos = 0;

   while(nof_remaining_lines > 1)
   {
      column_sum = 0;
      to_keep = 1;

      for(int i = 0; i < LINES; i++)
      {
         if(remaining_lines[i] == 1)
         {
            column_sum += (dat[CHARS*i + column_pos] - 48);
         }
      }

      if(column_sum*2 >= nof_remaining_lines)
      {
         to_keep = 0;
      }

      for(int i = 0; i < LINES; i++)
      {
         if(remaining_lines[i] == 1)
         {
            if(dat[CHARS*i + column_pos] - 48 != to_keep)
            {
               remaining_lines[i] = 0;
               nof_remaining_lines--;
            }
         }
      }

      column_pos++;
   }

   for(int i = 0; i < LINES; i++)
   {
      if(remaining_lines[i] == 1)
      {
         for(int j = 0; j < CHARS; j++)
         {
            printf("%c", dat[CHARS*i + j]);
         }
         printf("\n");
      }
   }

   return 0;
}
