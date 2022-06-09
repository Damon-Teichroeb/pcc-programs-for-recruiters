#include <stdio.h>

int main()
{
   int number,
       sum = 0;

   printf("The first 10 natural numbers are:\n");

   for (number = 1; number <= 10; number++)
   {
      sum += number;
      printf("%d ", number);
   }

   printf("\n");
   printf("The Sum is: %d", sum);
   printf("\n");
   return 0;
}
