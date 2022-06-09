/*********************************************************************
 CLASS INFORMATION
 -----------------
   Program Name: program11
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     05/02/2019

 DOCUMENTATION
 -------------
   This program sorts names alphabetically.
 ********************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_OF_NAMES 8
#define NAME_SIZE 4

void printNames(char names[][NAME_SIZE], int size);
void bubbleSortNames(char names[][NAME_SIZE], int last);
bool binarySearchNames(char list[][NAME_SIZE], int end, char target[],
                       int *location);

int main()
{
   char nameList[NUM_OF_NAMES][NAME_SIZE] =
   {
      "Bob",
      "Sue",
      "Jak",
      "Rod",
      "Jon",
      "Ash",
      "Deb",
      "Kay"
   };
   char searchText[NAME_SIZE];
   char userChoice;
   int  searchLocation;

   printf("\n\n\nLIST BEFORE SORTING\n");
   printNames(nameList, NUM_OF_NAMES);

   bubbleSortNames(nameList, NUM_OF_NAMES - 1);

   printf("\n\n\nLIST AFTER SORTING\n");
   printNames(nameList, NUM_OF_NAMES);

   printf("\n\n\nWould you like to search for a name? (y/n) ");
   scanf(" %c", &userChoice);

   while(userChoice == 'y')
   {
      printf("\n\n\nPlease try and search for a name: ");
      scanf("%3s", searchText);

      if(binarySearchNames(nameList, NUM_OF_NAMES - 1, searchText,
         &searchLocation))
      {
         printf("\n\n\nThe name %s was found at location %d!",
         searchText, searchLocation);
      }
      else
      {
         printf("\n\n\nThe name %s was not found. :(\n", searchText);
      }

      printf("\nWould you like to search for another name? (y/n) ");
      scanf(" %c", &userChoice);
   }

   printf("\n\n\nThank you for using this program.\n\n\n");

   return 0;
}
/*********************************************************************
   Displays all of the names.
*********************************************************************/
void printNames(char names[][NAME_SIZE], int size)
{
   int index;

   for(index = 0; index < size; index++)
   {
      puts(names[index]);
   }

   return;
}

/*********************************************************************
   Sorts all of the names alphabetically.
*********************************************************************/
void bubbleSortNames(char names[][NAME_SIZE], int last)
{
   char temp[NAME_SIZE];

   int current,
       walker;

   for(current = 0; current < last; current++)
   {
      for(walker = last; walker > current; walker--)
      {
         if(strcmp(names[walker], names[walker - 1]) < 0)
         {
            strncpy(temp, names[walker], sizeof(temp) - 1);
            strncpy(names[walker],
                    names[walker - 1], sizeof(names[walker -1]) - 1);
            strncpy(names[walker - 1],
                    temp, sizeof(names[walker -1]) - 1);
         }
      }
   }

   return;
}

/*********************************************************************
   Searches the names to see if the typed name is in the list.
*********************************************************************/
bool binarySearchNames(char list[][NAME_SIZE], int end, char target[],
                       int *location)
{
   int first = 0,
       last = end,
       mid;

   while(first <= last)
   {
      mid = (first + last) / 2;
      if(strcmp(target, list[mid]) > 0)
      {
         first = mid + 1;
      }
      else if(strcmp(target, list[mid]) < 0)
      {
         last = mid - 1;
      }
      else
      {
         first = last + 1;
      }
   }

   *location = mid;

   return strcmp(target, list[mid]) == 0;
}
