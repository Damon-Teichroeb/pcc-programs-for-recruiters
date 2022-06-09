/**********************************************************************/
/*                                                                    */
/* Program Name: program4 - Process Accounts Receivable Customer Data */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS227, Data Structures and Algorithms                */
/* Date Written: October 16, 2019                                     */
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
/* This program gets the amount of customers for the accounts         */
/* receivable customer database and gets all of the information of    */
/* each customer. Last, it shows all of the accounts cleanly and in   */
/* alphabetical order. This process repeats until the user quits.     */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define END_OF_STRING   '\0'    /* The end of string character        */
#define NEW_LINE        '\n'    /* The new line character             */
#define MIN_CUSTOMERS   2       /* Smallest amount of customers       */
#define MAX_CUSTOMERS   100     /* Largest amount of customers        */
#define QUIT            0       /* Program exit value                 */
#define DB_ALLOC_ERR    1       /* Can't allocate memory error        */
#define MAX_NAME_LENGTH 20      /* Maximum last name length           */
#define COURSE_NUMBER   "CS227" /* PCC assigned course number         */
#define PROGRAM_NUMBER  4       /* Teacher assigned program number    */
#define PROGRAMMER_NAME "Teichroeb"
                                /* The programmer's last name         */

/**********************************************************************/
/*                         Program Structures                         */
/**********************************************************************/
/* Accounts receivable customer database                              */
struct customer
{
   char  last_name[MAX_NAME_LENGTH + 1];
   float amount_owed;
   int   priority;
};
typedef struct customer CUSTOMER; /* Customer given by user           */

/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void print_heading();
   /* Print the heading                                               */
void print_instructions();
   /* Print the instructions                                          */
int get_customers();
   /* Get the amount of customers                                     */
void get_customer_data(CUSTOMER *p_customer_start, int amount);
   /* Get the accounts receivable customer data                       */
void get_last_name(CUSTOMER *p_customer);
   /* Get the customer's last name                                    */
void get_amount_owed(CUSTOMER *p_customer);
   /* Get the amount of money owed                                    */
void get_priority(CUSTOMER *p_customer);
   /* Get the customer's priority                                     */
char clean_customers(CUSTOMER *p_customer);
   /* Clean the names of each customer                                */
void sort_customers(CUSTOMER *p_customer_start, int amount);
   /* Sort all accounts aplhabetically by last name                   */
void print_customers(CUSTOMER *p_customer_start, int amount);
   /* Print the accounts receivable customer database                 */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main()
{
   int amount;      /* Amount of customers                            */
   CUSTOMER *p_customer_start;
                    /* Point to accounts receivable customer database */

   /* Print the heading                                               */
   printf("\n\n\n\n\n\n");
   print_heading();

   /* Print the instructions and do loop processing of the accounts   */
   /* receivable customer database                                    */
   while(print_instructions(), (amount = get_customers())!= QUIT)
   {

      /* Allocate memory of the accounts receivable customer database */
      /* and abort if not used                                        */
      if((p_customer_start=(CUSTOMER *)malloc(sizeof(*p_customer_start)*
                                                         amount))==NULL)
      {
         printf("\nError #%d occurred in main()", DB_ALLOC_ERR);
         printf("\nMemory for the accounts receivable customer data");
         printf("\ncould not be allocated");
         printf("\nThe program is aborting");
         exit  (DB_ALLOC_ERR);
      }

      /* Get the accounts receivable customer data, sort the data,    */
      /* and print the data.                                          */
      get_customer_data(p_customer_start, amount);
      sort_customers   (p_customer_start, amount);
      print_customers  (p_customer_start, amount);

      /* Print end of customer database processing                    */
      printf("\n\n******* End Of Customer Database Processing *******");

      /* Free memory of the accounts receivable customer database     */
      free(p_customer_start);
   }

   /* Say good-bye and terminate the program                          */
   printf("\nThanks for processing accounts. Have a nice day! ;-)");
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
   printf("\n\nThis program allows you to input customers which owe");
   printf(  "\nyou money (your accounts receivable), and manage these");
   printf(  "\naccounts in a database.  You will enter the following:");
   printf(  "\n   Customer last name (1-%d characters)",
      MAX_NAME_LENGTH);
   printf(  "\n   Amount the customer owes (to the exact cent)");
   printf(  "\n   Customer priority (1=VIP, 2=Important, 3=Regular)");
   printf(  "\nFrom %d to %d customers may be processed.",
      MIN_CUSTOMERS, MAX_CUSTOMERS);
   printf("\n\nGet the customers for the database");
   printf(  "\n--------------------------------------------------");
   return;
}

