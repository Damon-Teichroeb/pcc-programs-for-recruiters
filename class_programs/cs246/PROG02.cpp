//**********************************************************************
//*                                                                    *
//* Program Name: PROG02 - Calculate Geometric Shape Areas and Volume  *
//* Author:       Damon L. Teichroeb                                   *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: February 10, 2020                                    *
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
//* This program asks for their dimensions, then calculates and prints *
//* their areas and volume.                                            *
//*                                                                    *
//**********************************************************************

#include <iostream>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define PI             3.141593f // Mathematical constant pi
#define PROGRAM_NUMBER 2         // Teacher assigned program number
#define COURSE_NUMBER  "CS246"   // PCC assigned course number
#define COURSE_NAME    "Object-Oriented Programming and Design"
                                 // PCC assigned course name

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void print_heading();
   // Print the heading
void get_dimensions(float *p_length, float *p_width,
                    float *p_depth,  float *p_diameter);
   // Get the geometric shape dimensions
void shape_dimensions(float f_diameter);
   // Calculate and print the area of a circle
void shape_dimensions(float f_length, float f_width);
   // Calculate and print the area of a rectangle
void shape_dimensions(float f_length, float f_width, float f_depth);
   // Calculate and print the volume of a rectangular solid

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   float depth,    // Depth    of the rectangular solid
         diameter, // Diameter of the circle
         length,   // Length   of the rectangle and rectangular solid
         width;    // Width    of the rectangle and rectangular solid

   // Print the heading
   cout << "\n\n\n\n\n";
   print_heading();

   // Get the geometric shape dimensions
   get_dimensions(&length, &width, &depth, &diameter);

   // Calculate and display the geometric shape dimensions
   cout << "\n\nHere are the requested areas and volume:";
   cout << "\n----------------------------------------";
   shape_dimensions(diameter);
   shape_dimensions(length, width);
   shape_dimensions(length, width, depth);

   // Display the good-bye message and terminate the program
   cout << "\n\n\nThanks for calculating geometric shapes today ;)";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//**********************************************************************
//*                         Print the heading                          *
//**********************************************************************
void print_heading()
{
   cout << "\n"          << COURSE_NUMBER
        << " "           << COURSE_NAME
        << " - Program " << PROGRAM_NUMBER;
   cout << "\n========================================================";
   cout << "\n       Calculate geometric shape areas and volume";
   return;
}

//**********************************************************************
//*                 Get the geometric shape dimensions                 *
//**********************************************************************
void get_dimensions(float *p_length, float *p_width,
                    float *p_depth,  float *p_diameter)
{
   cout << "\n\n\nEnter the geometric shape dimensions as follows:";
   cout <<     "\n    Circle diameter: ";
   cin  >> *p_diameter;
   cout <<       "   Rectangle length: ";
   cin  >> *p_length;
   cout <<       "    Rectangle width: ";
   cin  >> *p_width;
   cout <<       "    Rectangle depth: ";
   cin  >> *p_depth;
   return;
}

//**********************************************************************
//*                   Calculate the area of a circle                   *
//**********************************************************************
void shape_dimensions(float f_diameter)
{
   cout <<   "\nArea of a circle with diameter "
                     << f_diameter << ":";
   cout <<   "\n   " << 0.25f * PI * f_diameter * f_diameter
        << " square units";
   return;
}

//**********************************************************************
//*                 Calculate the area of a rectangle                  *
//**********************************************************************
void shape_dimensions(float f_length, float f_width)
{
   cout << "\nArea of a rectangle of length "
                   << f_length             << " by width "
                   << f_width              << ":";
   cout << "\n   " << (f_length * f_width) << " square units";
   return;
}

//**********************************************************************
//*            Calculate the volume of a rectangular solid             *
//**********************************************************************
void shape_dimensions(float f_length, float f_width, float f_depth)
{
   cout << "\nVolume of a rectangular solid of length "
                      << f_length 
        << ", width " << f_width
        << ", depth " << f_depth                        << ":";
   cout << "\n   "    << (f_length * f_width * f_depth) << " cubic units";
   return;
}