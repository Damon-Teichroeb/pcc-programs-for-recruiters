//**********************************************************************
//*                                                                    *
//* Program Name: PROG05 - Calculate a Square To Circle Area Ratio     *
//* Author:       Damon L. Teichroeb                                   *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: March 17, 2020                                       *
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
//*  *
//*                                                                    *
//**********************************************************************

#include <iostream>
using namespace std;
class square;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define PI             3.141593f //
#define MIN_DIAMETER   0         //
#define QUIT_DIAMETER  0         //
#define PROGRAM_NUMBER 5         // Teacher assigned program number
#define COURSE_NUMBER  "CS246"   // PCC assigned course number
#define COURSE_NAME    "Object-Oriented Programming and Design"
                                 // PCC assigned course name

//**********************************************************************
//*                          Program Classes                           *
//**********************************************************************
// The specifications of a circle
class circle
{
   float area,
         circumference,
         diameter;
public:
   // Constructor, empty
                 circle           ()        {}

   // Constructor, set the diameter
                 circle           (float d) {diameter      = d;}

   // Set the members
          void   set_area         (float a) {area          = a;}
          void   set_circumference(float c) {circumference = c;}
          void   set_diameter     (float d) {diameter      = d;}

   // Get the members
          float  get_area         ()        {return area;}
          float  get_circumference()        {return circumference;}
          float  get_diameter     ()        {return diameter;}

   //
   friend square create_square    (circle circle);

   //
   friend float  area_ratio       (square square, circle circle);
};

// The specifications of a square
class square
{
   float area,
         perimeter,
         side;
public:
   // Constructor, empty
                 square       ()        {}

   // Constructor, set the side length
                 square       (float s) {side      = s;}

   // Set the members
          void   set_area     (float a) {area      = a;}
          void   set_perimeter(float p) {perimeter = p;}
          void   set_side     (float s) {side      = s;}

   // Get the members
          float  get_area     ()        {return area;}
          float  get_perimeter()        {return perimeter;}
          float  get_side     ()        {return side;}

   // Create the square specifications
          square create_square(circle circle);

   //
   friend float  area_ratio   (square square, circle circle);
};

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************

void print_heading();
   // Print the heading
float get_circle();
   // Get the diameter of a circle

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   // Print the heading
   cout << "\n\n\n\n\n\n";
   print_heading();



   // Print the good-bye message and terminate the program
   cout << "\n\n";
   cout << "\n  Goodbye, and I hope you learned something about the";
   cout << "\n ratio of the area of a square to the area of a circle,";
   cout << "\n where the perimeter of the square is exactly equal to";
   cout << "\n            the circumference of the circle.";
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
   cout << "\n        "
        << "========================================================";
   return;
}

//**********************************************************************
//*                    Get the diameter of a circle                    *
//**********************************************************************
float get_circle()
{
   float user_diameter = -1.0f;

   cout << "\n\n\nEnter a circle diameter greater than "
                                       << MIN_DIAMETER << " (or "
                                       << MIN_DIAMETER << " to quit): ";
   do
   {
      cin  >> user_diameter;
      cout << "     Invalid: diameter must be greater than "
                                       << MIN_DIAMETER << " (or "
                                       << MIN_DIAMETER << " to quit): ";
   }
   while (user_diameter < MIN_DIAMETER);
   return user_diameter;
}