#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Employee.h"
#include "Structures.h"


using namespace std;



//mutators & accessors for basic info

void Employee::setEmployeeNumber(int number)
{
	employeeNumber = number;
}

void Employee::setEmployeeName(string name)
{
	employeeName = name;
}

void Employee::setEmployeeQualification(string qual)
{
	employeeBaseQualification = qual;
}

void Employee::setEmployeeQualificationSHORT(string qualShort)
{
	employeeBaseQualificationSHORT = qualShort;
}

int Employee::getEmployeeNumber()
{
	return employeeNumber;
}

string Employee::getEmployeeName()
{
	return employeeName;
}

string Employee::getEmployeeQualification()
{
	return employeeBaseQualification;
}

string Employee::getEmployeeQualificationSHORT()
{
	return employeeBaseQualificationSHORT;
}



//Member functions related to hours
void Employee::setEmployeeDailyWork( EmployerContract contract, EmployerJobPayRates rates, Employee emp)
{
	//declare local variables
	int choice, number;
	double tempHours =0, tempMPHours=0;
	char  yesNo2;
	bool valid = false;

	//select a classification for [SELECTED EMPLOYEE]

			cout << '\n' << "Please select a job classification for "<<emp.employeeName<<" :" << '\n';
			cout << "1  Steward" << '\t' << "2 Rigger" << '\t'<<"3 Specialist"<<'\n';
			cout << "4  Head"<<'\t'<<'\t' << "5 Programmer" << '\t'<<"6 Grip"<<'\n';
			
			cout << "Please make a selection: " << '\t';
			cin >> choice;

			//validate user input
			while (!cin)
			{
				cout << "Invalid Input. Try again. Enter #1-6: " << '\t';
				cin.clear();
				cin.ignore();
				cin >> choice;
			}

			while (choice<1 || choice>6)
			{
				valid = !true;									//declare this attampt !valid
				cin.clear();									//clear the input stream
				cin.ignore();									//ignore invalid stuff.					
				cout << "Invalid input. Try again. Enter #1-6: " << '\t'; //user prompt
				cin >> choice;									//try again...
			}

	//Assign Rate to each JobClassification choice
			if (choice == 1)
			{
				emp.setEmployeeApplicableRateHourly(rates.StewardRateHourly);
				emp.setEmployeeApplicableRateShow(rates.StewardRateShow);
			}
			else if (choice == 2)
			{
				emp.setEmployeeApplicableRateHourly( rates.RiggerRateHourly);
				emp.setEmployeeApplicableRateShow ( rates.RiggerRateShow);
			}
			else if (choice == 3)
			{
				emp.setEmployeeApplicableRateHourly ( rates.SpecialistRateHourly);
				emp.setEmployeeApplicableRateShow ( rates.SpecialistRateShow);
			}
			else if (choice == 4)
			{
				emp.setEmployeeApplicableRateHourly ( rates.HeadRateHourly);
				emp.setEmployeeApplicableRateShow ( rates.HeadRateShow);
			}
			else if (choice == 5)
			{
				//this is where we use the base qualifications. 
				if (emp.employeeBaseQualificationSHORT == "J")
				{
					emp.setEmployeeApplicableRateHourly ( rates.JourneymanRateHourly);
					emp.setEmployeeApplicableRateShow ( rates.JourneymanRateShow);
				}
				else if (emp.employeeBaseQualificationSHORT == "A3" || emp.employeeBaseQualificationSHORT == "A2" || emp.employeeBaseQualificationSHORT == "A1")
				{
					emp.setEmployeeApplicableRateHourly ( rates.ApprenticeRateHourly);
					emp.setEmployeeApplicableRateShow ( rates.ApprenticeRateShow);
				}
				else if (emp.employeeBaseQualificationSHORT == "H")
				{
					emp.setEmployeeApplicableRateHourly(rates.HandRateHourly);
					emp.setEmployeeApplicableRateShow ( rates.HandRateShow);
				}
				else
				{
					cout << "ERROR. Employee does not have a base qualification. Will be paid hand rate." << '\n';
					emp.setEmployeeApplicableRateHourly(rates.HandRateHourly);
					emp.setEmployeeApplicableRateShow(rates.HandRateShow);
				}

			}//close "choice == INT"
			

			cout << "Please enter the number of shows "<<emp.employeeName<<" worked today (0 if none): " << '\t';
			cin >> number;
			//validate input. Max 3 shows/day before idiot-checking

			while (!cin)
			{
				valid = !true;
				cout << "Invalid Input. Try again." << '\t';
				cin.clear();
				cin.ignore();
				cin >> number;
			}
			if (number>3)
			{
				cout << "Did they really work " << number << " shows today? Y/N?";
				cin >> yesNo2;
				while (yesNo2 != 'Y' && yesNo2 != 'y' && yesNo2 != 'N' && yesNo2 != 'n')
				{
					cout << "Invalid Input. Y or N? " << '\t';
					cin.clear();
					cin.ignore();
					cin >> yesNo2;
				}

				if (yesNo2 == 'N' || yesNo2 == 'n')
				{
					cin.clear();
					cin.ignore();
					cout << "How many shows did they REALLY work?" << '\t';
					cin >> number;
					while (!cin)
					{
						cout << "Invalid Input. Try again." << '\t';
						cin.clear();
						cin.ignore();
						cin >> number;
					}
				}


			} //close idiot-check for number of shows worked
			emp.setEmployeeDailyShows(number);



//Hourly Work? YN, if Y, get hours
	cout << "Hourly work today? Y/N " << '\t';
	cin >> yesNo2;
	while (yesNo2 != 'Y' && yesNo2 != 'y' && yesNo2 != 'N' && yesNo2 != 'n')
			{
				cout << "Invalid Input. Y or N? " << '\t';
				cin.clear();
				cin.ignore();

				cin >> yesNo2;
			}

	if (yesNo2 == 'Y' || yesNo2 == 'y')					//yes, OK, more questions
		{


			cout << '\n' << "Please enter the number of hours between CALL TIME and FIRST meal break: " << '\n';
			cin >> number;

				while (!cin)
				{
					cout << "Invalid Input. Try again. " << '\t';
					cin.clear();
					cin.ignore();
					cin >> number;
				}
				if (number >6)
				{
					cout << '\n' << "Did they really work " << number << " hours without a meal break? Y/N?";
					cin >> yesNo2;
					while (yesNo2 != 'Y' && yesNo2 != 'y' && yesNo2 != 'N' && yesNo2 != 'n')
					{
						cout << "Invalid Input. Y or N? " << '\t';
						cin.clear();
						cin.ignore();
						cin >> yesNo2;
					}

					if (yesNo2 == 'N' || yesNo2 == 'n')
					{
						cin.clear();
						cin.ignore();
						cout << "How many hours did they REALLY work?" << '\t';
						cin >> number;
					}

				}
				//if <4 make equal to 4 (industry standard is 4 hour minimum)
				if (number <= 4)
				{
					number = 4;
					
					tempHours =  number;
				}

				else if (number = 5)
				{
					
					tempHours = number;
				}
				//if >5, process Meal Penalty, 
				else if (number >5)
				{
					
					tempHours = number;
					tempMPHours = (number - 5);
					
				}


				cout << "Please enter the number of hours between CALLBACK and SECOND meal break: " << '\n';
				cout << "Enter 0 if none." << '\t';
				cin >> number;
				while (!cin)
				{
					cout << "Invalid Input. Try again. " << '\t';
					cin.clear();
					cin.ignore();
					cin >> number;
				}
				if (number >6)
				{
					cout << "Did they really work " << number << " hours without a meal break? Y/N?";
					cin >> yesNo2;
					while (yesNo2 != 'Y' && yesNo2 != 'y' && yesNo2 != 'N' && yesNo2 != 'n')
					{
						cout << "Invalid Input. Y or N? " << '\t';
						cin.clear();
						cin.ignore();
						cin >> yesNo2;
					}

					if (yesNo2 == 'N' || yesNo2 == 'n')
					{
						cin.clear();
						cin.ignore();
						cout << "How many hours did they REALLY work?" << '\t';
						cin >> number;
					}

				}
				//if >5, process Meal Penalty, if <2 make equal to 2 (industry standard is 2 hours pay after "lunch")
				if (number < 2 )
				{
					number = 2;
					tempHours = number;
				}

				else if (number < 5)
				{
					
					tempHours = number;
				}
				//if >5, process Meal Penalty, 
				else if (number >5)
				{
					
					tempHours = number;
					tempMPHours = (number - 5);
				}


			cout << "Please enter the number of hours between CALLBACK and CUT: " << '\n';
				cout << "Enter 0 if none." << '\t';
				cin >> number;
				while (!cin)
				{
					cout << "Invalid Input. Try again. " << '\t';
					cin.clear();
					cin.ignore();
					cin >> number;
				}
				if (number >6)
				{
					cout << "Did they really work " << number << " hours without a meal break? Y/N?";
					cin >> yesNo2;
					while (yesNo2 != 'Y' && yesNo2 != 'y' && yesNo2 != 'N' && yesNo2 != 'n')
					{
						cout << "Invalid Input. Y or N? " << '\t';
						cin.clear();
						cin.ignore();
						cin >> yesNo2;
					}

					if (yesNo2 == 'N' || yesNo2 == 'n')
					{
						cin.clear();
						cin.ignore();
						cout << "How many hours did they REALLY work?" << '\t';
						cin >> number;
					}

				}
			//if >5, process Meal Penalty, if <2 make equal to 2 (industry standard is 2 hours pay after "lunch")
				if (number < 2)
				{
					number = 2;
					
					tempHours = number;
				}

				else if (number <5)
				{
					
					tempHours = number;
				}
				
				else if (number >5)
				{
					
					tempHours = number;
					tempMPHours = (number - 5);

				}
				
		emp.setEmployeeDailyTotalHours(tempHours);


				//if total >8, process OT, if >12, process DT

		if (emp.employeeDailyTotalHours > 12)
				{
					emp.setEmployeeDailySTHours(8);
					emp.setEmployeeDailyOTHours(4);
					emp.setEmployeeDailyDTHours  (tempHours - 12);
					emp.setEmployeeDailyMPHours(tempMPHours);
				}
		else if (emp.employeeDailyTotalHours>8)
				{
					emp.setEmployeeDailySTHours(8);
					emp.setEmployeeDailyOTHours (tempHours - 8);
					emp.setEmployeeDailyMPHours(tempMPHours);
				
				}
		else
				{
					emp.setEmployeeDailySTHours (tempHours);
					emp.setEmployeeDailyMPHours(tempMPHours);
				}

			} //close daily hourly input ( IF YES)
	else if (yesNo2 == 'n' || yesNo2 == 'N')
			cout << "No hourly pay today." << '\n';

		
}

