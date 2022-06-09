/**********************************************************************/
/*                                                                    */
/* Program Name: program2 - Loop Processing Until The User Quits      */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: September 19, 2019                                   */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/* I pledge this assignment is my own first time work.                */
/* I pledge I did not copy or try to copy any work from the Internet. */
/* I pledge the only person I asked for help from was my teacher.     */
/* I pledge I did not attempt to help any student on this assignment. */
/* I understand if I violate this pledge I will receive a 0 grade.    */
/*                                                                    */
/*                                                                    */
/*                      Signed: _____________________________________ */
/*                                           (signature)              */
/*                                                                    */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/* This program displays a menu with 5 choices to choose from. Once   */
/* the user selects a menu choice the program will perform the        */
/* operation selected. Once the operation is finished the menu        */
/* will be displayed again until the user decides to quit the program.*/
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define MAX_CHOICE_NUM  5        /* Highest menu choice number        */
#define MIN_CHOICE_NUM  1        /* Lowest menu choice number         */
#define MENU_CHOICE_ERR 1        /* Check for error                   */
#define QUIT            MAX_CHOICE_NUM
                                 /* End the program                   */
#define COURSE_NUMBER   "CS227"  /* PCC assigned course number        */
#define PROGRAM_NUMBER  2        /* Teacher assigned program number   */
#define PROGRAMMER_NAME "Teichroeb"
                                 /* The programmer's last name        */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
int   add_whole_numbers(int first_number, int second_number);
   /* Add two whole numbers                                           */
void  are_in_order(int *p_first_number, int *p_second_number);
   /* Swap the order of two whole numbers                             */
int   get_menu_choice();
   /* Get the menu choice                                             */
int   get_range_sum(int range_start, int range_end);
   /* Get the inclusive sum of whole numbers                          */
void  get_whole_numbers(int *p_first_number, int *p_second_number);
   /* Get two whole numbers                                           */
void  print_heading();
   /* Print the program heading                                       */
void  print_menu();
   /* Display the menu choices                                        */
float raise_power_of_number(float first_number, float second_number);
   /* Raise the power of the first number to the second number        */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int first_number,  /* First whole number                           */
       menu_choice,
       second_number; /* Second whole number                          */

   /* Print the program heading                                       */
   printf("\n\n\n\n\n\n");
   print_heading();

   /* Loop processing pairs of whole numbers until the user quits     */
   while(print_menu(), (menu_choice = get_menu_choice()) != QUIT)
   {
      /* Get two whole numbers                                        */
      get_whole_numbers(&first_number, &second_number);

      switch(menu_choice)
      {
         /* Add two whole numbers                                     */
         case 1:
            printf("The sum of %d and %d is: %d",
               first_number, second_number, add_whole_numbers
               (first_number, second_number));
            break;
         /* Raise a whole number to the power of another              */
         case 2:
            printf("%d raised to the power of %d = %e",
               first_number, second_number, raise_power_of_number
               (first_number, second_number));
            break;
         /* Get the whole number range sum                            */
         case 3:
            if(first_number > second_number)
               are_in_order(&first_number, &second_number);
            printf("The sum of the numbers between %d and %d ",
               first_number, second_number);
            printf("(inclusively) is: %d", get_range_sum
               (first_number, second_number));
            break;
         /* Put two whole numbers is ascending order                  */
         case 4:
            if(first_number > second_number)
            {
               printf("%d and %d properly ordered ",
                  first_number, second_number);
               are_in_order(&first_number, &second_number);
               printf("are: %d and %d", first_number, second_number);
            }
            else
            {
               printf("%d and %d are already in order",
                  first_number, second_number);
            }
            break;
         /* Display error message and exit the program                */
         default:
            printf("\n   Error #1 occurred in main()");
            printf("\n      Incorrect menu choice");
            printf("\n     The program is aborting");
            exit(MENU_CHOICE_ERR);
      }
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for processing numbers.  Have a nice day! ;-)");
   printf("\n\n\n\n\n\n");
   return 0;
}

/**********************************************************************/
/*                     Print the program heading                      */
/**********************************************************************/
void print_heading()
{
   printf(  "\n======================================================");
   printf(  "\n            Program Number:    %d", PROGRAM_NUMBER);
   printf(  "\n            Programmer:        %s", PROGRAMMER_NAME);
   printf(  "\n            PCC Course Number: %s", COURSE_NUMBER);
   printf(  "\n======================================================");
   printf(  "\n   Miscellaneous operations on your two whole numbers");
   return;
}

/**********************************************************************/
/*                     Display the menu choices                       */
/**********************************************************************/
void print_menu()
{
   printf("\n\nMake a selection from the following menu:");
   printf(  "\n-----------------------------------------");
   printf(  "\n    1 - Add two whole numbers");
   printf(  "\n    2 - Raise the 1st number to the power of the 2nd");
   printf(  "\n    3 - Sum all numbers between two whole numbers");
   printf(  "\n    4 - Put two whole numbers into ascending order");
   printf(  "\n    5 - Quit");
   return;
}

/**********************************************************************/
/*                        Get the menu choice                         */
/**********************************************************************/
int get_menu_choice()
{
   int menu_choice;

   printf("\n");
   do
   {
      printf("Enter your menu selection (1-5): ");
      scanf (" %d", &menu_choice);
   }
   while(menu_choice < MIN_CHOICE_NUM || menu_choice > MAX_CHOICE_NUM);
   return menu_choice;
}

/**********************************************************************/
/*                       Get two whole numbers                        */
/**********************************************************************/
void get_whole_numbers(int *p_first_number, int *p_second_number)
{
   printf("\nType in any two whole numbers now:");
   printf("\n   Give me your first number:  ");
   scanf (" %d", p_first_number);
   printf(  "   Give me your second number: ");
   scanf (" %d", p_second_number);
   return;
}

/**********************************************************************/
/*                    Get the sum of whole numbers                    */
/**********************************************************************/
int add_whole_numbers(int first_number, int second_number)
{
   return first_number + second_number;
}

/**********************************************************************/
/*     Raise the power of the first number to the second number       */
/**********************************************************************/
float raise_power_of_number(float first_number, float second_number)
{
   return (float) pow((float) first_number, (float) second_number);
}

/**********************************************************************/
/*                Get the range sum of whole numbers                  */
/**********************************************************************/
int get_range_sum(int range_start, int range_end)
{
   int range_counter,  /* Count each loop iteration                   */
       range_sum = 0;  /* Sum the whole number range                  */

   for(range_counter = range_start; range_counter <= range_end;
                                                        range_counter++)
      range_sum += range_counter;
   return range_sum;
}

/**********************************************************************/
/*             Swap the order of the two whole numbers                */
/**********************************************************************/
void are_in_order(int *p_first_number, int *p_second_number)
{
   int temporary_number; /* Holds the first whole number              */

   temporary_number = *p_first_number;
   *p_first_number = *p_second_number;
   *p_second_number = temporary_number;
   return;
}
