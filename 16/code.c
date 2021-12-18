#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_LEN 7000

typedef long long unsigned llu;

llu bin2int(char* b, int l)
{
   llu  multiplier = 1, bin = 0;

   for (int i = l-1; i >= 0; --i )
   {
      bin += (multiplier * b[i]);
      multiplier *= 2;
   }

   return bin;
}

llu f(char *b, int bits, int packets, int* ix, int *p1, int oper)
{
   int packets_r = 0, start_ix = *ix, val_nof = 0;
   llu *val_buf = NULL, retval = 0, to_r;

   int t, k, g, a;
   char* tmp;

   while(packets_r != packets && (*ix-start_ix) != bits)
   {
      // Version
      *p1 += bin2int(&b[*ix], 3);
      *ix+=3;

      // Type
      t = bin2int(&b[*ix], 3);
      *ix+=3;

      if(t == 4)
      {
         // Litteral
         g = a = 0;
         tmp = NULL;

         // 5-bit chunks as long as first bit == 1
         do
         {
            k = b[*ix];
            *ix+=1;
            g++;

            tmp = (char*) realloc(tmp, g*4);

            for(int i = 0; i < 4; i++)
            {
               tmp[a++] = b[*ix];
               *ix+=1;
            }
         } while(k);

         val_nof++;
         val_buf = (llu *) realloc(val_buf, val_nof*sizeof(llu));
         val_buf[val_nof-1] = bin2int(tmp, g*4);

         free(tmp);
      }
      else
      {
         // Operator
         if(b[*ix])
         {
            // Number of packets in 11 bits
            *ix += 1;
            to_r = bin2int(&b[*ix], 11);
            *ix += 11;

            val_nof++;
            val_buf = (llu *) realloc(val_buf, val_nof*sizeof(llu));
            val_buf[val_nof-1] = f(b, -1, to_r, ix, p1, t);
         }
         else
         {
            // Number of bits in 15 bits
            *ix += 1;
            to_r = bin2int(&b[*ix], 15);
            *ix += 15;

            val_nof++;
            val_buf = (llu *) realloc(val_buf, val_nof*sizeof(llu));
            val_buf[val_nof-1] = f(b, to_r, -1, ix, p1, t);
         }
      }

      packets_r++;
   }

   // Switch over operator passed down from overlaying packet
   switch(oper)
   {
   case 0:
      for(int i = 0; i < val_nof; i++)
      {
         retval += val_buf[i];
      }
      break;

   case 1:
      retval = 1;
      for(int i = 0; i < val_nof; i++)
      {
         retval *= val_buf[i];
      }
      break;

   case 2:
      retval = val_buf[0];
      for(int i = 1; i < val_nof; i++)
      {
         if(val_buf[i] < retval)
         {
            retval = val_buf[i];
         }
      }
      break;

   case 3:
      for(int i = 0; i < val_nof; i++)
      {
         if(val_buf[i] > retval)
         {
            retval = val_buf[i];
         }
      }
      break;

   case 5:
      retval = (val_buf[0] > val_buf[1]);
      break;

   case 6:
      retval = (val_buf[0] < val_buf[1]);
      break;

   case 7:
      retval = (val_buf[0] == val_buf[1]);
      break;
   }

   free(val_buf);

   return retval;
}

int main(int argc, char* argv[])
{
   char c, a, buf[BUF_LEN], *buf_p = buf;

   memset(buf, 0, BUF_LEN);

   while ((c = getchar()) != EOF)
   {
      if(c != '\n')
      {
         if(isalpha(c))
         {
            a = c-'A'+10;
         }
         else
         {
            a = c-'0';
         }

         buf_p += 3;

         for(int i = 3; i >= 0; i--)
         {
            *buf_p-- = a & 1;
            a >>= 1;
         }

         buf_p += 5;
      }
   }

   buf_p = buf;

   int p1 = 0, ix = 0;
   llu p2 = f(buf_p, -1, 1, &ix, &p1, 0);

   printf("%d\n", p1);
   printf("%llu\n", p2);

   return 0;
}
