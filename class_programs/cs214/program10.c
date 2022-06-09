/********************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program10
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     04/18/2019

 DOCUMENTATION
 -------------
   This program will test an ISBN number to see if it is valid
   or invalid.
 *******************************************************************/
#include <stdio.h>
#include <stdbool.h>

#define ISBN_SIZE 10

void printInstructions();
void getIsbn(int isbnArray[]);
void printIsbn(int isbnArray[]);
int  calculateWeightedSum(int isbnArray[]);
bool isIsbnValid(int value);
void printGoodbye();

int main()
{
   int isbnArray[ISBN_SIZE] = {0};

   printInstructions();
   getIsbn(isbnArray);

   printf("\n\nThe ISBN ");
   printIsbn(isbnArray);

   if(isIsbnValid(calculateWeightedSum(isbnArray)))
   {
      printf(" is valid.");
   }
   else
   {
      printf(" is not valid.");
   }

   printGoodbye();

   return 0;
}

/********************************************************************
   Displays instructions to the user.
********************************************************************/
void printInstructions()
{
   printf("\nThis program will test an ISBN number to see ");
   printf("if it is a valid or invalid number.\n\n\n");

   return;
}

/********************************************************************
   Recieves digit values from the user.
********************************************************************/
void getIsbn(int isbnArray[])
{
   int counter;

   for(counter = 0; counter < ISBN_SIZE; counter++)
   {
      printf("Please type in ISBN digit #%d: ", counter + 1);
      scanf(" %d", &isbnArray[counter]);

      while (isbnArray[counter] < 0 || isbnArray[counter] > 9)
      {
         printf("Please type in a single digit (0-9): ");
         scanf(" %d", &isbnArray[counter]);
      }
   }

   return;
}

/********************************************************************
   Displays digit values.
********************************************************************/
void printIsbn(int isbnArray[])
{
   int counter;

   for(counter = 0; counter < ISBN_SIZE; counter++)
   {
      if(counter == 1 || counter == 3 || counter == 9)
      {
         printf("-%d", isbnArray[counter]);
      }
      else
      {
         printf("%d", isbnArray[counter]);
      }
   }

   return;
}

/********************************************************************
   Calculates the weighted sum of the values.
********************************************************************/
int calculateWeightedSum(int isbnArray[])
{
   int counter,
       weightedSum = 0;

   for(counter = ISBN_SIZE - 1; counter >= 0; counter--)
   {
      weightedSum += isbnArray[counter] * (counter + 1);
   }

   return weightedSum;
}

/********************************************************************
   Tests the value to see if it is valid or invalid.
********************************************************************/
bool isIsbnValid(int value)
{
   value = value % 11;

   return !value;
}

/********************************************************************
   Displays a goodbye message.
********************************************************************/
void printGoodbye()
{
   printf("\n\nThank you for using my program! \n");
   printf("Have a nice day!                    \n");

   return;
}
