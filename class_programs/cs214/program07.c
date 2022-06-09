/*************************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program07
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     03/28/2019

 DOCUMENTATION
 -------------
   This program calculates the accuracy of pi based on the
   input of the user.
 ************************************************************************/
#include <stdio.h>
#include <math.h>

#define QUIT 99999

void printInstructions();
int  getUserValue();
void printResults(int limit, double piValue);
void printGoodbye();

int main()
{
   int    counter,
          userLimit;
   double pi;

   do
   {
      printInstructions();

      userLimit = getUserValue();
      if (userLimit == QUIT)
      {
         continue;
      }

      pi = 0.0;
      for (counter = 1; counter <= userLimit; counter++)
      {
         pi += 1.0 / pow(counter, 2.0);
      }

      printResults(userLimit, (sqrt(6.0 * pi)));
   }
   while (userLimit != QUIT);

   printGoodbye();
   return 0;
}

/***********************************************************************
  Displays the program instructions to the user.
 ***********************************************************************/
void printInstructions()
{
   printf("\nEnter a limit to use for a calculation of PI. ");
   printf("(%d to stop)\n> ", QUIT);

   return;
}

/***********************************************************************
  Gets one integer value from the user.
 ***********************************************************************/
int getUserValue()
{
   int value;

   scanf(" %d", &value);

   return value;
}

/***********************************************************************
  Displays a summary of result.
 ***********************************************************************/
void printResults(int limit, double piValue)
{
   printf("\n\nThe value of PI up to the limit of %d is %.15f", limit,
      piValue);

   return;
}

/***********************************************************************
  Prints a goodbye message.
 ***********************************************************************/
void printGoodbye()
{
   printf("\n\nThanks for using this program!");
   printf("\nHave a good day!\n\n");

   return;
}
