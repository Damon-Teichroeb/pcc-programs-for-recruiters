/*************************************************************************
 CLASS INFORMATION                                    
 -----------------                                    
   Program Name: program05
   Programmer:   Damon Teichroeb
   Instructor:   Dr. Sparks for CS 214-1, C Programming
   Date Due:     03/6/2019

 DOCUMENTATION
 -------------
   This program creates a payroll earnings statement.
 ************************************************************************/
#include <stdio.h>
#include <math.h>

#define FEDERAL_TAX_RATE 0.25f
#define RETIREMENT_RATE  0.08f
#define STATE_TAX_RATE   0.1f

void printInstructions();
float getValue();
float calculateWithholding(float grossPay, float constant);
float calculateGrossPay(float sales, float bonus);
float calculateNetPay(float grossPay, float federalTax,
   float stateTax, float retirement);
void printResults(float sales, float bonus, float grossPay,
   float federalTax, float stateTax, float retirement, float netPay);

int main()
{
   float bonus,
         federalTax,
         grossPay,
         netPay,
         retirement,
         sales,
         stateTax;
	   
   printInstructions();   

   sales = getValue();
   bonus = getValue();

   grossPay   = calculateGrossPay(sales, bonus);
   federalTax = calculateWithholding(grossPay, FEDERAL_TAX_RATE);
   stateTax   = calculateWithholding(grossPay, STATE_TAX_RATE);
   retirement = calculateWithholding(grossPay, RETIREMENT_RATE);
   netPay     = calculateNetPay(grossPay,federalTax, stateTax, 
                                retirement);

   printResults(sales, bonus, grossPay, federalTax, stateTax, 
                retirement, netPay);

   return 0;
}

/********************
 Prints instructions.
*********************/
void printInstructions()
{
   printf("\n\n\n\nThis program will create ");
   printf("a payroll earnings statement.\n\n");
   printf("Please type in your sales and bonus ");
   printf("putting a space in between them:\n");

   return;
}

/***************************
 Recieves a value from user.
****************************/
float getValue()
{
   float money;
   scanf("%f", &money);

   return money;
}

/***********************************
 Calculates and returns witholdings.
************************************/
float calculateWithholding(float grossPay, float constant)
{
   return grossPay * constant;
}

/*********************************
 Calculates and returns gross pay.
**********************************/
float calculateGrossPay(float sales, float bonus)
{
   return sales + bonus;
}

/*******************
 Calculates net pay.
********************/
float calculateNetPay(float grossPay, float federalTax,
   float stateTax, float retirement)
{
   return grossPay - (federalTax + stateTax + retirement);
}

/*********************
 Displays the results.
**********************/
void printResults(float sales, float bonus, float grossPay,
   float federalTax, float stateTax, float retirement, float netPay)
{
   printf("\nSales amount:\t %9.2f", sales);
   printf("\nBonus:       +\t %9.2f", bonus);
   printf("\n\t     -------------");
   printf("\nGross Pay:   \t %9.2f", grossPay);
   printf("\nFederal Tax: \t %9.2f", federalTax);
   printf("\nState Tax:   \t %9.2f", stateTax);
   printf("\nRetirement:  \t %9.2f", retirement);
   printf("\n\t     -------------");
   printf("\nNet Pay:     \t %9.2f\n\n\n\n\n", netPay);

   return;
}