void Employee::setEmployeeDailySTHours(double st)
{
	employeeDailySTHours = st;
}

void Employee::setEmployeeDailyOTHours(double ot)
{
	employeeDailyOTHours = ot;
}

void Employee::setEmployeeDailyDTHours(double dt)
{
	employeeDailyDTHours = dt;
}

void Employee::setEmployeeDailyMPHours(double mp)
{
	employeeDailyMPHours = mp;
}

void Employee::setEmployeeDailyShows(double shows)
{
	employeeDailyShows = shows;
}

void Employee::setEmployeeDailyTotalHours(double total)
{
	employeeDailyTotalHours = total;
}



double Employee::getEmployeeDailySTHours()
{
	return employeeDailySTHours;
}

double Employee::getEmployeeDailyOTHours()
{
	return employeeDailyOTHours;	
}

double Employee::getEmployeeDailyDTHours()
{
	return employeeDailyDTHours;
}

double Employee::getEmployeeDailyMPHours()
{
	return employeeDailyMPHours;
}

double Employee::getEmployeeDailyShows()
{
	return employeeDailyShows;
}

double Employee::getEmployeeDailyTotalHours()
{
	return employeeDailyTotalHours;
}



//member functions related to pay



void Employee::setEmployeeApplicableRateHourly(double hrRate)
{
	employeeApplicableRateHourly = hrRate;
}

