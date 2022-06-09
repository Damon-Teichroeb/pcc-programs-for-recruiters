/*************************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program06
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     03/21/2019

 DOCUMENTATION
 -------------
   This program provides a menu of calculations to choose from.
 ************************************************************************/
#include <stdio.h>

#define MENU_OPTION_AVERAGE  'd'
#define MENU_OPTION_LARGEST  'b'
#define MENU_OPTION_SMALLEST 'a'
#define MENU_OPTION_SUM      'c'

void  printInstructions ();
void  printMenu         ();
char  getUserMenuChoice ();
void  getUserValues     (int *valueOne, int *valueTwo,
                         int *valueThree, int *valueFour, int *valueFive);
int   findSmallest      (int valueOne, int valueTwo, int valueThree,
                         int valueFour, int valueFive);
int   findLargest       (int valueOne, int valueTwo, int valueThree,
                         int valueFour, int valueFive);
int   calculateSum      (int valueOne, int valueTwo, int valueThree,
                         int valueFour, int valueFive);
float calculateAverage  (int valueOne, int valueTwo, int valueThree,
                         int valueFour, int valueFive);
void  printGoodbye      ();

int main ()
{
   int valueFive,
       valueFour,
       valueOne,
       valueThree,
       valueTwo;

   char letter;

   printInstructions();

   printMenu();

   letter = getUserMenuChoice();

   switch (letter)
   {
      case MENU_OPTION_SMALLEST:
         getUserValues(&valueOne, &valueTwo,
                       &valueThree, &valueFour, &valueFive);
         printf("             The smallest number is: %d\n",
                findSmallest(valueOne, valueTwo, valueThree,
                             valueFour, valueFive));
         printGoodbye();
         break;
      case MENU_OPTION_LARGEST:
         getUserValues(&valueOne, &valueTwo,
                       &valueThree, &valueFour, &valueFive);
         printf("             The largest number is: %d\n",
                findLargest(valueOne, valueTwo, valueThree,
                            valueFour, valueFive));
         printGoodbye();
         break;
      case MENU_OPTION_SUM:
         getUserValues(&valueOne, &valueTwo,
                       &valueThree, &valueFour, &valueFive);
         printf("             The sum of five numbers is: %d\n",
                calculateSum(valueOne, valueTwo, valueThree,
                             valueFour, valueFive));
         printGoodbye();
         break;
      case MENU_OPTION_AVERAGE:
         getUserValues(&valueOne, &valueTwo,
                       &valueThree, &valueFour, &valueFive);
         printf("           The average of five numbers is: %.1f\n",
                calculateAverage(valueOne, valueTwo, valueThree,
                                 valueFour, valueFive));
         printGoodbye();
         break;
      default:
         printf("                         Error\n");
         break;
   }

   return 0;
}

/*************************************************************************
Displays instructions to the user.
*************************************************************************/
void printInstructions()
{
   printf("\n\n\n");
   printf(" This program will perform a calculation of five numbers  \n");
   printf("           based on the choices of the user.              \n");
   printf("\n");

   return;
}

/*************************************************************************
Displays the menu to the user.
*************************************************************************/
void printMenu()
{
   printf("Menu:\n");
   printf("==========================================================\n");
   printf("|     Now choose the type of calculation by typing       |\n");
   printf("|                    in a letter:                        |\n");
   printf("|                                                        |\n");
   printf("|                  Smallest Number = a                   |\n");
   printf("|                   Largest Number = b                   |\n");
   printf("|                   Sum of Numbers = c                   |\n");
   printf("|               Average of Numbers = d                   |\n");
   printf("==========================================================\n");

   return;
}

/*************************************************************************
Recieves a menu choice from the user.
*************************************************************************/
char getUserMenuChoice()
{
   char letter;

   printf("                           ");
   scanf(" %c", &letter);

   return letter;
}

/*************************************************************************
Recieves five numbers from the user.
*************************************************************************/
void getUserValues(int *valueOne, int *valueTwo,
                   int *valueThree, int *valueFour, int *valueFive)
{
   printf("  Please type in five numbers that you want to calculate  \n");
   printf("             (put a space between each number):           \n");
   printf("                       ");
   scanf(" %d %d %d %d %d", valueOne, valueTwo,
         valueThree, valueFour, valueFive);
   printf("\n");

   return;
}

/*************************************************************************
Finds the smallest number.
*************************************************************************/
int findSmallest(int valueOne, int valueTwo, int valueThree,
                 int valueFour, int valueFive)
{
   if (valueOne <= valueTwo && valueOne <= valueThree &&
       valueOne <= valueFour && valueOne <= valueFive)
   {
      return valueOne;
   }
   else if (valueTwo <= valueOne && valueTwo <= valueThree &&
            valueTwo <= valueFour && valueTwo <= valueFive)
   {
      return valueTwo;
   }
   else if (valueThree <= valueOne && valueThree <= valueTwo &&
            valueThree <= valueFour && valueThree <= valueFive)
   {
      return valueThree;
   }
   else if (valueFour <= valueOne && valueFour <= valueTwo &&
            valueFour <= valueThree && valueFour <= valueFive)
   {
      return valueFour;
   }
   else
   {
      return valueFive;
   }
}

/*************************************************************************
Finds the largest number.
*************************************************************************/
int findLargest(int valueOne, int valueTwo, int valueThree,
                int valueFour, int valueFive)
{
   if (valueOne >= valueTwo && valueOne >= valueThree &&
       valueOne >= valueFour && valueOne >= valueFive)
   {
      return valueOne;
   }
   else if (valueTwo >= valueOne && valueTwo >= valueThree &&
            valueTwo >= valueFour && valueTwo >= valueFive)
   {
      return valueTwo;
   }
   else if (valueThree >= valueOne && valueThree >= valueTwo &&
            valueThree >= valueFour && valueThree >= valueFive)
   {
      return valueThree;
   }
   else if (valueFour >= valueOne && valueFour >= valueTwo &&
            valueFour >= valueThree && valueFour >= valueFive)
   {
      return valueFour;
   }
   else
   {
      return valueFive;
   }
}

/*************************************************************************
Calculates the sum of all the numbers.
*************************************************************************/
int calculateSum(int valueOne, int valueTwo, int valueThree,
                 int valueFour, int valueFive)
{
   return (valueOne + valueTwo + valueThree
           + valueFour + valueFive);
}

/*************************************************************************
Calculates the average from all the numbers.
*************************************************************************/
float calculateAverage(int valueOne, int valueTwo, int valueThree,
                       int valueFour, int valueFive)
{
   return (valueOne + valueTwo + valueThree
           + valueFour + valueFive) / 5.0f;
}

/*************************************************************************
Displays the final message.
*************************************************************************/
void printGoodbye()
{
   printf("             Thank you for using my program.              \n");
   printf("                     Have a nice day!                     \n");

   return;
}
