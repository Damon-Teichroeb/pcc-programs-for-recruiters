/**********************************************************************/
/*                                                                    */
/* Program Name: program5 - Process The Sum of an Even Numbers Range  */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: October 31, 2019                                     */
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
/* This program calculates the sum of the even numbers in a range.    */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <ctype.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/

#define MINIMUM_RANGE   -5000   /* Smallest number                    */
#define MAXIMUM_RANGE   5000    /* Largest number                     */
#define COURSE_NUMBER   "CS227" /* PCC assigned course number         */
#define PROGRAM_NUMBER  5       /* Teacher assigned program number    */
#define PROGRAMMER_NAME "Teichroeb"
                                /* The programmer's last name         */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the heading                                               */
void print_instructions();
   /* Print the instructions                                          */
char get_response();
   /* Get the response                                                */
void get_range(int *p_first_number, int *p_second_number);
   /* Get the range                                                   */
void swap_numbers(int *p_first_number, int *p_second_number);
   /* Swap two whole numbers                                          */
int is_even(int first_number);
   /* Check for even numbers                                          */
int sum_even_range(int first_number, int second_number);
   /* Recursively calculate the sum of even numbers                   */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int first_number,  /* First whole number                           */
       second_number; /* Second whole number                          */

   /* Print the heading and instructions                              */
   printf("\n\n\n\n\n\n");
   print_heading();
   print_instructions();

   /* Process the calculation of the sum of an even numbers range     */
   while(get_response() == 'y')
   {
      /* Get the whole number range                                   */
      get_range(&first_number, &second_number);
      if(first_number > second_number)
         swap_numbers(&first_number, &second_number);

      /* Calculate and print the sum of the even numbers range        */
      printf("\nProcessing the range %d to %d:", first_number,
                                                         second_number);
      printf("\nThe sum of all even numbers in the range %d to %d is: %d",
         first_number, second_number,
         sum_even_range(first_number, second_number));
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for \"even summing\".  Have a nice day! ;-)");
   printf("\n\n\n\n\n\n");
   return 0;
}

/**********************************************************************/
/*                        Print the heading                           */
/**********************************************************************/
void print_heading()
{
   printf(  "\n======================================================");
   printf(  "\n              Program Number:    %d", PROGRAM_NUMBER);
   printf(  "\n              Programmer:        %s", PROGRAMMER_NAME);
   printf(  "\n              PCC Course Number: %s", COURSE_NUMBER);
   printf(  "\n======================================================");
   return;
}

/**********************************************************************/
/*                      Print the instructions                        */
/**********************************************************************/
void print_instructions()
{
   printf("\nThis program recursively calculates the sum of all");
   printf("\neven whole numbers between two numbers inclusively.");
   printf("\nYou are repeatedly asked to enter in the start and");
   printf("\nend of a range, and the sum of all even numbers in");
   printf("\nthat range is calculated and printed.  Information");
   printf("\nabout the recursive action of the function is also");
   printf("\nprinted so the recursive nature of the calculation");
   printf("\n                 may be observed.");
   return;
}

/**********************************************************************/
/*                         Get the response                           */
/**********************************************************************/
char get_response()
{
   char letter[2]; /* A single letter response                        */

   printf("\n");
   do
   {
      printf("\nDo you want to process another range (y or n): ");
      scanf(" %1s", letter);
   }
   while (tolower(letter[0]) != 'y' && tolower(letter[0]) != 'n');
   return tolower(letter[0]);
}

/**********************************************************************/
/*                    Get the whole number range                      */
/**********************************************************************/
void get_range(int *p_first_number, int *p_second_number)
{
   printf("\n");
   do
   {
      printf("Enter in the first number (from %d to %d): ",
         MINIMUM_RANGE, MAXIMUM_RANGE);
      scanf(" %d", p_first_number);
   }
   while(*p_first_number < MINIMUM_RANGE ||
         *p_first_number > MAXIMUM_RANGE);
   printf("\n");
   do
   {
      printf("Enter in the last number  (from %d to %d): ",
         MINIMUM_RANGE, MAXIMUM_RANGE);
      scanf(" %d", p_second_number);
   }
   while(*p_second_number < MINIMUM_RANGE ||
         *p_second_number > MAXIMUM_RANGE);
   return;
}

/**********************************************************************/
/*                      Swap two whole numbers                        */
/**********************************************************************/
void swap_numbers(int *p_first_number, int *p_second_number)
{
   printf("\nSwapping %d and %d ", *p_first_number, *p_second_number);
   *p_first_number += *p_second_number;
   *p_second_number = *p_first_number - *p_second_number;
   *p_first_number -= *p_second_number;
   return;
}

/**********************************************************************/
/*                      Check for even numbers                        */
/**********************************************************************/
int is_even(int first_number)
{
   return first_number % 2 == 0;
}

/**********************************************************************/
/*                 Recursively calculate the even sum                 */
/**********************************************************************/
int sum_even_range(int first_number, int second_number)
{
   int even_sum = 0; /* The sum of even numbers                       */

   if(first_number > (second_number + 1))
      return 0;
   printf("\n   Entering sum function for range %d to %d",
      first_number, second_number);
   if(is_even(first_number) && first_number <= second_number)
   {
      printf("\n      Adding: %d", first_number);
      even_sum = first_number + sum_even_range(first_number + 1,
                                                         second_number);
   }
   if(!is_even(first_number) && first_number <= second_number)
   {
      printf("\n      Skipping: %d", first_number);
      even_sum = sum_even_range(first_number + 1, second_number);
   }
   printf("\n   Exiting sum function for range %d to %d with result %d",
      first_number, second_number, even_sum);
   return even_sum;
}
