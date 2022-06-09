/*************************************************************************
 CLASS INFORMATION                                    
 -----------------                                    
   Program Name: program03
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     02/22/2019

 DOCUMENTATION
 -------------
   This program converts from inches to feet.
 ************************************************************************/
#include <stdio.h>

int main()
{
   float feet,
         inches;

   printf("This program will convert inches that you type in to feet\n\n");

   printf("Please type in your inches:\n");
   scanf("%f", &inches);
   feet = inches / 12;

   printf("Your result is: %.4f ", feet);
   printf("feet\n");

   return 0;
}
