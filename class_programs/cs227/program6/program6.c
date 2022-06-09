/**********************************************************************/
/*                                                                    */
/* Program Name: program6 - Process List of Student IDs               */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: December 5, 2019                                     */
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
/* This program asks the user to create a student id list, then it    */
/* displays the data with unsorted, sorted, and cleaned student id    */
/* lists.                                                             */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define MAXIMUM_ID        999999  /* Largest student ID               */
#define MINIMUM_ID        1       /* Smallest student ID              */
#define LIST_HEADER       MINIMUM_ID - 1
                                  /* Beginning of student list        */
#define LIST_TRAILER      MAXIMUM_ID + 1
                                  /* Ending of student list           */
#define HEADER_ALLOC_ERR  1       /* Cannot allocate header memory    */
#define TRAILER_ALLOC_ERR 2       /* Cannot allocate trailer memory   */
#define ID_ALLOC_ERR      3       /* Cannot allocate ID memory        */
#define QUIT              0       /* Program exit value               */
#define COURSE_NUMBER     "CS227" /* PCC assigned course number       */
#define PROGRAM_NUMBER    6       /* Teacher assigned program number  */
#define PROGRAMMER_NAME   "Teichroeb"
                                  /* The programmer's last name       */

/**********************************************************************/
/*                         Program Structures                         */
/**********************************************************************/
/* Structure of student id's                                          */
struct student
{
   int            student_id;
   struct student *p_next_student;
};
typedef struct student STUDENT; /* Reference to student id structures */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the heading                                               */
void print_instructions();
   /* Print the instructions                                          */
char get_response();
   /* Get the response                                                */
STUDENT *p_empty_student_list(int list_header, int list_trailer);
   /* Create the empty student id list                                */
void insert_student(STUDENT *p_student_list, int student_id);
   /* Create a new student id                                         */
int get_number_of_students(STUDENT *p_student_list, int list_trailer);
   /* Get the number of students                                      */
void print_student_ids(STUDENT *p_student_list, int list_trailer);
   /* Print the student id list                                       */
void sort_student_ids(STUDENT *p_student_list, int list_trailer);
   /* Sort the student id list into ascending order                   */
void remove_duplicate_ids(STUDENT *p_student_list, int list_trailer);
   /* Remove duplicate student id's                                   */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   STUDENT *p_student_list,  /* Point to the student id list          */
           *p_student_start; /* Point to the student id list header   */
   int     student_id;       /* Student id number                     */

   /* Print the heading                                               */
   print_heading();

   /* Loop processing of the student id list until the user quits     */
   while(print_instructions(), get_response() == 'y')
   {

      /* Create an empty student id list                              */
      p_student_list  = p_empty_student_list(LIST_HEADER, LIST_TRAILER);
      p_student_start = p_student_list;

      /* Loop processing to create new student id's until the user    */
      /* quits                                                        */
      while(printf("Enter the next student id (%d to quit): ", QUIT),
            scanf (" %d", &student_id), student_id >= MINIMUM_ID)
         if(student_id > MAXIMUM_ID)
         {
            printf("    Id rejected - it cannot exceed %d", MAXIMUM_ID);
            printf("\n");
         }
         else
            insert_student(p_student_list, student_id);

      /* Print the unsorted, raw student id list data                 */
      printf("\nThe unsorted student id list, as entered, is:");
      print_student_ids(p_student_list, LIST_TRAILER);
      printf("\nThe length of the unsorted student id list is: %d",
         get_number_of_students(p_student_list, LIST_TRAILER));

      /* Print the sorted student id list data in ascending order     */
      sort_student_ids(p_student_list, LIST_TRAILER);
      printf("\n\nThe student id list, sorted ascending by id, is:");
      print_student_ids(p_student_list, LIST_TRAILER);
      printf("\nThe length of the sorted student id list is: %d",
         get_number_of_students(p_student_list, LIST_TRAILER));

      /* Print the sorted student id list data with duplicate         */
      /* numbers removed                                              */
      remove_duplicate_ids(p_student_list, LIST_TRAILER);
      printf("\nThe student id list, with duplicate id's removed, ");
      printf("sorted ascending by id, is:");
      print_student_ids(p_student_list, LIST_TRAILER);
      printf("\nThe length of the cleaned and sorted student ");
      printf("id list is: %d",
         get_number_of_students(p_student_list, LIST_TRAILER));

      /* Loop processing to free the student id list data until the   */
      /* list trailer is reached                                      */
      while(p_student_list = p_student_start->p_next_student,
            p_student_list->p_next_student != NULL)
      {
         p_student_start->p_next_student=p_student_list->p_next_student;
         free(p_student_list);
      }
      free(p_student_start);
      free(p_student_list);
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for using this program.  Have a nice day! ;-)");
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
   printf("\n\n");
   printf("\n    This program maintains a list of students by their");
   printf("\n    id number.  After entry of all id's, it sorts them");
   printf("\n    into ascending order, then removes all duplicates.");
   return;
}

