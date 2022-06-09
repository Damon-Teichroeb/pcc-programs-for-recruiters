//**********************************************************************
//*                                                                    *
//* Program Name: PROG01 - Calculate and Draw a Picture of a Rectangle *
//* Author:       Damon L. Teichroeb                                   *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: February 1, 2020                                     *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* I pledge this assignment is my own first time work.                *
//* I pledge I did not copy or try to copy any work from the Internet. *
//* I pledge the only person I asked for help from was my teacher.     *
//* I pledge I did not attempt to help any student on this assignment. *
//* I understand if I violate this pledge I will receive a 0 grade.    *
//*                                                                    *
//*                                                                    *
//*                      Signed: _____________________________________ *
//*                                           (signature)              *
//*                                                                    *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* This program asks the user to input the length and width of a      *
//* rectangle. Then the program calculates the dimensions, draws the   *
//* rectangle, and displays the specifications of the rectangle.       *
//*                                                                    *
//**********************************************************************

#include <iostream>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define MIN_RECT_LENGTH 1.0f    // Rectangle minimum length
#define MIN_RECT_WIDTH  1.0f    // Rectangle minimum width
#define RECT_BORDER     '*'     // Rectangle border
#define RECT_CENTER     ' '     // Rectangle center
#define SCALE_FACTOR    1.5f    // Scale factor for the rectangle length
#define PROGRAM_NUMBER  1       // Number of the program
#define COURSE_NUMBER   "CS246" // PCC assigned course number
#define COURSE_NAME     "Object-Oriented Programming and Design"
                                // Name of the course

//**********************************************************************
//*                         Program Structures                         *
//**********************************************************************
// Structure of dimensions
struct dimensions
{
   float area,      // Area of the rectangle
         length,    // Length of the rectangle
         perimeter, // Perimeter of the rectangle
         width;     // Width of the rectangle
};

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void print_heading();
   // Print the heading
void get_rect_dimensions(dimensions *p_rectangle);
   // Get the rectangle dimensions
void draw_rectangle(float f_length, float f_width);
   // Draw a rectangle
void show_specifications(dimensions rectangle);
   // Display the rectangle dimensions

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   dimensions rectangle; // Dimensions of a rectangle

   // Print the heading
   print_heading();

   // Get the dimensions of the rectangle
   get_rect_dimensions(&rectangle);

   // Draw the rectangle and show the dimensions of the rectangle
   draw_rectangle     (rectangle.length, rectangle.width);
   show_specifications(rectangle);

   // Display the good-bye message and terminate the program
   cout << "\n\nThanks for drawing a rectangle today ;)";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//**********************************************************************
//*                         Print the heading                          *
//**********************************************************************
void print_heading()
{
   cout << "\n\n\n\n\n\n        "    << COURSE_NUMBER
        << " "                       << COURSE_NAME
        << " - Program "             << PROGRAM_NUMBER;
   cout << "\n\n                     This program draws a rectangle";
   cout <<   "\n                     ==============================";
   return;
}

//**********************************************************************
//*                    Get the rectangle dimensions                    *
//**********************************************************************
void get_rect_dimensions(dimensions *p_rectangle)
{
   cout << "\n\n\nEnter the rectangle length now: ";
   cin  >> p_rectangle->length;
   cout <<       "Enter the rectangle width here: ";
   cin  >> p_rectangle->width;
   p_rectangle->area = (p_rectangle->length * p_rectangle->width);
   p_rectangle->perimeter
                     = (p_rectangle->length + p_rectangle->width) * 2.0f;
   return;
}

//**********************************************************************
//*                         Draw the rectangle                         *
//**********************************************************************
void draw_rectangle(float f_length, float f_width)
{
   int columns,  // Columns of the rectangle
       i_length, // Integer length of the rectangle
       i_width,  // Integer width of the rectangle
       rows;     // Rows of the rectangle
       
   if (f_length < MIN_RECT_LENGTH || f_width < MIN_RECT_WIDTH)
   {
      cout << "\nA "   << f_length
           <<   " by " << f_width
           <<   " rectangle is too small to draw.";
      cout << "\nIt must be at least size 1 by 1 (length by width).\n";
   }
   else
   {
      i_length  = int(f_length * SCALE_FACTOR);
      i_width   = int(f_width);

      cout << "\n\nHere is a picture of your rectangle:";

      cout << "\n";
      for (columns = 1; columns <= i_length; columns++)
         cout << RECT_BORDER;

      for (rows = 1; rows <= i_width - 2; rows++)
      {
         cout << "\n" << RECT_BORDER;
         for (columns = 1; columns <= i_length - 2; columns++)
            cout << RECT_CENTER;
         cout << RECT_BORDER;
      }

      if (i_width >= 2)
      {
         cout << "\n";
         for (columns = 1; columns <= i_length; columns++)
            cout << RECT_BORDER;
      }
   }
   return;
}

//**********************************************************************
//*                Show the dimensions of the rectangle                *
//**********************************************************************
void show_specifications(dimensions rectangle)
{
   cout << "\nThe rectangle specifications are:";
   cout << "\n        Length = " << rectangle.length    <<" units";
   cout << "\n         Width = " << rectangle.width     <<" units";
   cout << "\n          Area = " << rectangle.area      <<" sq. units";
   cout << "\n     Perimeter = " << rectangle.perimeter << " units";
   return;
}