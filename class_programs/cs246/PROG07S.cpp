//**********************************************************************
//*                                                                    *
//* Program Name: PROG07S - Test for the presence of all required      *
//*                         money class overloaded operator and member *
//*                         functions in a money.h file.               *
//* Author:       CS246 Instructor                                     *
//* Installation: Pensacola Christian College, Pensacola, Florida      *
//* Course:       CS246, Object-Oriented Programming and Design        *
//* Date Written: January 2, 2008                                      *
//*                                                                    *
//**********************************************************************

//**********************************************************************
//*                                                                    *
//* This program tests to see if an included "money.h" file contains   *
//* all required money class overloaded operator and member functions. *
//* The "money.h" file being tested must be in this programs folder.   *
//* If this program runs correctly after compiling and linking, the    *
//* "money.h" file does contain all required money class overloaded    *
//* operator and member functions.                                     *
//* NOTE: This program DOES NOT test the correct execution of these    *
//*       overloaded operators and member functions.  It ONLY tests    *
//*       for their presence in the included "money.h" file.           *
//*                                                                    *
//**********************************************************************

#include <iostream>
#include "money.h"
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define COURSE_NAME     "Object-Oriented Programming and Design"
                                 // PCC assigned course name
#define COURSE_NUMBER   "CS246"  // PCC assigned course number
#define PROGRAM_NUMBER  "7S"     // Teacher assigned program number

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   // Print the program heading
   cout << "\n\n\n\n\n\n" << COURSE_NUMBER
      << " " << COURSE_NAME
      << " - Program " << PROGRAM_NUMBER;
   cout << "\n=========================================================";

   // Print the "complied and linked properly" message
   cout << "\n\n  Your money.h compiled and linked properly, indicating"
      << "\n  all required overloaded operator and member functions"
      << "\n  are present. However this DOES NOT mean the functions"
      << "\n  are working correctly.   YOU MUST completely test all"
      << "\n  your functions yourself, to ensure their reliability.";

   // Normal program termination
   cout << "\n\n\n\n\n\n";
   return 0;

   // The code which follows checks to see if all required money class
   // overloaded operator and member functions are present in the
   // included "money.h" file; note, none of this code is to be executed.

   // Test for the presence of the constructors
   money ob1,        // Uninitialized money object
      ob2(0.00f); // Initialized   money object

// Test for the presence of the set member functions
   ob1.set_dollars(0.00f);
   ob1.set_cents(0.00f);

   // Test for the presence of the get member function
   ob1.get_total();

   // Test for the presence of the overloaded operator functions
   ob1 = ob2;
   ob1 + ob2;
   ob1 - ob2;
   ob1* ob2;
   ob1 / ob2;
   ob1 += ob2;
   ob1 == ob2;
   ob1 != ob2;
   ob1 << 1;
   ob1 >> 1;
   ++ob1;
   ob1++;
}