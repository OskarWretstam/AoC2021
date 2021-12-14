#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 50
#define MAX_BINS 150

typedef struct
{
   char key[2];
   char add;
   long long int cnt;
   int map_to[2];
} b_t;


int main(int argc, char* argv[])
{
   int f = 1;

   b_t b[MAX_BINS];
   b_t bb[MAX_BINS];

   int nof = 0;

   // Intialise stucture with keys (character pairs) and what they create (new char)
   char line[LINE], *next_row, start[LINE], *tokk;
   for (next_row = fgets(line, LINE, stdin); next_row!=NULL; next_row=fgets(line, LINE, stdin))
   {
      if(f)
      {
         strcpy(start, line);
         f = 0;
      }
      else
      {
         for(char* tok = strtok(line, " ->\n"); tok != NULL; tok = strtok(NULL, " ->\n"))
         {
            tokk = strtok(NULL, " ->\n");

            memcpy(b[nof].key, tok, 2);
            b[nof].cnt = 0;
            b[nof].add = tokk[0];
            nof++;
         }
      }
   }


   // Find mapping indicies, adding the char will create a new and existing pair
   int mapped;
   char tmp1[2], tmp2[2];

   for(int i = 0; i < nof; i++)
   {
      mapped = 0;

      for(int j = 0; j < nof; j++)
      {
         tmp1[0] = b[i].key[0];
         tmp1[1] = b[i].add;

         tmp2[0] = b[i].add;
         tmp2[1] = b[i].key[1];

         if(strncmp(tmp1, b[j].key, 2) == 0 ||
            strncmp(tmp2, b[j].key, 2) == 0)
         {
            b[i].map_to[mapped++] = j;
         }

         if(mapped == 2)
         {
            break;
         }
      }
   }

   // Setup the working copy, does not not to be a complete struct array but did not bother in the end
   memset(bb, 0, MAX_BINS*sizeof(b_t));
   memcpy(bb, b, MAX_BINS*sizeof(b_t));

   // Bins for counting added characters
   long long int bbb['Z'-'A'+1];
   long long int bbb1['Z'-'A'+1];
   memset(bbb, 0, ('Z'-'A'+1)*sizeof(long long int));

   // Input start line, both to structure array and character bins
   int ix = 0;
   while(start[ix+1] != '\n')
   {
      bbb[start[ix]-'A']++;
      tmp1[0] = start[ix];
      tmp1[1] = start[ix+1];

      for(int i = 0; i < nof; i++)
      {
         if(strncmp(tmp1, b[i].key, 2) == 0)
         {
            b[i].cnt++;
         }
      }
      ix++;
   }
   bbb[start[ix]-'A']++;

   // Iterate steps
   for(int i = 0; i < 40; i++)
   {
      for(int j = 0; j < nof; j++)
      {
         if(b[j].cnt)
         {
            bb[b[j].map_to[0]].cnt += b[j].cnt;
            bb[b[j].map_to[1]].cnt += b[j].cnt;
            bbb[b[j].add-'A'] += b[j].cnt;

            b[j].cnt = 0;
         }
      }

      for(int j = 0; j < nof; j++)
      {
         b[j].cnt = bb[j].cnt;
         bb[j].cnt = 0;
      }

      // Just store state for part 1
      if(i == 9)
      {
         memcpy(bbb1, bbb, ('Z'-'A'+1)*sizeof(long long int));
      }
   }

   // Find min max
   long long int min = 100000000000000, max = 0, min1 = 100000000000000, max1 = 0;
   for(int i = 0; i <= 'Z'-'A'; i++)
   {
      if(bbb[i] && bbb[i] < min)
      {
         min = bbb[i];
      }

      if(bbb1[i] && bbb1[i] < min1)
      {
         min1 = bbb1[i];
      }

      if(bbb[i] > max)
      {
         max = bbb[i];
      }

      if(bbb1[i] > max1)
      {
         max1 = bbb1[i];
      }
   }

   printf("%lld\n", max1-min1);
   printf("%lld\n", max-min);

   return 0;
}
