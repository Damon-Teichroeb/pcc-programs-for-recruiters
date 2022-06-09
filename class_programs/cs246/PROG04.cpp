//**********************************************************************
//*                                                                    *
//* Program Name: PROG04 - Calculate the Specifications of             *
//*                        Straight-Sided Geometric Shapes             *
//* Author:       Damon L. Teichroeb                                   *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: March 5, 2020                                        *
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
//* This program calculates and prints the specifications of each      *
//* straight-sided geometric shape.                                    *
//*                                                                    *
//**********************************************************************

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define RT_ALLOC_ERROR       1       // Right triangle error number
#define SQUARE_ALLOC_ERROR   2       // Square error number
#define RECTANGLE_ALOC_ERROR 3       // Rectangle error number
#define PROGRAM_NUMBER       4       // Teacher assigned program number
#define COURSE_NUMBER        "CS246" // PCC assigned course number
#define COURSE_NAME          "Object-Oriented Programming and Design"
                                     // PCC assigned course name

//**********************************************************************
//*                          Program Classes                           *
//*                             Base Class                             *
//**********************************************************************
// The specifications of straight-sided geometric shapes
class geometric_shape
{
   float area,         // Area of a shape
         perimeter;    // Perimeter of a shape
   int   total_sides,  // Number of sides of a shape
         unique_sides; // Number of unique sides of a shape

public:
   // Print the specifications for straight-sided geometric shapes
   virtual void  show_shape      ()        {}

   // Set the data members
           void  set_area        (float a) {area         = a;}
           void  set_perimeter   (float p) {perimeter    = p;}
           void  set_total_sides (int   t) {total_sides  = t;}
           void  set_unique_sides(int   u) {unique_sides = u;}

   // Get the data members
           float get_area        ()        {return area;}
           float get_perimeter   ()        {return perimeter;}
           int   get_total_sides ()        {return total_sides;}
           int   get_unique_sides()        {return unique_sides;}

   // Print the memory allocation error
           void  fatal_error     (const char *p_preset_name,
                                  int error_number);
};

//**********************************************************************
//*                          Derived Classes                           *
//**********************************************************************
// The name and dimensions of a right triangle
class right_triangle: public geometric_shape
{
   char  *p_name;    // Point to a name for a right triangle
   float base,       // Base of a right triangle
         height,     // Height of a right triangle
         hypotenuse; // Hypotenuse of a right triangle
public:
   // Constructor, create a right triangle
        right_triangle (const char *p_preset_name,
                        float preset_base, float preset_height);
   // Destructor, delete a right triangle
        ~right_triangle() {free(p_name);}

   // Print the specifications of a right triangle
   void show_shape     ();
};

// The name and dimension of a square
class square: public geometric_shape
{
   char  *p_name; // Point to a name for a square
   float side;    // Side length of a square
public:
   // Constructor, create a square
        square    (const char *p_preset_name, float preset_side);

   // Destructor, delete a square
        ~square   () {free(p_name);}

   // Print the specifications of a square
   void show_shape();
};

// The name and dimensions of a rectangle
class rectangle: public geometric_shape
{
   char  *p_name; // Point to a name for a rectangle
   float base,    // Base of a rectangle
         height;  // Height of a rectangle
public:
   // Constructor, create a rectangle
         rectangle (const char *p_preset_name, float preset_base,
                    float preset_height);

   // Destructor, delete a rectangle
         ~rectangle() {free(p_name);}

   // Print the specifications of a rectangle
   void show_shape ();
};

//**********************************************************************
//*                 Print the memory allocation error                  *
//**********************************************************************
void geometric_shape::fatal_error(const char *p_preset_name,
                                  int error_number)
{
   cout << "\n\nError #" << error_number
        << " occurred in the constructor of a straight-sided"
        << " geometric shape.";
   cout <<   "\nCannot allocate memory for the name: "
        << "\""          << p_preset_name << "\"";
   cout <<   "\nThe program is aborting.";
   exit(error_number);
   return;
}

//**********************************************************************
//*                      Create a right triangle                       *
//**********************************************************************
right_triangle::right_triangle(const char *p_preset_name,
                               float preset_base, float preset_height)
{
   base       = preset_base;
   height     = preset_height;
   hypotenuse = sqrtf((base * base) + (height * height));

   cout << "\nCreating right triangle shape " << p_preset_name;
   cout << "\n     with base = "              << base
        <<      " and height = "              << height;

   if((p_name = (char *) malloc(strlen(p_preset_name) + 1)) == NULL)
      fatal_error(p_preset_name, RT_ALLOC_ERROR);
   else
      strcpy_s(p_name, strlen(p_preset_name) + 1, p_preset_name);

   set_area        (base * height * 0.5f);
   set_perimeter   (base + height + hypotenuse);
   set_total_sides (3);
   set_unique_sides(3);
}