void Employee::setEmployeeApplicableRateShow(double showRate)
{
	employeeApplicableRateShow = showRate;
}

void Employee::setEmployeeDailyAssignment(string assign)
{
	employeeDailyAssignment = assign;
	
}

void Employee::setEmployeeDailySTPay(double st)
{
	employeeDailySTPay = st;
}

void Employee::setEmployeeDailyOTPay(double ot)
{
	employeeDailyOTPay = ot;
}

void Employee::setEmployeeDailyDTPay(double dt)
{
	employeeDailyDTPay = dt;
}

void Employee::setEmployeeDailyMPPay(double mp)
{
	employeeDailyMPPay = mp;
}

void Employee::setEmployeeDailyShowPay(double showpay)
{
	employeeDailyShowPay = showpay;
}

void Employee::setEmployeeDailyOtherPay(double other)
{
	employeeDailyOtherPay = other;
}

void Employee::setEmployeeDailyPayTotal(double total)
{
	employeeDailyTotalPay = total;
}

double Employee::getEmployeeApplicableHourlyRate()
{
	return employeeApplicableRateHourly;
}

double Employee::getEmployeeApplicableShowRate()
{
	return employeeApplicableRateShow;
}

string Employee::getEmployeeDailyAssignment()
{
	return employeeDailyAssignment;
}

double Employee::getEmployeeDailySTPay()
{
	return employeeDailySTPay;
}

double Employee::getEmployeeDailyOTPay()
{
	return employeeDailyOTPay;
}

double Employee::getEmployeeDailyDTPay()
{
	return employeeDailyDTPay;
}

double Employee::getEmployeeDailyMPPay()
{
	return employeeDailyMPPay;
}

double Employee::getEmployeeDailyShowPay()
{
	return employeeDailyShowPay;
}

double Employee::getEmployeeDailyOtherPay()
{
	return employeeDailyOtherPay;
}

double Employee::getEmployeeDailyPayTotal()
{
	return employeeDailyTotalPay;
}

//destructor

Employee::~Employee()
{
}