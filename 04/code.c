#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDE 5
#define TALL 5
#define MAX_LINE 512

typedef struct
{
   int no;
   int marked;
} square_t;

int sum_unmarked(square_t* data)
{
   int sum = 0;
   for(int i = 0; i < WIDE; i++)
   {
      for(int j = 0; j < TALL; j++)
      {
         if(data[i*WIDE + j].marked == 0)
         {
            sum += data[i*WIDE + j].no;
         }
      }
   }

   return sum;
}

int is_winner(square_t* data)
{
   // Check all rows + columns because hungover
   for(int i = 0; i < WIDE; i++)
   {
      for(int j = 0; j < TALL; j++)
      {
         if(data[i*WIDE + j].marked == 0)
         {
            break;
         }

         if(j == TALL - 1)
         {
            return 1;
         }
      }

      for(int j = 0; j < TALL; j++)
      {
         if(data[j*WIDE + i].marked == 0)
         {
            break;
         }

         if(j == TALL - 1)
         {
            return 1;
         }
      }
   }

   return 0;
}

int main(int argc, int *argv[])
{
   int nof_boards = 0, buf_boards = 0, nof_board_elements = 0;
   square_t* boards = NULL;
   int to_draw[256], no_to_draw = 0;

   char line[MAX_LINE], *next_row;
   fgets(line, MAX_LINE, stdin);
   for(char* tok = strtok(line, ","); tok != NULL; tok = strtok(NULL, ","))
   {
      sscanf(tok, "%d", &to_draw[no_to_draw]);
      no_to_draw++;
   }

   for (next_row = fgets(line, MAX_LINE, stdin); next_row!=NULL; next_row=fgets(line, MAX_LINE, stdin))
   {
      if(line[0] == '\n')
      {
         nof_boards++;
      }
      else
      {
         if(nof_boards > buf_boards)
         {
            boards = realloc(boards, nof_boards*WIDE*TALL*sizeof(square_t));
            if(boards == NULL)
            {
               printf("Error: failed to allocate more memory\n");
               return 1;
            }
         }

         for(char* tok = strtok(line, " "); tok != NULL; tok = strtok(NULL, " "))
         {
            sscanf(tok, "%d", &boards[nof_board_elements].no);
            boards[nof_board_elements].marked = 0;
            nof_board_elements++;
         }
      }
   }

   int *winners = malloc(nof_boards*sizeof(int));
   int sum_winners;

   if(winners == NULL)
   {
      printf("Error\n");
      return 1;
   }

   for(int i = 0; i < no_to_draw; i++)
   {
      for(int j = 0; j < nof_boards; j++)
      {
         for(int k = 0; k < TALL; k++)
         {
            for(int l = 0; l < WIDE; l++)
            {
               if(boards[(j*WIDE*TALL) + k*WIDE + l].no == to_draw[i])
               {
                  boards[(j*WIDE*TALL) + k*WIDE + l].marked = 1;
                  if(is_winner(&boards[j*WIDE*TALL]))
                  {
                     winners[j] = 1;
                     sum_winners = 0;
                     for(int m = 0; m < nof_boards; m++)
                     {
                        sum_winners += winners[m];
                     }

                     if(sum_winners == 1 || sum_winners == 100)
                     {
                        printf("Winner %d is board: %d score: %d\n", sum_winners, j, to_draw[i]*sum_unmarked(&boards[j*WIDE*TALL]));
                     }

                     if(sum_winners == nof_boards)
                     {
                        return 0;
                     }
                  }
               }
            }
         }
      }
   }

   return 1;
}
