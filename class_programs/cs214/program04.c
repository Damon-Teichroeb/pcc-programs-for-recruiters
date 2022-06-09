/*************************************************************************
 CLASS INFORMATION                                    
 -----------------                                    
   Program Name: program04
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     02/28/2019

 DOCUMENTATION
 -------------
   This program converts inches to centimeters.
 ************************************************************************/
#include <stdio.h>

float convertInches(float inches);

int main()
{
   float inches;

   printf("\nThis program will convert inches into centimeters.\n\n");

   printf("Please type in your inches:\n");
   scanf("%f", &inches);

   printf("\nYour input was: %.4f ", inches);
   printf("inches\n");

   printf("Your result is: %.4f ", convertInches(inches));
   printf("centimeters\n\n");

   return 0;
}

float convertInches(float inches)
{
   return (inches * 2.54f);
}