//**********************************************************************
//*            Print the specifications of a right triangle            *
//**********************************************************************
void right_triangle::show_shape()
{
   cout << "\n\n\nThe specifications of a right triangle shape are:";
   cout <<     "\n-------------------------------------------------";
   cout <<     "\nName of the shape:         \"" << p_name << "\"";
   cout <<     "\nTotal number of sides:     "   << get_total_sides();
   cout <<     "\nNumber of unique sides:    "   << get_unique_sides();
   cout <<     "\nLength of base:            "   << base;
   cout <<     "\nLength of height:          "   << height;
   cout <<     "\nLength of hypotenuse:      "   << hypotenuse;
   cout <<     "\nArea:                      "   << get_area();
   cout <<     "\nPerimeter:                 "   << get_perimeter();
   return;
}

//**********************************************************************
//*                          Create a square                           *
//**********************************************************************
square::square(const char *p_preset_name, float preset_side)
{
   side = preset_side;

   cout << "\nCreating square shape " << p_preset_name;
   cout << "\n     with side = "      << side;

   if((p_name = (char *) malloc(strlen(p_preset_name) + 1)) == NULL)
      fatal_error(p_preset_name, SQUARE_ALLOC_ERROR);
   else
      strcpy_s(p_name, strlen(p_preset_name) + 1, p_preset_name);

   set_area        (side * side);
   set_perimeter   (side * 4.0f);
   set_total_sides (4);
   set_unique_sides(1);
}

//**********************************************************************
//*                Print the specifications of a square                *
//**********************************************************************
void square::show_shape()
{
   cout << "\n\n\nThe specifications of a square shape are:";
   cout <<     "\n-----------------------------------------";
   cout <<     "\nName of the shape:         \"" << p_name << "\"";
   cout <<     "\nTotal number of sides:     "   << get_total_sides();
   cout <<     "\nNumber of unique sides:    "   << get_unique_sides();
   cout <<     "\nLength of a side:          "   << side;
   cout <<     "\nArea:                      "   << get_area();
   cout <<     "\nPerimeter:                 "   << get_perimeter();
   return;
}

//**********************************************************************
//*                         Create a rectangle                         *
//**********************************************************************
rectangle::rectangle(const char *p_preset_name, float preset_base,
                     float preset_height)
{
   base   = preset_base;
   height = preset_height;

   cout << "\nCreating rectangle shape " << p_preset_name;
   cout << "\n     with base = "         << base
        <<      " and height = "         << height;

   if((p_name = (char *) malloc(strlen(p_preset_name) + 1)) == NULL)
      fatal_error(p_preset_name, RECTANGLE_ALOC_ERROR);
   else
      strcpy_s(p_name, strlen(p_preset_name) + 1, p_preset_name);

   set_area        (base * height);
   set_perimeter   ((base + height) * 2.0f);
   set_total_sides (4);
   set_unique_sides(2);
}

//**********************************************************************
//*               Print the specifications of a rectangle              *
//**********************************************************************
void rectangle::show_shape()
{
   cout << "\n\n\nThe specifications of a rectangle shape are:";
   cout <<     "\n--------------------------------------------";
   cout <<     "\nName of the shape:         \"" << p_name << "\"";
   cout <<     "\nTotal number of sides:     "   << get_total_sides();
   cout <<     "\nNumber of unique sides:    "   << get_unique_sides();
   cout <<     "\nLength of base:            "   << base;
   cout <<     "\nLength of height:          "   << height;
   cout <<     "\nArea:                      "   << get_area();
   cout <<     "\nPerimeter:                 "   << get_perimeter();
   return;
}

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
// Print the heading
void print_heading();

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   geometric_shape *p_shape; // Point to straight-sided geometric shapes

   // Print the heading
   cout << "\n\n\n\n\n\n";
   print_heading();

   // Create and calculate the dimensions of each straight-sided
   // geometric shape
   cout << "\n\n";
   right_triangle right_triangle_1("RIGHT-TRIANGLE-1", 5.99f, 11.99f);
   square         square_1        ("SQUARE-1", 11.99f);
   rectangle      rectangle_1     ("RECTANGLE-1", 11.99f, 5.99f);

   // Point to each straight-sided geometric shape and print their
   // specifications
   p_shape = &right_triangle_1;
   p_shape->show_shape();
   p_shape = &square_1;
   p_shape->show_shape();
   p_shape = &rectangle_1;
   p_shape->show_shape();

   // Print the good-bye message and terminate the program
   cout << "\n\n\nThanks for shaping things up today ;)";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//**********************************************************************
//*                         Print the heading                          *
//**********************************************************************
void print_heading()
{
   cout << "  "          << COURSE_NUMBER
        << " "           << COURSE_NAME
        << " - Program " << PROGRAM_NUMBER;
   cout << "\n\n   The specifications of straight-sided geometric shapes";
   cout <<   "\n   =====================================================";
   return;
}