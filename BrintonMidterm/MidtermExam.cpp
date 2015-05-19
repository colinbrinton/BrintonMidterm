/******************************************************************************
* Bellevue Class: PROG 113
*           Term: Spring 2015
*     Instructor: Robert Main
*
* Solution/Project Name: PROG113_MidtermExam
*             File Name: MidtermExam.cpp
*
* This file defines the entry point method, main(), for a C++ Console
* application. When the executable file is selected for execution, the OS
* will transfer execution to the first line of code in method main(). Other
* methods called from main() may be defined here as well.
*
* Programmer: Colin Brinton
*
* Revision     Date                        Release Comment
* --------  ----------  ------------------------------------------------------
*   1.0     05/18/2015  Initial Release
*
* File Methods
* ------------
*     Name                             Description
* ------------  --------------------------------------------------------------
* main          Program entry point method
*
* UDT Classes Utilized
* --------------------
*     Name                             Description
* ------------  --------------------------------------------------------------
* Mail          Base class: Common services for a mail item of any type
* Package       Sub-class:  Fixed cost, adds delivery days feature
*
* Program Inputs
* --------------
*  None
*
* Program Outputs
* ---------------
*   Stream Type                             Description
* ---------------  -----------------------------------------------------------
* Console Monitor  Display of various objects of type "Mail" and "Package"
*
******************************************************************************
*/
// External Definition files
// The first inclusion file MUST always be declared and MUST be first in the list
#include "stdafx.h"  // Defines IDE required external definition files
#include <iostream>  // Defines objects and classes used for stream I/O
#include <iomanip>   // Defines I/O Manipulators needed here

// Namespaces utilized in this program
using namespace std; // Announces to the compiler that members of the namespace
// "std" are utilized in this program

/******************************************************************************
* Class Name: Mail
* Base Class: None
*
* This file defines the members of the class: Mail
* These members include class variable data members, class constant, static
* data members, and class method declarations only and/or class method
* declarations and definitions.
*
* Class Description
* -----------------
* Allows for the creation of objects that hold information about the piece of
* mail to be shipped. Data members include the type of mail service, the weight
* in oz. of the mail item, and the shipping rate. Provides methods to store, display
* and modify objects.
*
* Class Data Members
* ------------------
*     Name        Scope     Type                   Description
* ------------  ---------  ------  --------------------------------------------
* TYPE_SIZE     private    char[]  Size of C-Style array: Mail Type    (static)
* FIRST_CLASS   private    char[]  C-Style string array: "First Class" (static)
* DFLT_COST     private    double  Default cost for Mail class, $0.49
* DFLT_WEIGHT   private    int	   Default weight for Mail class, 1 oz.
* type          private    char[]  Variable to hold the mail type string (First Class)
* perOunceCost  private	   double  Variable to hold the cost per ounce shipping rate ($0.49)
* weight		private	   int	   Variable to hold the object's weight in oz.
*
* Class Methods
* -------------
*           Name				Scope                   Description
* ----------------------		------  --------------------------------------------
* Mail()						public  Class Default Constructor: First Class, 1 oz
* Mail(char*,double,int)		public  Class Initializing Constructor
* Mail(const Mail&)				public  Class Copy Constructor
* ~Mail()						public  Class Destructor
* getCost()						public  RETurn total cost to mail item
* setType(char*, const char*)	public	Works like strncpy()
* printMail()					public	Prints the formatted information contained in the Mail variables
* operator=(const Mail&)		public  Assignment Operator
* operator+(int)				public  Addition Operator: Add ounces to item
* operator<<()					public  Insertion Operator: "string" description
*
******************************************************************************
*/
class Mail
{
	// Public Interface
public:
	// Class Constructor(s)
	Mail();
	Mail(const char* type, double perOunceCost, int weight);
	Mail(const Mail& other);

	// Class Destructor
	~Mail()
	{ }  // Nothing to do, included for completeness

	// Mutator Methods
	Mail operator=(const Mail& rValue);
	Mail operator+(int ounces);
	void setType(char* dest, const char* source);

