/*************************************************************************
 CLASS INFORMATION                                    
 -----------------                                    
   Program Name: program02
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     02/14/2019

 DOCUMENTATION
 -------------
   This program displays 3 numbers typed in by the user.
 ************************************************************************/
#include <stdio.h>

int main()
{
   float num1,
         num2,
         num3;

   printf("Please enter three numbers: ");

   scanf("%f %f %f", &num1, &num2, &num3);

   printf(" --------\n");
   printf("|Forward |\n");
   printf(" --------\n");
   printf("|%08.4f|\n", num1);
   printf("|%08.4f|\n", num2);
   printf("|%08.4f|\n", num3);
   printf(" --------\n\n");

   printf(" --------\n");
   printf("|Reversed|\n");
   printf(" --------\n");
   printf("|%08.4f|\n", num3);
   printf("|%08.4f|\n", num2);
   printf("|%08.4f|\n", num1);
   printf(" --------\n");

   return 0;
}
