/**********************************************************************/
/*                                                                    */
/* Program Name: program7 - Search ordered lists of whole numbers     */
/*                          using three different search algorithms   */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: November 14, 2019                                    */
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
/* This program ask for a whole number and then searches for that     */
/* whole number by using three different search algorithms.           */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/

#define DATA_SIZE       15          /* Maximum index length           */
#define LAST_INDEX      DATA_SIZE-1 /* True index length              */
#define QUIT            0           /* Program exit value             */
#define COURSE_NUMBER   "CS227"     /* PCC given course number        */
#define PROGRAM_NUMBER  7           /* Teacher given program number   */
#define PROGRAMMER_NAME "Teichroeb" /* The programmer's last name     */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the heading                                               */
void print_instructions();
   /* Print the instructions                                          */
void get_search_data(int search_type[], int last_index);
   /* Get the search data                                             */
int seq_search(int search_type[], int search_target,
               int *p_target_index, int last_index);
   /* Process an ordered sequential search                            */
int pro_search(int search_type[], int search_target,
               int *p_target_index, int last_index);
   /* Process a probability search                                    */
int bin_search(int search_type[], int search_target,
               int *p_target_index, int last_index);
   /* Process a binary search                                         */
void show_search_data(int search_type[], int search_target,
                                                        int last_index);
   /* Show the search data                                            */
void search_results(char result, int target_index);
   /* Display the search results                                      */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int bin_data[DATA_SIZE], /* Binary search data                     */
       pro_data[DATA_SIZE], /* Probability search data                */
       search_target,       /* Target number                          */
       seq_data[DATA_SIZE], /* Ordered sequential search data         */
       target_index;        /* Location of the target number          */

   /* Print the heading and the instructions                          */
   print_heading();
   print_instructions();

   /* Get the search data for each search type                        */
   get_search_data(seq_data, LAST_INDEX);
   get_search_data(pro_data, LAST_INDEX);
   get_search_data(bin_data, LAST_INDEX);

   /* Loop processing of three different search algorithms            */
   while(printf("\n\n\nEnter an integer search target (0 to quit): "),
         scanf (" %d" , &search_target), search_target != QUIT)
   {
      /* Process an ordered sequential search                         */
      printf("\n\nOrdered Sequential Search:");
      show_search_data(seq_data, search_target, LAST_INDEX);
      if(seq_search(seq_data, search_target, &target_index, LAST_INDEX))
         search_results('S', target_index);
      else
         search_results('U', target_index);

      /* Process a probability search                                 */
      printf("\n\nProbability Search:");
      show_search_data(pro_data, search_target, LAST_INDEX);
      if(pro_search(pro_data, search_target, &target_index, LAST_INDEX))
         search_results('S', target_index);
      else
         search_results('U', target_index);

      /* Process a binary search                                      */
      printf("\n\nBinary Search:");
      show_search_data(bin_data, search_target, LAST_INDEX);
      if(bin_search(bin_data, search_target, &target_index, LAST_INDEX))
         search_results('S', target_index);
      else
         search_results('U', target_index);
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for searching.  Have a nice day! ;-)");
   printf("\n\n\n\n\n\n");
   return 0;
}

/**********************************************************************/
/*                         Print the heading                          */
/**********************************************************************/
void print_heading()
{
   printf(  "\n======================================================");
   printf(  "\n               Program Number: %d",    PROGRAM_NUMBER);
   printf(  "\n               Programmer: %s",        PROGRAMMER_NAME);
   printf(  "\n               PCC Course Number: %s", COURSE_NUMBER);
   printf(  "\n======================================================");
   return;
}

/**********************************************************************/
/*                      Print the instructions                        */
/**********************************************************************/
void print_instructions()
{
   printf("\nThis program demonstrates various search algorithms.");
   printf("\nYou enter in any whole number, and the program will");
   printf("\nsearch for it in an ORDERED array of whole numbers");
   printf("\nusing each of the following search algorithms:");
   printf("\n     1. Ordered Sequential Search");
   printf("\n     2. Probability Search");
   printf("\n     3. Binary Search");
   printf("\nThe progress of each search is shown so the efficiency");
   printf("\nof the search algorithms can be compared.");
   return;
}

/**********************************************************************/
/*                       Get the search data                          */
/**********************************************************************/
void get_search_data(int search_type[], int last_index)
{
   int index; /* Index of search formula                              */

   for(index = 0; index <= last_index; index++)
      search_type[index] = (5 * index + 10);
   return;
}

/**********************************************************************/
/*                       Show the search data                         */
/**********************************************************************/
void show_search_data(int search_type[], int search_target,
                                                         int last_index)
{
   int index; /* Index of search data                                 */

   printf("\n   Array Index: ");
   for(index = 0; index <= last_index; index++)
      printf("[%2d]", index);
   printf("\n    Array Data:");
   for(index = 0; index <= last_index; index++)
      printf("  %2d", search_type[index]);
   printf("\n   User Target:");
   printf("  %2d", search_target);
   printf("\n   Search Path: ");
   return;
}

/**********************************************************************/
/*                     Ordered Sequential Search                      */
/**********************************************************************/
int seq_search(int search_type[], int search_target,
               int *p_target_index, int last_index)
{
   int index = 0; /* Index of the ordered sequential search           */

   if(search_target <= search_type[last_index])
   {
      while(printf("[%2d]", index), search_type[index] < search_target)
         index++;
      *p_target_index = index;
   }
   else
   {
      *p_target_index = last_index;
      printf("[%2d]", *p_target_index);
   }
   return search_target == search_type[*p_target_index];
}

/**********************************************************************/
/*                        Probability Search                          */
/**********************************************************************/
int pro_search(int search_type[], int search_target,
               int *p_target_index, int last_index)
{
   int index = 0,        /* Index of the probability search           */
       temporary_number; /* Use to swap whole numbers                 */

   while(printf("[%2d]", index),
         index < last_index && search_target != search_type[index])
      index++;
   if(index > 0 && search_target == search_type[index])
   {
      temporary_number       = search_type[index];
      search_type[index]     = search_type[index - 1];
      search_type[index - 1] = temporary_number;
      *p_target_index        = index - 1;
   }
   else
      *p_target_index = index;
   return search_target == search_type[*p_target_index];
}

/**********************************************************************/
/*                           Binary Search                            */
/**********************************************************************/
int bin_search(int search_type[], int search_target,
               int *p_target_index, int last_index)
{
   int begin_index = 0,        /* Beginning index after the middle    */
       end_index = last_index, /* Ending index after the beginning    */
       middle_index;           /* Middle index of the beginning and   */
                               /* ending                              */

   while(begin_index <= end_index)
   {
      middle_index = (begin_index + end_index) / 2;
      if(search_target > search_type[middle_index])
         begin_index = middle_index + 1;
      else
      {
         if(search_target < search_type[middle_index])
            end_index   = middle_index - 1;
         else
            begin_index = end_index + 1;
      }
      printf("[%2d]", middle_index);
   }
   *p_target_index = middle_index;
   return search_target == search_type[*p_target_index];
}

/**********************************************************************/
/*                    Display the search results                      */
/**********************************************************************/
void search_results(char result, int target_index)
{
   printf("\nSearch Outcome: ");
   if(result == 'S')
      printf("Successful - target found at index [%2d]", target_index);
   else
   {
      if(result == 'U')
         printf("Unsuccessful - target not found");
      else
         printf("Undetermined");
   }
   return;
}
