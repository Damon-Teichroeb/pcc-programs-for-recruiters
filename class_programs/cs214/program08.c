/*************************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program08
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     04/04/2019

 DOCUMENTATION
 -------------
   This program allows the user to choose a pattern and a number
   which will print to another file.
 ************************************************************************/
#include <stdio.h>

#define PATTERN1 '1'
#define PATTERN2 '2'
#define PATTERN3 '3'
#define PATTERN4 '4'
#define SIZE_MIN 2
#define SIZE_MAX 9
#define QUIT     '5'

void printInstructions ();
void printMenu();
char getMenuChoice();
int  getUserValue();
void displayPattern1(int value);
void displayPattern2(int value);
void displayPattern3(int value);
void displayPattern4(int value);
void printGoodbye();

int main ()
{
   char  menuChoice;

   printInstructions();
   printMenu();

   menuChoice = getMenuChoice();

   switch (menuChoice)
   {
      case PATTERN1:
         displayPattern1(getUserValue());
         break;
      case PATTERN2:
         displayPattern2(getUserValue());
         break;
      case PATTERN3:
         displayPattern3(getUserValue());
         break;
      case PATTERN4:
         displayPattern4(getUserValue());
         break;
      case QUIT:
         printf("Ending the program");
         break;
   }

   printGoodbye();

   return 0;
}

/*************************************************************************
   Displays instructions to the user.
*************************************************************************/
void printInstructions()
{
   printf("This program will display a number pattern in a file.\n\n");
   printf("Please type in a number for your menu choice.        \n\n");

   return;
}

/*************************************************************************
   Displays the menu to the user.
*************************************************************************/
void printMenu()
{
   printf("Menu:                      \n");
   printf("---------------------------\n");
   printf("%c. Pattern One            \n", PATTERN1);
   printf("%c. Pattern Two            \n", PATTERN2);
   printf("%c. Pattern Three          \n", PATTERN3);
   printf("%c. Pattern Four           \n", PATTERN4);
   printf("%c. Quit                   \n\n", QUIT);

   return;
}

/*************************************************************************
   Recieves a number from the user.
*************************************************************************/
char getMenuChoice()
{
   char menuChoice;

   printf("Choose an option (between %c and %c): ", PATTERN1, QUIT);
   scanf(" %c", &menuChoice);

   while (menuChoice < PATTERN1 || menuChoice > QUIT)
   {
      printf("Your option is incorrect. Please try again: ");
      scanf(" %c", &menuChoice);
   }

   printf("\n");
   return menuChoice;
}

/*************************************************************************
   Recieves another number from the user.
*************************************************************************/
int  getUserValue()
{
   int value;

   printf("Choose a pattern size (between %d and %d): ",
      SIZE_MIN, SIZE_MAX);
   scanf(" %d", &value);

   while (value < SIZE_MIN || value > SIZE_MAX)
   {
      printf("Your option is incorrect. Please try again: ");
      scanf(" %d", &value);
   }

   return value;
}

/*************************************************************************
   Outputs the first pattern to the file.
*************************************************************************/
void displayPattern1(int value)
{
   FILE *fileOut;

   fileOut = fopen("teichroeb08.txt", "w");

   int rows,
       columns;

   for (rows = 1; rows <= value; rows++)
   {
      for(columns = 1; columns <= value; columns++)
      {
         if(rows == columns)
         {
            fprintf(fileOut,"%d", value);
         }
         else
         {
            fprintf(fileOut,"$");
         }
      }

      fprintf(fileOut,"\n");
   }

   fclose(fileOut);

   printf("\n");
   printf("The pattern was written to the file: teichroeb08.txt");

   return;
}

/*************************************************************************
   Outputs the second pattern to the file.
*************************************************************************/
void displayPattern2(int value)
{
   FILE *fileOut;

   fileOut = fopen("teichroeb08.txt", "w");

   int rows,
       columns;

   for (rows = value; rows >= 1; rows--)
   {
      for(columns = 1; columns <= value; columns++)
      {
         if(rows == columns)
         {
            fprintf(fileOut,"%d", value);
         }
         else
         {
            fprintf(fileOut,"$");
         }
      }

      fprintf(fileOut,"\n");
   }

   fclose(fileOut);

   printf("\n");
   printf("The pattern was written to the file: teichroeb08.txt");

   return;
}

/*************************************************************************
   Outputs the third pattern to the file.
*************************************************************************/
void displayPattern3(int value)
{
   FILE *fileOut;

   fileOut = fopen("teichroeb08.txt", "w");

   int rows,
       columns;

   for (rows = value; rows >= 1; rows--)
   {
      for(columns = 1; columns <= value; columns++)
      {
         if(rows < columns)
         {
            fprintf(fileOut,"%d", value);
         }
         else
         {
            fprintf(fileOut,"$");
         }
      }

     fprintf(fileOut,"\n");
   }

   fclose(fileOut);

   printf("\n");
   printf("The pattern was written to the file: teichroeb08.txt");

   return;
}

/*************************************************************************
   Outputs the fourth pattern to the file.
*************************************************************************/
void displayPattern4(int value)
{
   FILE *fileOut;

   fileOut = fopen("teichroeb08.txt", "w");

   int rows,
       columns;

   for (rows = 1; rows <= value; rows++)
   {
      for(columns = 1; columns <= value; columns++)
      {
         if(rows > columns)
         {
            fprintf(fileOut,"%d", value);
         }
         else
         {
            fprintf(fileOut,"$");
         }
      }

      fprintf(fileOut,"\n");
   }

   fclose(fileOut);

   printf("\n");
   printf("The pattern was written to the file: teichroeb08.txt");

   return;
}

/*************************************************************************
   Displays a goodbye message to the user.
*************************************************************************/
void printGoodbye()
{
   printf("\n");
   printf("Have a nice day!\n");

   return;
}
