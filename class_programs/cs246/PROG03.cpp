//**********************************************************************
//*                                                                    *
//* Program Name: PROG03 - Calculate and Draw a Picture of a Rectangle *
//* Author:       Damon L. Teichroeb                                   *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: February 18, 2020                                    *
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
//* This program asks for the length and width of a rectangle, then    *
//* draws a picture of the rectangle, and calculates and displays its  *
//* specifications.                                                    *
//*                                                                    *
//**********************************************************************

#include <iostream>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define MIN_RECT_LENGTH  1.0f    // Rectangle minimum length
#define MIN_RECT_WIDTH   1.0f    // Rectangle minimum width
#define RECTANGLE_BORDER '*'     // Rectangle border
#define RECTANGLE_CENTER ' '     // Rectangle center
#define SCALE_FACTOR     1.5f    // Rectangle length scale factor
#define PROGRAM_NUMBER   3       // Teacher assigned program number
#define COURSE_NUMBER    "CS246" // PCC assigned course number
#define COURSE_NAME      "Object-Oriented Programming and Design"
                                 // PCC assigned course name

//**********************************************************************
//*                          Program Classes                           *
//**********************************************************************
// The specifications of a rectangle
class rectangle
{
   float area,      // Area of the rectangle
         length,    // Length of the rectangle
         perimeter, // Perimeter of the rectangle
         width;     // Width of the rectangle
public:
   // Calculate the area and perimeter of the rectangle
        rectangle           (float user_length, float user_width);

   // Print the ending
        ~rectangle          ();

   // Draw a picture of the rectangle
   void draw_rectangle      ();

   // Show the rectangle specifications
   void print_specifications();

};

//**********************************************************************
//*         Calculate the area and perimeter of the rectangle          *
//**********************************************************************
rectangle::rectangle(float user_length, float user_width)
{
   length    = user_length;
   width     = user_width;
   area      = (length * width);
   perimeter = (length + width) * 2.0f;
}

//**********************************************************************
//*                          Print the ending                          *
//**********************************************************************
rectangle::~rectangle()
{
   cout << "\n\nThe rectangle object is being destructed now.";
}

//**********************************************************************
//*                  Draw a picture of the rectangle                   *
//**********************************************************************
void rectangle::draw_rectangle()
{
   int columns,  // Count the columns of the rectangle picture
       i_length, // Integer length of the rectangle
       i_width,  // Integer width of the rectangle
       rows;     // Count the rows of the rectangle picture

   // Check for minimum size length and width of the rectangle
   if (length < MIN_RECT_LENGTH || width < MIN_RECT_WIDTH)
   {
      cout << "\n\nA "                        << length
           << " by "                          << width
           << " rectangle is too small to draw.";
      cout <<   "\nIt must be at least size " << MIN_RECT_LENGTH
           << " by "                          << MIN_RECT_WIDTH
           << " (length by width).";
   }
   else
   {
      // Scale and convert the rectangle length and width
      i_length = int (length * SCALE_FACTOR);
      i_width  = int (width);

      // Print the rectangle picture title
      cout << "\n\nHere is a picture of your rectangle:";

      // Print the top part of the rectangle picture
      cout << "\n";
      for (columns = 1; columns <= i_length; columns++)
         cout << RECTANGLE_BORDER;

      // Print the center part of the rectangle picture
      for (rows = 1; rows <= i_width - 2; rows++)
      {
         cout << "\n" << RECTANGLE_BORDER;
         for (columns = 1; columns <= i_length - 2; columns++)
            cout << RECTANGLE_CENTER;
         cout << RECTANGLE_BORDER;
      }

      // Print the bottom part of the rectangle picture
      if (i_width >= 2)
      {
         cout << "\n";
         for (columns = 1; columns <= i_length; columns++)
            cout << RECTANGLE_BORDER;
      }
   }
   return;
}

//**********************************************************************
//*                 Print the rectangle specifications                 *
//**********************************************************************
void rectangle::print_specifications()
{
   cout << "\n\nThe rectangle specifications are:";
   cout <<   "\n        Length = "  << length    << " units";
   cout <<   "\n         Width = "  << width     << " units";
   cout <<   "\n          Area = "  << area      << " sq. units";
   cout <<   "\n     Perimeter = "  << perimeter << " units";
   return;
}

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void print_heading();
   // Print the heading
void get_dimensions(float *p_length, float *p_width);
   // Get the length and width of the rectangle

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   float user_length, // Length of the rectangle
         user_width;  // Width  of the rectangle

   // Print the heading
   cout << "\n\n\n\n\n\n";
   print_heading();

   // Get the length and width of the rectangle
   get_dimensions(&user_length, &user_width);

   // Create the rectangle and calculate the area and perimeter
   rectangle user_rectangle(user_length, user_width);

   // Draw a picture of the rectangle and print its specifications
   user_rectangle.draw_rectangle();
   user_rectangle.print_specifications();

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
   cout << "        "    << COURSE_NUMBER
        << " "           << COURSE_NAME
        << " - Program " << PROGRAM_NUMBER;
   cout << "\n\n                     This program draws a rectangle";
   cout <<   "\n                     ==============================";
   return;
}

//**********************************************************************
//*             Get the length and width of the rectangle              *
//**********************************************************************
void get_dimensions(float *p_length, float *p_width)
{
   cout << "\n\n\nEnter the rectangle length now: ";
   cin  >> *p_length;
   cout <<       "Enter the rectangle width here: ";
   cin  >> *p_width;
   return;
}