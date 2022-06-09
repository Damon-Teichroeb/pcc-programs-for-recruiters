/**********************************************************************/
/*                                                                    */
/* Program Name: program1 - The Sum of Numbers Within a Number Range  */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: September 5, 2019                                    */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/* This program asks the user for a small number and a big number to  */
/* create a range and then calculates the inclusive sum of the range. */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define COURSE_NUMBER   "CS227"  /* PCC assigned course number        */
#define PROGRAM_NUMBER  1        /* Teacher assigned program number   */
#define PROGRAMMER_NAME "teichroeb"
                                 /* The programmer's name             */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the program heading                                       */
void get_range(int *p_minimum_range, int *p_maximum_range);
   /* Get a small and a big number from the user                      */
int get_range_sum(int *p_minimum_range, int *p_maximum_range);
   /* Get the inclusive sum of all numbers within the range           */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int minimum_range, /* Store the small number of the range          */
       maximum_range; /* Store the big number of the range            */

   /* Print the program heading                                       */
   printf("\n\n\n\n\n\n\n");
   print_heading();

   /* Get the range from the user                                     */
   get_range(&minimum_range, &maximum_range);

   /* Get the inlcusive sum of the range and print the sum            */
   printf("\nThe sum of all numbers in the range (inclusively) is: %d",
          get_range_sum(&minimum_range, &maximum_range));

   /* Say good-bye and terminate the program                          */
   printf("\n\nGood-bye and Thank you for using my program!");
   printf("\nHave a nice day! :D");
   printf("\n\n\n\n\n\n\n");

   return 0;
}

/**********************************************************************/
/*                     Print the program heading                      */
/**********************************************************************/
void print_heading()
{
   printf("\n========================================================");
   printf("\n              Program Number:    %d", PROGRAM_NUMBER);
   printf("\n              Programmer:        %s", PROGRAMMER_NAME);
   printf("\n              PCC Course Number: %s", COURSE_NUMBER);
   printf("\n========================================================");
   printf("\nThis program will sum all whole numbers (inclusively) in");
   printf("\n                   a number range.");
   printf("\n--------------------------------------------------------");

   return;
}

/**********************************************************************/
/*                    Get the range from the user                     */
/**********************************************************************/
void get_range(int *p_minimum_range, int *p_maximum_range)
{
   printf("\nEnter a range of whole numbers now, lower number first:");

   printf("\n  What is your small number: ");
   scanf(" %d", p_minimum_range);
   printf("  Give me your large number: ");
   scanf(" %d", p_maximum_range);

   return;
}

/**********************************************************************/
/*                     Get the sum of the ranges                      */
/**********************************************************************/
int get_range_sum(int *p_minimum_range, int *p_maximum_range)
{
   int loop_counter,  /* Count each loop iteration                    */
       sum = 0;       /* Store the sum of the range                   */

   for(loop_counter = *p_minimum_range;
       loop_counter <= *p_maximum_range;
       loop_counter++)
   {
      sum += loop_counter;
   }

   return sum;
}
