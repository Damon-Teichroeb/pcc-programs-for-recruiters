/**********************************************************************/
/*                                                                    */
/* Program Name: program3 - Processing Experimental Scientific Data   */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: October 3, 2019                                      */
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
/* The user selects the quantity of experimental scientific data and  */
/* then gives every experimental scientific data value. Each value is */
/*   sorted, summed, and displayed to the user. This process loops    */
/*                 until the user quits the program.                  */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define MINIMUM_QUANTITY 2       /* Smallest amount of data           */
#define MAXIMUM_QUANTITY 100     /* Biggest amount of data            */
#define MEM_ALLOC_ERR    1       /* Can't allocate memory error       */
#define SORT_ALLOC_ERR   2       /* Can't sort allocated memory error */
#define QUIT             0       /* Program exit value                */
#define COURSE_NUMBER    "CS227" /* PCC assigned course number        */
#define PROGRAM_NUMBER   3       /* Teacher assigned program number   */
#define PROGRAMMER_NAME  "Teichroeb"
                                 /* The programmer's last name        */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the heading                                               */
void print_instructions();
   /* Print the instructions                                          */
int get_quantity();
   /* Get the amount of experimental scientific data values           */
void get_data_values(float *p_data_start, float *p_data, int quantity);
   /* Get experimental scientific data values                         */
void sort_into_descending(float *p_data_start, float *p_sort_start,
                            float *p_data, float *p_sort, int quantity);
   /* Sort experimental scientific data values into descending order  */
float data_sum(float *p_data_start, float *p_data, int quantity);
   /* Sum the experimental scientific data values                     */
void print_total(float *p_data_start, float *p_data, int quantity);
   /* Print the sum of the experimental scientific data values        */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int    quantity;   /* Quantity of scientific data                  */
   float *data_start, /* Starting location of the scientific data     */
         *data,       /* Location of scientific data values           */
         *sort_start, /* Starting location of the sorted data         */
         *sort;       /* Location of sorted data values               */

   /* Print the heading                                               */
   printf("\n\n\n\n\n\n");
   print_heading();

   /* Loop processing of experimental scientific data                 */
   /* until the user quits                                            */
   while(print_instructions(),(quantity = get_quantity()) != QUIT)
   {
      float data_array[quantity],    /* Experimental scientific data  */
            sort_array[quantity];    /* Sorted scientific data        */
            data_start = data_array; /* Starting location of data     */
            sort_start = sort_array; /* Starting location sorted data */


      /* Allocate the memory for experimental scientific data         */
      /* and abort if not used                                        */
      if((data = (float *) malloc(sizeof(*data) * quantity)) == NULL)
      {
         printf("\nError #%d occurred in main()", MEM_ALLOC_ERR);
         printf("\nExperimental scientific data could not be allocated");
         printf("\nThe program is aborting");
         printf("\n\n\n\n\n\n");
         exit  (MEM_ALLOC_ERR);
      }
      if((sort = (float *) malloc(sizeof(*sort) * quantity)) == NULL)
      {
         printf("\nError #%d occurred in main()", SORT_ALLOC_ERR);
         printf("\nExperimental scientific data could not be sorted");
         printf("\nThe program is aborting");
         printf("\n\n\n\n\n\n");
         exit  (SORT_ALLOC_ERR);
      }

      /* Get experimental scientific data values, sort values,        */
      /* and sum values                                               */
      get_data_values     (data_start, data, quantity);
      sort_into_descending(data_start, sort_start, data, sort, quantity);
      memcpy              (data_array, sort_array, sizeof(sort_array[0])
                                                             * quantity);

      /* Print the sum of sorted experimental scientific              */
      /* data values                                                  */
      print_total(data_start, data, quantity);
      printf     ("\n                 ---------");
      printf     ("\n                  %8.2f total",
         data_sum(data_start, data, quantity));

      /* Free memory of the array                                     */
      free(data);
      free(sort);
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for processing numbers.  Have a nice day! ;-)");
   printf("\n\n\n\n\n\n");
   return 0;
}

/**********************************************************************/
/*                         Print the heading                          */
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
   printf("\n\n");
   printf("\nThis program processes experimental scientific data");
   printf("\n---------------------------------------------------");
   return;
}

/**********************************************************************/
/*         Get the quantity of experimental scientific data           */
/**********************************************************************/
int get_quantity()
{
   int quantity; /* Quantity of experimental scientific data          */

   printf("\n");
   do
   {
      printf("How many data values are there (%d to %d, %d = Quit): ",
         MINIMUM_QUANTITY, MAXIMUM_QUANTITY, QUIT);
      scanf (" %d", &quantity);
   }
   while((quantity < MINIMUM_QUANTITY || quantity > MAXIMUM_QUANTITY)
                                                   && quantity != QUIT);
   return quantity;
}

/**********************************************************************/
/*            Get all experimental scientific data values             */
/**********************************************************************/
void get_data_values(float *p_data_start, float *p_data, int quantity)
{
   for(p_data = p_data_start; (p_data - p_data_start) < quantity;
                                                               p_data++)
   {
      *p_data = 0.0f;
      printf("   Enter data value %d: ",
         (int) (p_data - p_data_start) + 1);
      scanf (" %f", p_data);
      if    (*p_data < 0.0f)
      {
         printf("       Negative %.2f ", *p_data);
         *p_data = -*p_data;
         printf("converted to positive %.2f\n", *p_data);
      }
   }
   return;
}

/**********************************************************************/
/*    Sort all experimental scientific data into descending order     */
/**********************************************************************/
void sort_into_descending(float *p_data_start, float *p_sort_start,
                             float *p_data, float *p_sort, int quantity)
{
   float *p_largest_data; /* Largest experimental scientific data value */

   for(p_sort = p_sort_start; (p_sort - p_sort_start) < quantity;
                                                               p_sort++)
   {
         *p_sort = 0.0f;
      for(p_data = p_data_start; (p_data - p_data_start) < quantity;
                                                               p_data++)
         if(*p_sort < *p_data || *p_sort == 0.0f)
         {
           *p_sort         = *p_data;
            p_largest_data = p_data;
         }
           *p_largest_data = 0.0f;
   }
   return;
}
/**********************************************************************/
/*      Calculate the sum of experimental scientific data values      */
/**********************************************************************/
float data_sum(float *p_data_start, float *p_data, int quantity)
{
   float data_sum = 0.0f; /* The sum of numbers in the array          */

   for(p_data = p_data_start; (p_data - p_data_start) < quantity;
                                                               p_data++)
      data_sum += *p_data;
   return data_sum;
}

/**********************************************************************/
/*    Print the sum of sorted experimental scientific data values     */
/**********************************************************************/
void print_total(float *p_data_start, float *p_data, int quantity)
{
   float *p_slow_data = p_data; /* Check for duplicates in data       */

   printf("\n\nThe data in descending order (with duplicates noted):");
   printf(  "\n-----------------------------------------------------");
   for   (p_data = p_data_start; (p_data - p_data_start) < quantity;
                                                               p_data++)
   {
      printf   ("\n                  %8.2f", *p_data);
      if       (*p_data == *p_slow_data)
         printf(" (duplicate)");
      p_slow_data = p_data;
   }
   return;
}