/**********************************************************************/
/*                    Get the amount of customers                     */
/**********************************************************************/
int get_customers()
{
   int amount; /* Amount of customers                                 */

   printf("\n");
   do
   {
      printf("How many customers do you have (%d to %d, %d=Quit): ",
         MIN_CUSTOMERS, MAX_CUSTOMERS, QUIT);
      scanf (" %d", &amount);
   }
   while((amount < MIN_CUSTOMERS ||
          amount > MAX_CUSTOMERS)&& amount != QUIT);
   return amount;
}

/**********************************************************************/
/*               Get accounts receivable customer data                */
/**********************************************************************/
void get_customer_data(CUSTOMER *p_customer_start, int amount)
{
   CUSTOMER *p_customer; /* Point to each account                     */

   /* Get the accounts receivable customer data                       */
   for(p_customer=p_customer_start;
                     (p_customer-p_customer_start)<amount; p_customer++)
   {
      printf("\nCustomer number %d:",
         (int)(p_customer-p_customer_start+1));
      get_last_name  (p_customer);
      get_amount_owed(p_customer);
      get_priority   (p_customer);

      /* Remove all non-letters from each name and title case names   */
      p_customer->last_name[0] = clean_customers(p_customer);
   }
   return;
}

/**********************************************************************/
/*                     Get customer's last name                       */
/**********************************************************************/
void get_last_name(CUSTOMER *p_customer)
{
   char *p_fast, /* Point to last name chars                          */
        *p_slow; /* Point to the most recently typed char             */

   printf("\n   Enter the customer's last name: ");
   p_fast = p_customer->last_name;
   getchar();
   do
   {
      *p_fast = getchar();
      p_slow = p_fast;
      p_fast++;
   }
   while (*p_slow != NEW_LINE);
   *p_slow = END_OF_STRING;
   return;
}

/**********************************************************************/
/*                     Get amount of money owed                       */
/**********************************************************************/
void get_amount_owed(CUSTOMER *p_customer)
{
   printf("   Enter the amount owed: ");
   scanf (" %f", &p_customer->amount_owed);
   return;
}

/**********************************************************************/
/*                    Get the customer's priority                     */
/**********************************************************************/
void get_priority(CUSTOMER *p_customer)
{
   do
   {
      printf("   Enter the customer's priority (1-3): ");
      scanf (" %d", &p_customer->priority);
   }
   while (p_customer->priority < 1 || p_customer->priority > 3);
   return;
}

/**********************************************************************/
/*         Remove all non-letters and convert to title case           */
/**********************************************************************/
char clean_customers(CUSTOMER *p_customer)
{
   char *p_fast = p_customer->last_name,
                                    /* Point to every char in name    */
        *p_slow = p_customer->last_name;
                                    /* Point to all valid characters  */

   while(*p_fast != END_OF_STRING)
   {
      if(isalpha(*p_fast))
         *p_slow++ = tolower(*p_fast);
      p_fast++;
   }
   *p_slow = END_OF_STRING;
   return toupper(p_customer->last_name[0]);
}

/**********************************************************************/
/*          Sort all accounts aplhabetically by last name             */
/**********************************************************************/
void sort_customers(CUSTOMER *p_customer_start, int amount)
{
   CUSTOMER *p_inner,            /* Point to inner account            */
            *p_outer,            /* Point to outer account            */
            temporary_customer;  /* Temporary account                 */

   for(p_outer=p_customer_start; (p_outer-p_customer_start)<amount-1;
                                                              p_outer++)
      for(p_inner=p_outer+1; (p_inner-p_customer_start)<amount;
                                                              p_inner++)
         if(strcmp(p_outer->last_name, p_inner->last_name)>0)
         {
            temporary_customer = *p_outer;
            *p_outer           = *p_inner;
            *p_inner           = temporary_customer;
         }
   return;
}

/**********************************************************************/
/*         Print the accounts receivable customer database            */
/**********************************************************************/
void print_customers(CUSTOMER *p_customer_start, int amount)
{
   CUSTOMER *p_customer; /* Point to each account                     */

   printf("\n  Here is the accounts receivable customer database");
   printf("\n=====================================================");
   printf("\n   Customer Name         Amount        Priority");
   printf("\n--------------------    ---------    -------------");
   for(p_customer=p_customer_start;
                     (p_customer-p_customer_start)<amount; p_customer++)
   {
      printf("\n%20s    $%8.2f    %d ", p_customer->last_name,
         p_customer->amount_owed, p_customer->priority);
      switch(p_customer->priority)
      {
         case 1: printf("(VIP)");
                 break;
         case 2: printf("(Important)");
                 break;
         case 3: printf("(Regular)");
      }
   }
   return;
}