	// Observer Methods
	double getCost() const;
	void printMail() const;
	friend ostream& operator<<(ostream& stream, const Mail letter);


private:
	// Class "static, const" Constant Values
	static const int TYPE_SIZE = 30;
	static const char FIRST_CLASS[];
	static const double DFLT_COST;
	static const int DFLT_WEIGHT = 1;

	// Variable Declarations
	char type[TYPE_SIZE];	// C-Style "string" array (Required!)
	double perOunceCost;
	int weight;

};

// Class "static, const" Value Declarations
// 1. Description of first class mail item
const char Mail::FIRST_CLASS[] = "First Class";
// 2. Default cost per ounce
const double Mail::DFLT_COST = 0.49;

// External methods

// Default Constructor
Mail::Mail()
{
	// Use default values to initialize variables
	setType(type, FIRST_CLASS);
	perOunceCost = DFLT_COST;
	weight = DFLT_WEIGHT;
}

// Initializing constructor
Mail::Mail(const char* type, double perOunceCost, int weight)
{
	setType(this->type, type);
	this->perOunceCost = perOunceCost;
	this->weight = weight;
}

// Copy Constructor
Mail::Mail(const Mail& other)
{
	setType(type, other.type);
	perOunceCost = other.perOunceCost;
	weight = other.weight;
}

//Return total cost to ship
double Mail::getCost() const
{
	if (perOunceCost >= NULL)
		return perOunceCost * weight;

	// Conditioned used by default in the fixed price Package class
	else
		return abs(perOunceCost);

}

// Method to print the Mail portion of the Package class
void Mail::printMail() const
{
	cout << "Mail Class: " << type << endl
		<< "Weight: " << weight << " oz." << endl
		<< showpoint << fixed << setprecision(2)
		<< "Total Cost: $" << getCost() << endl;
}