/**********************************************************************/
/*                         Get the response                           */
/**********************************************************************/
char get_response()
{
   char single_letter; /* Response character                          */

   printf("\n");
   do
   {
      printf("\nDo you want to enter another student id list ");
      printf("(y or n): ");
      scanf (" %c", &single_letter);
      single_letter = tolower(single_letter);
   }
   while (single_letter != 'y' && single_letter != 'n');
   return single_letter;
}

/**********************************************************************/
/*                  Create an empty student id list                   */
/**********************************************************************/
STUDENT *p_empty_student_list(int list_header, int list_trailer)
{
   STUDENT *p_new_student; /* Point to the newly created student list */

   if((p_new_student = (STUDENT *) malloc(sizeof(STUDENT))) == NULL)
   {
      printf("\nError #%d occurred in p_empty_student_list.",
                                                      HEADER_ALLOC_ERR);
      printf("\nCannot allocate memory for the list header");
      printf("\nThe program is aborting.");
      exit(HEADER_ALLOC_ERR);
   }
   p_new_student->student_id = list_header;

   if((p_new_student->p_next_student=(STUDENT *)malloc(sizeof(STUDENT)))
                                                                == NULL)
   {
      printf("\nError #%d occurred in p_empty_student_list.",
                                                     TRAILER_ALLOC_ERR);
      printf("\nCannot allocate memory for the list trailer");
      printf("\nThe program is aborting.");
      exit(TRAILER_ALLOC_ERR);
   }
   p_new_student->p_next_student->student_id     = list_trailer;
   p_new_student->p_next_student->p_next_student = NULL;
   return p_new_student;
}

/**********************************************************************/
/*                      Create a new student id                       */
/**********************************************************************/
void insert_student(STUDENT *p_student_list, int student_id)
{
   STUDENT *p_insert_student; /* Point to the new student id          */

   if((p_insert_student = (STUDENT *) malloc(sizeof(STUDENT))) == NULL)
   {
      printf("\nError #%d occurred in insert_student.", ID_ALLOC_ERR);
      printf("\nCannot allocate memory for the new student");
      printf("\nThe program is aborting.");
      exit(ID_ALLOC_ERR);
   }
   p_insert_student->student_id     = student_id;
   p_insert_student->p_next_student = p_student_list->p_next_student;
   p_student_list->p_next_student   = p_insert_student;
   return;
}

/**********************************************************************/
/*                    Get the number of students                      */
/**********************************************************************/
int get_number_of_students(STUDENT *p_student_list, int list_trailer)
{
   int student_amount = 0; /* Number of students                      */

   while(p_student_list = p_student_list->p_next_student,
         p_student_list->student_id != list_trailer)
      student_amount++;
   return student_amount;
}

/**********************************************************************/
/*                      Print the student list                        */
/**********************************************************************/
void print_student_ids(STUDENT *p_student_list, int list_trailer)
{
   while(p_student_list = p_student_list->p_next_student,
         p_student_list->student_id != list_trailer)
      printf("\n                   %6d", p_student_list->student_id);
   return;
}

/**********************************************************************/
/*             Sort the student list into ascending order             */
/**********************************************************************/
void sort_student_ids(STUDENT *p_student_list, int list_trailer)
{
   STUDENT *p_current_student = p_student_list,
                                 /* Point to the student id list      */
           *p_temporary_student; /* Temporarily point to a student id */

   while(p_student_list->p_next_student->student_id != list_trailer)
   {
      while(p_current_student->p_next_student->
               p_next_student->student_id != list_trailer)
      {
         if(p_current_student->p_next_student->student_id >
            p_current_student->p_next_student->
               p_next_student->student_id)
         {
            p_temporary_student =
               p_current_student->p_next_student->p_next_student;
            p_current_student->p_next_student->p_next_student =
               p_current_student->p_next_student->
               p_next_student->p_next_student;
            p_temporary_student->p_next_student =
               p_current_student->p_next_student;
            p_current_student->p_next_student = p_temporary_student;
            p_current_student = p_student_list;
         }
         else
            p_current_student = p_current_student->p_next_student;
      }
      p_student_list = p_student_list->p_next_student;
   }
   return;
}

/**********************************************************************/
/*                 Remove all duplicate student id's                  */
/**********************************************************************/
void remove_duplicate_ids(STUDENT *p_student_list, int list_trailer)
{
   STUDENT *p_current_student; /* Point to the duplicate student id   */

   printf("\n");
   while(p_current_student = p_student_list->p_next_student,
         p_current_student->student_id != list_trailer)
      if(p_student_list->student_id == p_current_student->student_id)
      {
         printf("\nDeleting the duplicate student id: %d",
            p_current_student->student_id);
         p_student_list->p_next_student =
            p_current_student->p_next_student;
         free(p_current_student);
      }
      else
         p_student_list = p_student_list->p_next_student;
   return;
}
