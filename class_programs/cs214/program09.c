/*************************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program09
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     04/11/2019

 DOCUMENTATION
 -------------
   This program will process the file when the user selects a process type
   from the menu.
 ************************************************************************/
#include <stdio.h>
#include <ctype.h>

#define ALL_OPTION  1
#define ALPHA_CHARS 2
#define DIGIT_CHARS 3
#define PUNCT_CHARS 4
#define SPACE_CHARS 5
#define QUIT        6

void printInstructions();
void printMenu();
int  getMenuChoice();
int  processFile(int choice);
void printResult(int choice, int result);
void printGoodbye();

int main()
{
   int charCount,
       menuChoice;

   printInstructions();
   printMenu();

   menuChoice = getMenuChoice();

   while(menuChoice != QUIT)
   {
      switch (menuChoice)
      {
         case ALPHA_CHARS:
         case DIGIT_CHARS:
         case PUNCT_CHARS:
         case SPACE_CHARS:
            charCount = processFile(menuChoice);
            printResult(menuChoice, charCount);
            break;
         case ALL_OPTION:
            charCount = processFile(ALPHA_CHARS);
            printResult(ALPHA_CHARS, charCount);

            charCount = processFile(DIGIT_CHARS);
            printResult(DIGIT_CHARS, charCount);

            charCount = processFile(PUNCT_CHARS);
            printResult(PUNCT_CHARS, charCount);

            charCount = processFile(SPACE_CHARS);
            printResult(SPACE_CHARS, charCount);
            break;
         default:
            printf("Unknown choice.");
            break;
      }
      printMenu();
      menuChoice = getMenuChoice();
   }

   printGoodbye();

   return 0;
}

/*************************************************************************
   Displays the instructions.
*************************************************************************/
void printInstructions()
{
   printf("\nThis program will process \"input09.txt\" when a ");
   printf("process type is selected.\n");

   printf("\nPlease type in a number corresponding to the menu ");
   printf("choice below.\n");

   return;
}

/*************************************************************************
   Displays the menu choices.
*************************************************************************/
void printMenu()
{
   printf("\n\nMenu:                   \n");
   printf("--------------------------- \n");
   printf("%d - All Options            \n", ALL_OPTION);
   printf("%d - Alpha Characters       \n", ALPHA_CHARS);
   printf("%d - Digit Characters       \n", DIGIT_CHARS);
   printf("%d - Puncuation Characters  \n", PUNCT_CHARS);
   printf("%d - Space Characters       \n", SPACE_CHARS);
   printf("%d - Quit                   \n", QUIT);

   return;
}

/*************************************************************************
   Recieves a value from the user.
*************************************************************************/
int  getMenuChoice()
{
   int value;

   printf("\nChoose a menu option (between %d and %d): ",
      ALL_OPTION, QUIT);
   scanf(" %d", &value);

   printf("\n");

   return value;
}

/*************************************************************************
   Uses four different types of processes.
*************************************************************************/
int processFile(int choice)
{
   char  character;
   int   result = 0;
   FILE *fileIn;

   fileIn = fopen("input09.txt","r");

   while(fscanf(fileIn, "%c", &character) != EOF)
   {
      if(choice == ALPHA_CHARS && isalpha(character))
      {
         result++;
      }

      if(choice == DIGIT_CHARS && isdigit(character))
      {
         result++;
      }

      if(choice == PUNCT_CHARS && ispunct(character))
      {
         result++;
      }

      if(choice == SPACE_CHARS && isspace(character))
      {
         result++;
      }
   }
   fclose(fileIn);

   return result;
}

/*************************************************************************
   Displays the results.
*************************************************************************/
void printResult(int choice, int result)
{
   switch(choice)
   {
      case ALPHA_CHARS:
         printf("Total alphabetic characters = %d\n", result);
         break;
      case DIGIT_CHARS:
         printf("Total digit characters = %d\n", result);
         break;
      case PUNCT_CHARS:
         printf("Total punctuation characters = %d\n", result);
         break;
      case SPACE_CHARS:
         printf("Total whitespace characters = %d\n", result);
		 break;
   }

   return;
}

/*************************************************************************
   Displays a closing message.
*************************************************************************/
void printGoodbye()
{
   printf("Thank you for using my program! \n");
   printf("Have a nice day!                \n");

   return;
}