// Works identically to strncpy() - Visual studio will not allow for
//		use of strncpy without changing the default compiler behavior
void Mail::setType(char* dest, const char* source)
{
	// Copy source to dest
	int index = NULL;
	while (source[index] != '\0')
	{
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
}

// Overloaded assignment operator
Mail Mail::operator=(const Mail& rValue)
{
	Mail newMail;
	setType(newMail.type, rValue.type);
	newMail.perOunceCost = rValue.perOunceCost;
	newMail.weight = rValue.weight;
	return newMail;
}

// Overloaded addition operator
Mail Mail::operator+(int ounces)
{
	this->weight += ounces;
	return *this;
}

// Overloaded insertion operator
ostream& operator<<(ostream& stream, const Mail letter)
{
	stream << "Mail Class: " << letter.type << endl
		<< "Weight: " << (letter.weight) << " oz." << endl
		<< "Total Cost: $" << letter.getCost() << endl;

	return stream;
}
/******************************************************************************
* Class Name: Package
* Base Class: Mail
*
* This file defines the members of the class: Package
* These members include class variable data members, class constant, static
* data members, and class method declarations only and/or class method
* declarations and definitions.
*
* Class Description
* -----------------
* A specialized version of its base class, Mail. Defaults to using a fixed pricing system.
* (Shipping rates by oz. are still possible, but must be entered as negative doubles). Includes
* the addition of a shipping days data member and uses a modified insertion operator to reflect
* this.
*
* Class Data Members
* ------------------
* Name			  Scope    Type                     Description
* ----			--------- ------ ------------------------------------------------------
* EXPRESS_MAIL	 private  char[]  C-Style string array: "First Class" (static)
* days			 private  int	  Variable to store the number of shipping days
*
*
* Class Methods
* -------------
*           Name            Scope                   Description
* -----------------------  -------  ------------------------------------------
* Package(double,int,int)  public   Class Initializing Constructor
* Package(const Package&)  public   Class Copy Constructor
* ~Package()               public   Class Destructor
* operator<<()             public   Overloaded, friend Insertion Operator
*
******************************************************************************
*/
class Package : public Mail
{
	// Public Interface
public:
	// Class Constructor(s)
	Package(double cost, int weight, int days);
	Package(const Package&);

	// Class Destructor
	~Package()
	{ }  // Nothing to do, included for completeness

	// Mutator Methods
	// None

	// Observer Methods
	friend ostream& operator<<(ostream& stream, const Package package);

private:
	// Class static, "const" Constant Values
	static const char EXPRESS_MAIL[];

	// Variable Declarations
	int days;

};



// Class "static, const" Value Declarations
// 1. Description of first class mail item
const char Package::EXPRESS_MAIL[] = "Express Mail";

// External methods

// Initializing constructor
Package::Package(double cost, int weight, int days)
	: Mail(EXPRESS_MAIL, (-cost), weight)		 // Use Mail initializing constructor, pass cost as negative
{												 // so that fixed price behavior occurs
	//Initialize additional data member
	this->days = days;
}

// Copy Constructor
Package::Package(const Package& other)
	: Mail(other)  // Use Mail Copy Constructor
{
	// Copy the additional data member
	days = other.days;
}

// Overloaded insertion operator
ostream& operator<<(ostream& stream, const Package package)
{
	// Print Mail inherited data members
	package.printMail();
	// Print Package data member
	stream << "Delivery: " << package.days << " days" << endl;
	return stream;
}



/******************************************************************************
* Method: main()
*
* Method Description
* ------------------
* This Client program will test the various requirements for creating,"
* copying, adding an "int" value to an object, and assigning one object"
* to another object. The objects are of two types, 1) A base class,"
* "Mail", and 2) A derived class (sub-class), "Package".
*
* Method Arguments
* ----------------
* None
*
* Pre-Conditions
* --------------
* None
*
* Return Value (Post-Condition)
* -----------------------------
* Type                              Description
* ----  ---------------------------------------------------------------
* int   Program Status to OS: 0 - No errors
*
***************************************************************************
*/
int main()
{
	// Constant "const" Value Declaration
	const int ADDITIONAL_WEIGHT = 5;      // Ounces
	const double PACKAGE_COST = 7.50;     // Dollars
	const int PACKAGE_WEIGHT = 42;        // Ounces
	const int PACKAGE_DELIVERY_TIME = 3;  // Days

	// Initialized Variable Declarations
	// 1. A "Mail" object, default type (First class, 1 oz, @ .49 per ounce)
	Mail mailItem1;
	// 2. A copy of the default "Mail" object
	Mail mailItem2(mailItem1);
	// 3. An object of type "Package"
	Package package1(PACKAGE_COST, PACKAGE_WEIGHT, PACKAGE_DELIVERY_TIME);
	// 4. A copy of the "Package" object
	Package package2(package1);


	// Describe the program to the User
	cout << "                       PROG-113: Midterm Exam\n\n"
		<< "This Client program will test the various requirements for creating,"
		<< "\ncopying, adding an \"int\" value to an object, and assigning one object"
		<< "\nto another object. The objects are of two types, 1) A base class,"
		<< "\n\"Mail\", and 2) A derived class (sub-class), \"Package\".\n" << endl;


	// Test the Insertion Operator for class "Mail"
	cout << "\"mailItem1\":\n" << mailItem1 << endl;
	cout << "\n\"mailItem2\", a copy of \"mailItem1\":\n"
		<< mailItem2 << endl;

	// Test the Addition and Assignment Operators, class "Mail"
	mailItem1 = mailItem1 + ADDITIONAL_WEIGHT;
	cout << "\nAdding " << ADDITIONAL_WEIGHT << " oz. to weight of \"mailItem1\":\n"
		<< mailItem1 << endl;
	cout << "\n\"mailItem2\", AFTER adding weight to \"mailItem1\":\n"
		<< mailItem2 << endl;

	cout << "\n\"package1\":\n" << package1 << endl;

	cout << "\n\"package2\", a copy of \"package1\":\n" << package2 << endl;

	cout << "\nCost of \"mailItem1\": " << mailItem1.getCost() << endl;
	cout << "Cost of \"mailItem2\": " << mailItem2.getCost() << endl;
	cout << "Cost of \"package1\":  " << package1.getCost() << endl;



	// This prevents the Visual Studio Console Window from closing during
	// debug mode and allows you to select and copy the results displayed in
	// the Console window.
	cout << endl;  // Inserts a blank line before the prompt occurs
	system("pause");

	return 0;

}	// End method: main()

