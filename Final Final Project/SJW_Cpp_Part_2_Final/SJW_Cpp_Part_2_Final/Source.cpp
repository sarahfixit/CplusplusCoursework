/*
Sarah Wood
C++ Part 2
FINAL PROJECT

"Steward's Payroll Tools"

**********************************************
This program presumes 2016!!

(in order to use for other years
	*update holiday calendar
	*implement leap-year checking)
**********************************************

Other presumptions/places to improve:
	*One single time to start work for the whole crew (implement multiple start times - figure out elegant UI for that)
	*One contract
	*One Field Job ("Gig" "Call" "Show" In real life, this could be multiple days, but under the umbrella of one event.)
	*One day (Multiple day tracking provisioned, could be implemented on a per-employee or per-client basis)
	*Our workday is the first day of the Job. 


*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>	//raw time entry might come in a later release
#include <time.h>


#include "Employee.h"
#include "Structures.h"


using namespace std;

//structure declarations & definitions included in "structures.cpp"


//function prototypes


bool getContractData(EmployerContract);
bool getRatesData(EmployerJobPayRates);
void makeCrewList(Employee*);
void makeTimeSheet(Employee*);
void MANUALinputDailyWork(EmployerContract, EmployerJobPayRates*, Employee*);		//IRL contract 9.0x, pg 6-7
void FILEinputDailyWork(EmployerContract, EmployerJobPayRates*, Employee*);		//IRL contract 9.0x, pg 6-7
void calculateDailyTotalPayPerEmployee(Employee*, EmployerJobPayRates*);
void calculateTotalGrossForCrew(Employee*);
void outputFiguresPerEmployee(Employee*);
void contingentTotalGrossForCrew(Employee*); //"What if" function for management planning purposes

void testInput(Employee*, EmployerJobPayRates*);


//global variables

int day, month, hour, minute; //time-based hours are on the wishlist
const int SIZE = 10; //size of our labor Pool

double invoiceTotal;



EmployerContract GenericEmployerContract;	//conditions impacting pay
EmployerJobPayRates EmployerRatesArray[2] ;	//rates
//********************************************************************
//I ran into the "most vexing parse" problem in C++. I found it exceedingly difficult to overwrite my default constructor.
//I instead built an array, so that default could be [0], and my working data could be[1].
//I think I didn't run into this in the part 1 final project, because I was using my defaults as test data.
//********************************************************************

//instantiate a pool of crew to draw from
//note: (emp#, name, baseQual, baseQualShort = J, a1, a2, a3, H, Assignment)
//make an array of test Employees

Employee laborPool[SIZE] = {
	Employee(100, "Tex Avery", "Journeyman", "J", "Steward"),
	Employee(110, "Bugs Bunny", "Journeyman", "J", "Rigger"),
	Employee(160, "Porky Pig", "Journeyman", "J", "Head"),
	Employee(8010, "Daffy Duck", "Apprentice 3", "A3", "Grip"), 
	Employee(8120, "Elmer Fudd", "Apprentice 2", "A2", "Grip"), 
	Employee(10120, "Tweety Bird", "Hand", "H", "Grip"), 
	Employee(10130, "Sylvester Cat", "Hand", "H", "Grip"), 
	Employee(10210, "Yosemite Sam", "Hand", "H", "Grip"), 
	Employee(10310, "Gossamer", "Hand", "H", "Grip"),
	Employee(10440, "Marvin Martian", "Hand", "H", "Grip"), 

};

void main()
{
	//initialize console
	cout << "Steward's Payroll Tools" << '\n' << '\n';
	cout << "Your CREW LIST wil be generated." << '\n';
	cout << "For this release, your WORKSHEET has been filled out with test data." << '\n';


	//get CONTRACT data (rates & conditions), 

	
	getContractData(GenericEmployerContract);
	getRatesData(EmployerRatesArray[1]);

	

	//get CREW LIST
	//(I thought I may not need a crew list. However, it is a great worksheet onsite. It will be used to automate work input.)
	makeCrewList(laborPool);

	//manual input of daily work
	//MANUALinputDailyWork(GenericEmployerContract, EmployerRatesArray[1], laborPool);

	//file import of daily work -- CREW LIST filled out in spreadsheet editor with hours/shows worked
	FILEinputDailyWork(GenericEmployerContract, EmployerRatesArray, laborPool);


	//make TIME SHEET,

	makeTimeSheet(laborPool);
	
	//calculate total per day per employee
	calculateDailyTotalPayPerEmployee(laborPool, EmployerRatesArray);
	
	//calculate total gross wages invoiced
	calculateTotalGrossForCrew(laborPool);


	//output table of figures per employee
	outputFiguresPerEmployee(laborPool);

	//output total gross, based on contingencies
	contingentTotalGrossForCrew(laborPool);



	//testInput(laborPool, EmployerRatesArray);


	//Keep window open
	cout << "Press ENTER to close program." << endl;
	cin.ignore(256, '\n');
	cin.get();

}



bool getContractData(EmployerContract contract)
{

	//If we were working with multiple contracts, we could import the relevant one and send it into the appropriate structure.
	//As currently scoped, this is a single-contract program, but I am building it to be scalable in the future.
	fstream contractData;
	contractData.open("testContract.txt");

	if (contractData)
	{
		cout << "Contract file opened successfully." << '\n';
		contractData >> contract.EmployerName;
		contractData >> contract.EmployerShortName;
		contractData >> contract.FourHrMini;
		contractData >> contract.HrsBeforeMP;
		contractData >> contract.HrsBeforeOTdaily;
		contractData >> contract.HrsBeforeOTweekly;
		contractData >> contract.otherOTconditions;
		contractData >> contract.HrsBeforeDTdaily;
		contractData >> contract.otherDTconditions;
		contractData >> contract.MinHoursOffToAvoidTurnaroundPay;
		contractData >> contract.NumberOfContractualHolidays;
		contractData >> contract.HolidayRatePremium;
		for (int i = 1; i < 11; i++)
		{
			contractData >> contract.HolidayDateCodes2016[i];
		}
		return true;
	}
	else
	{
		cout << "Contract File Error." << '\n';
		return false;
	}

	

}

bool getRatesData(EmployerJobPayRates rates)
{
	ifstream ratesData;
	ratesData.open("testRates.txt");

	
	while (ratesData)
	{
		
		
		ratesData >> rates.MealPenaltyPercentageAsDec;
		ratesData >> rates.StewardRateHourly;
		ratesData >> rates.StewardRateShow;
		ratesData >> rates.RiggerRateHourly;
		ratesData >> rates.RiggerRateShow;
		ratesData >> rates.SpecialistRateHourly;
		ratesData >> rates.SpecialistRateShow;
		ratesData >> rates.HeadRateHourly;
		ratesData >> rates.HeadRateShow;
		ratesData >> rates.JourneymanRateHourly;
		ratesData >> rates.JourneymanRateShow;
		ratesData >> rates.ApprenticeRateHourly;
		ratesData >> rates.ApprenticeRateShow;
		ratesData >> rates.HandRateHourly;
		ratesData >> rates.HandRateShow;
		ratesData >> rates.ProgrammerRateHourly;
		ratesData >> rates.ProgrammerRateShow;

		cout << "Rates file opened successfully." << '\n';
		return true;
	}
	

	return false;
}

void MANUALinputDailyWork(EmployerContract contract, EmployerJobPayRates rates, Employee[])
{
	//logic gates for daily work 
	//(is straight hourly, OT, DT, SHOW pay, penalties? other?)
	//(dictated by CONTRACT data)

	for (int i = 0; i < SIZE; i++)
	{
		//declare local variables
		
		double number, number2, number3;
		double tempHours = 0, tempMPHours = 0;
		char  yesNo2;
		bool valid = false;
		/*
		//select a classification for [SELECTED EMPLOYEE]

		cout << '\n' << "Please select a job classification for " << laborPool[i].employeeName << " :" << '\n';
		cout << "1  Steward" << '\t' << "2 Rigger" << '\t' << "3 Specialist" << '\n';
		cout << "4  Head" << '\t' << '\t' << "5 Programmer" << '\t' << "6 Grip" << '\n';

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
			laborPool[i].setEmployeeApplicableRateHourly(rates.StewardRateHourly);
			laborPool[i].setEmployeeApplicableRateShow(rates.StewardRateShow);
		}
		else if (choice == 2)
		{
			laborPool[i].setEmployeeApplicableRateHourly(rates.RiggerRateHourly);
			laborPool[i].setEmployeeApplicableRateShow(rates.RiggerRateShow);
		}
		else if (choice == 3)
		{
			laborPool[i].setEmployeeApplicableRateHourly(rates.SpecialistRateHourly);
			laborPool[i].setEmployeeApplicableRateShow(rates.SpecialistRateShow);
		}
		else if (choice == 4)
		{
			laborPool[i].setEmployeeApplicableRateHourly(rates.HeadRateHourly);
			laborPool[i].setEmployeeApplicableRateShow(rates.HeadRateShow);
		}
		else if (choice == 5)
		{
			//this is where we use the base qualifications. 
			if (laborPool[i].employeeBaseQualificationSHORT == "J")
			{
				laborPool[i].setEmployeeApplicableRateHourly(rates.JourneymanRateHourly);
				laborPool[i].setEmployeeApplicableRateShow(rates.JourneymanRateShow);
			}
			else if (laborPool[i].employeeBaseQualificationSHORT == "A3" || laborPool[i].employeeBaseQualificationSHORT == "A2" || laborPool[i].employeeBaseQualificationSHORT == "A1")
			{
				laborPool[i].setEmployeeApplicableRateHourly(rates.ApprenticeRateHourly);
				laborPool[i].setEmployeeApplicableRateShow(rates.ApprenticeRateShow);
			}
			else if (laborPool[i].employeeBaseQualificationSHORT == "H")
			{
				laborPool[i].setEmployeeApplicableRateHourly(rates.HandRateHourly);
				laborPool[i].setEmployeeApplicableRateShow(rates.HandRateShow);
			}
			else
			{
				cout << "ERROR. Employee does not have a base qualification. Will be paid hand rate." << '\n';
				laborPool[i].setEmployeeApplicableRateHourly(rates.HandRateHourly);
				laborPool[i].setEmployeeApplicableRateShow(rates.HandRateShow);
			}

		}//close "choice == INT"

		*/
		cout << "Please enter the number of shows " << laborPool[i].employeeName << " worked today (0 if none): " << '\t';
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
		laborPool[i].setEmployeeDailyShows(number);



		//Hourly Work? get hours
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
				tempHours = number;
			}

			else if (number <= 5)
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
			cin >> number2;
			while (!cin)
			{
				cout << "Invalid Input. Try again. " << '\t';
				cin.clear();
				cin.ignore();
				cin >> number2;
			}
			if (number2 >6)
			{
				cout << "Did they really work " << number2 << " hours without a meal break? Y/N?";
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
					cin >> number2;
				}

			}
			//if >5, process Meal Penalty, if <2 make equal to 2 (industry standard is 2 hours pay after "lunch")
			if (number2 == 0)
			{
				tempHours += 0;
			}
			else if (number2>0 && number2 < 2)
			{
				number2 = 2;
				tempHours += number2;
			}

			else if (number2 <= 5)
			{

				tempHours += number2;
			}
			//if >5, process Meal Penalty, 
			else if (number2 >5)
			{

				tempHours += number2;
				tempMPHours += (number2 - 5);
			}

		
			cout << "Please enter the number of hours between CALLBACK and CUT: " << '\n';
			cout << "Enter 0 if none." << '\t';
			cin >> number3;
			while (!cin)
			{
				cout << "Invalid Input. Try again. " << '\t';
				cin.clear();
				cin.ignore();
				cin >> number3;
			}
			if (number3 >6)
			{
				cout << "Did they really work " << number3 << " hours without a meal break? Y/N?";
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
					cin >> number3;
				}

			}
			//if >5, process Meal Penalty, if <2 make equal to 2 (industry standard is 2 hours pay after "lunch")
			if (number3 == 0)
			{
				tempHours += 0;
			}
			else if (number3>0 && number3 < 2)
			{
				number3 = 2;

				tempHours += number3;
			}

			else if (number3 <=5)
			{

				tempHours += number3;
			}

			else if (number3 >5)
			{

				tempHours += number3;
				tempMPHours += (number3 - 5);

			}

			laborPool[i].setEmployeeDailyTotalHours(tempHours);


			//if total >8, process OT, if >12, process DT

			if (tempHours > 12)
			{
				laborPool[i].setEmployeeDailySTHours(8);
				laborPool[i].setEmployeeDailyOTHours(4);
				laborPool[i].setEmployeeDailyDTHours(tempHours - 12);
				laborPool[i].setEmployeeDailyMPHours(tempMPHours);
			}
			else if (tempHours>8)
			{
				laborPool[i].setEmployeeDailySTHours(8);
				laborPool[i].setEmployeeDailyOTHours(tempHours - 8);
				laborPool[i].setEmployeeDailyMPHours(tempMPHours);

			}
			else
			{
				laborPool[i].setEmployeeDailySTHours(tempHours);
				laborPool[i].setEmployeeDailyMPHours(tempMPHours);
			}

		
	

	}

}

void FILEinputDailyWork(EmployerContract contract, EmployerJobPayRates *rates, Employee[])
{
	double workTemp1, showsTemp, hours1Temp, hours2Temp, hours3Temp, tempMPHours=0;
	
	string tempAssignment;

	ifstream crewWorksheet;

	crewWorksheet.open("crewWorksheet.txt", ios::in);
	crewWorksheet.ignore(256, '\n'); //ignore the first line. It's only headers.

	for (int i = 0; i < SIZE ; i++)
	{
		//read from the worksheet
		crewWorksheet.ignore(20, '\t'); //ignore the first field (emp name)
		crewWorksheet.ignore(20, '\t'); //ignore the second field (emp#)
		
		crewWorksheet >>  tempAssignment>>showsTemp >> hours1Temp >> hours2Temp >> hours3Temp;

		


		//assign temp values read from worksheet to Employee object values
		laborPool[i].setEmployeeDailyShows(showsTemp);
		//workTemp1 = (hours1Temp + hours2Temp + hours3Temp);
		//laborPool[i].setEmployeeDailyTotalHours(workTemp1);
		
		
		//*********************************************************************************
		//Compute ST, OT, DT, MP
		if (hours1Temp <= 4)
		{
			//set to 4 hour minimum
			hours1Temp = 4;
			workTemp1 = hours1Temp;
		}

		else if (hours1Temp <= 5)
		{

			workTemp1 = hours1Temp;
		}
		//if >5, process Meal Penalty, 
		else if (hours1Temp >5)
		{
			workTemp1 = 5;
			tempMPHours = (hours1Temp - 5);
		}


		if (hours2Temp == 0)
		{
			workTemp1 += 0;
		}
		else if (hours2Temp>0 && hours2Temp < 2)
		{
			hours2Temp = 2;
			workTemp1 += hours2Temp;
		}

		else if (hours2Temp <= 5)
		{

			workTemp1 += 5;
		}
		//if >5, process Meal Penalty, 
		else if (hours2Temp >5)
		{

			workTemp1 += hours2Temp;
			tempMPHours += (hours2Temp - 5);
		}

		//if >5, process Meal Penalty, if <2 make equal to 2 (industry standard is 2 hours pay after "lunch")
		if (hours3Temp == 0)
		{
			workTemp1 += 0;
		}
		else if (hours3Temp>0 && hours3Temp < 2)
		{
			hours3Temp = 2;

			workTemp1 += hours3Temp;
		}

		else if (hours3Temp <= 5)
		{

			workTemp1 += hours3Temp;
		}

		else if (hours3Temp >5)
		{

			workTemp1 += hours3Temp;
			tempMPHours += (hours3Temp - 5);

		}

		laborPool[i].setEmployeeDailyTotalHours(workTemp1);


		//if total >8, process OT, if >12, process DT

		if (workTemp1 > 12)
		{
			laborPool[i].setEmployeeDailySTHours(8);
			laborPool[i].setEmployeeDailyOTHours(4);
			laborPool[i].setEmployeeDailyDTHours(workTemp1 - 12);
			laborPool[i].setEmployeeDailyMPHours(tempMPHours);
		}
		else if (workTemp1>8)
		{
			laborPool[i].setEmployeeDailySTHours(8);
			laborPool[i].setEmployeeDailyOTHours(workTemp1 - 8);
			laborPool[i].setEmployeeDailyMPHours(tempMPHours);

		}
		else
		{
			laborPool[i].setEmployeeDailySTHours(workTemp1);
			laborPool[i].setEmployeeDailyMPHours(tempMPHours);
		}

		
	}

}
void testInput(Employee *emp, EmployerJobPayRates *rates)
{
	cout<< '\n' << rates[1].MealPenaltyPercentageAsDec
		<< '\n' << rates[1].StewardRateHourly
		<< '\n' << rates[1].StewardRateShow
		<< '\n' << rates[1].RiggerRateHourly
		<< '\n' << rates[1].RiggerRateShow
		<< '\n' << rates[1].SpecialistRateHourly
		<< '\n' << rates[1].SpecialistRateShow
		<< '\n' << rates[1].HeadRateHourly
		<< '\n' << rates[1].HeadRateShow
		<< '\n' << rates[1].JourneymanRateHourly
		<< '\n' << rates[1].JourneymanRateShow
		<< '\n' << rates[1].ApprenticeRateHourly
		<< '\n' << rates[1].ApprenticeRateShow
		<< '\n' << rates[1].HandRateHourly
		<< '\n' << rates[1].HandRateShow
		<< '\n' << rates[1].ProgrammerRateHourly
		<< '\n' << rates[1].ProgrammerRateShow << '\n';

	for (int i = 0; i < SIZE; i++)
	cout << laborPool[i].getEmployeeName() << '\t' <<
		laborPool[i].getEmployeeNumber() << '\t' <<
		laborPool[i].getEmployeeDailyTotalHours() << '\t' <<
		laborPool[i].getEmployeeDailyShows() << '\t'<<
		laborPool[i].getEmployeeDailyAssignment()<< '\t'<<
		laborPool[i].getEmployeeApplicableHourlyRate()<<'\t'<<
		laborPool[i].getEmployeeApplicableShowRate()<<'\t'<<
		laborPool[i].getEmployeeDailyPayTotal()<<'\n';
}

void makeCrewList(Employee *emp)
{
	fstream crewList;
	crewList.open("crewList.txt", ios::out);
	cout << "Generating Crew List." << '\n';
	crewList << "Name" << '\t' << "#" << '\t'<<"Assignment"<<'\t' <<"Shows"<<'\t'<< "Hours1" << '\t' << "Hours2" << '\t' << "Hours3"<< '\n';
	for (int i = 0; i < SIZE; i++)
	{
		crewList << laborPool[i].getEmployeeName() << '\t' << laborPool[i].getEmployeeNumber() << '\t'<<laborPool[i].getEmployeeDailyAssignment()<<'\t'<<'\t'<<'\t'<<'\n';
	}
}
void makeTimeSheet(Employee *emp)
{
	ofstream timeSheet;
	timeSheet.open("timeSheet.txt", ios::out);
	cout << '\n' << "TIME SUMMARY" << '\n';
	cout << "Name" << '\t' << '\t' << "#" << '\t' << "ST" << '\t' << "OT" << '\t' << "DT" << '\t' << "MP" << '\t' << "Shows" <<'\n';
	timeSheet<< "Name" << '\t' << "#" << '\t' << "ST" << '\t' << "OT" << '\t' << "DT" << '\t' << "MP" << '\t' << "Shows" << '\n';

	for (int i = 0; i < SIZE; i++)
	{
		cout << laborPool[i].getEmployeeName() << '\t' <<
			laborPool[i].getEmployeeNumber() << '\t' <<
			laborPool[i].getEmployeeDailySTHours() << '\t' <<
			laborPool[i].getEmployeeDailyOTHours() << '\t' <<
			laborPool[i].getEmployeeDailyDTHours() << '\t' <<
			laborPool[i].getEmployeeDailyMPHours() << '\t' <<
			laborPool[i].getEmployeeDailyShows() << '\n';
		timeSheet << laborPool[i].getEmployeeName() << '\t' <<
			laborPool[i].getEmployeeNumber() << '\t' <<
			laborPool[i].getEmployeeDailySTHours() << '\t' <<
			laborPool[i].getEmployeeDailyOTHours() << '\t' <<
			laborPool[i].getEmployeeDailyDTHours() << '\t' <<
			laborPool[i].getEmployeeDailyMPHours() << '\t' <<
			laborPool[i].getEmployeeDailyShows() << '\n';
		
	}
}

void calculateDailyTotalPayPerEmployee(Employee *emp, EmployerJobPayRates *rates)
{
	double tempSTPay, tempOTPay, tempDTPay, tempMPPay, tempShowPay, tempTotalPay;
	double hourlyRate, showRate;
	string tempAssignment;

	for (int i = 0; i < SIZE; i++)
	{
		//Assign Rate to each JobClassification choice
		if (laborPool[i].employeeDailyAssignment == "Steward")
		{
			hourlyRate = rates[1].StewardRateHourly;
			showRate = rates[1].StewardRateShow;
			
		}
		else if (laborPool[i].employeeDailyAssignment == "Rigger")
		{
			hourlyRate = rates[1].RiggerRateHourly;
			showRate = rates[1].RiggerRateShow;
		}
		else if (laborPool[i].employeeDailyAssignment == "Specialist")
		{
			hourlyRate = rates[1].SpecialistRateHourly;
			showRate = rates[1].SpecialistRateShow;
		}
		else if (laborPool[i].employeeDailyAssignment == "Head")
		{
			hourlyRate = rates[1].HeadRateHourly;
			showRate = rates[1].HeadRateShow;
		}
		else if (laborPool[i].employeeDailyAssignment == "Grip")
		{
			//this is where we use the base qualifications. 
			if (laborPool[i].employeeBaseQualificationSHORT == "J")
			{
				hourlyRate = rates[1].JourneymanRateHourly;
				showRate = rates[1].JourneymanRateShow;
			}
			else if (laborPool[i].employeeBaseQualificationSHORT == "A3" || laborPool[i].employeeBaseQualificationSHORT == "A2" || laborPool[i].employeeBaseQualificationSHORT == "A1")
			{
				hourlyRate = rates[1].ApprenticeRateHourly;
				showRate = rates[1].ApprenticeRateShow;
			}
			else if (laborPool[i].employeeBaseQualificationSHORT == "H")
			{
				hourlyRate = rates[1].HandRateHourly;
				showRate = rates[1].HandRateShow;
			}
			else
			{
				cout << "ERROR. Employee does not have a base qualification. Will be paid hand rate." << '\n';
				hourlyRate = rates[1].HandRateHourly;
				showRate = rates[1].HandRateShow;
			}

		}
		//do math for pay
		tempSTPay = (hourlyRate * laborPool[i].employeeDailySTHours);
		tempOTPay = (1.5 * (hourlyRate * laborPool[i].employeeDailyOTHours));
		tempDTPay = (2 * (hourlyRate * laborPool[i].employeeDailyDTHours));
		tempMPPay = (2 * (hourlyRate * laborPool[i].employeeDailyMPHours));
		tempShowPay = (showRate * laborPool[i].employeeDailyShows);
		tempTotalPay = (tempSTPay + tempOTPay + tempDTPay + tempMPPay + tempShowPay);

		//store values in member variables
		laborPool[i].setEmployeeApplicableRateHourly(hourlyRate);
		laborPool[i].setEmployeeApplicableRateShow(showRate);
		laborPool[i].setEmployeeDailySTPay(tempSTPay);
		laborPool[i].setEmployeeDailyOTPay(tempOTPay);
		laborPool[i].setEmployeeDailyDTPay(tempDTPay);
		laborPool[i].setEmployeeDailyMPPay(tempMPPay);
		laborPool[i].setEmployeeDailyShowPay(tempShowPay);
		laborPool[i].setEmployeeDailyPayTotal(tempTotalPay);


	}


}

void calculateTotalGrossForCrew(Employee *emp)
{
	double tempAccumulator=0, tempEmployeeDaily;
	for (int i = 0; i < SIZE; i++)
	{
		tempEmployeeDaily = laborPool[i].employeeDailyTotalPay;
		tempAccumulator += tempEmployeeDaily;
	}

	cout << fixed << showpoint<<setprecision(2) << '\n';
	cout << "Daily Invoice Total is: $" << tempAccumulator << '\n';
	invoiceTotal = tempAccumulator;
}

void contingentTotalGrossForCrew(Employee *emp)
{
	double currentHourlyCost, tempInvoiceTotal, tempAccumulator=0;
	char yesNo;
	tempInvoiceTotal = invoiceTotal;

	cout << "Would you like to estimate costs if you keep the crew longer?" << '\n';
	cin >> yesNo;

	while (yesNo != 'Y' && yesNo != 'y' && yesNo != 'N' && yesNo != 'n')
	{
		cout << "Invalid Input. Try again." << '\t';
		cin.clear();
		cin.ignore();
		cin >> yesNo;
	}

	//note: the crew chief is the bellwether in this case, because they are the first one on the clock, and the last one off the clock
	//They have been "on" the longest, and will put in the most hours.


	if (yesNo == 'Y' || yesNo == 'y')
	{
		if (laborPool[0].employeeDailyOTHours > 0) //if the crew chief is in OT, base estimate on OT
		{
			//add up crew rate, *1.5, make that current hourly cost
			for (int i = 0; i < SIZE; i++)
			{
				tempAccumulator += laborPool[i].employeeApplicableRateHourly;
			}
			currentHourlyCost = (1.5 * tempAccumulator);
		}
		else if (laborPool[0].employeeDailyDTHours > 0)//if crew chief is in DT, base estimate on DT
		{
			//add up crew rate, *2.0, make that current hourly cost
			for (int i = 0; i < SIZE; i++)
			{
				tempAccumulator += laborPool[i].employeeApplicableRateHourly;
			}
			currentHourlyCost = (2 * tempAccumulator);
		}
		else //if crew chief in Straight Time, base estimate on Straight Time
		{
			for (int i = 0; i < SIZE; i++)
			{
				tempAccumulator += laborPool[i].employeeApplicableRateHourly;
			}
			currentHourlyCost = tempAccumulator;
		}

		cout << fixed << showpoint << setprecision(2) << '\n';
		cout << "Your crew costs about $" << currentHourlyCost << " for each additional hour." << '\n' <<
			"(Note, OT @ 8hours, DT @ 12hours.)" << '\n';
		cout << "FYI, your steward has been here for " << laborPool[0].employeeDailyTotalHours << " hours so far." <<'\n'<< '\n';

	}
}

void outputFiguresPerEmployee(Employee *emp)
{
	fstream payrollInvoice;
	payrollInvoice.open("testInvoice.txt", ios::out);

	//This is formatted to accomodate real payroll invoices used in the field.  
	//It will be tested with a real invoice that has been "scrubbed" of any confidential data.

	for (int i = 0; i < SIZE; i++)
	{
		payrollInvoice << laborPool[i].getEmployeeName() << '\t' <<
			laborPool[i].getEmployeeDailyAssignment() << '\t' <<
			laborPool[i].getEmployeeApplicableHourlyRate() << '\t' <<
			laborPool[i].getEmployeeDailySTHours() << '\t' <<
			laborPool[i].getEmployeeDailySTPay() << '\t' <<
			laborPool[i].getEmployeeDailyOTHours() << '\t' <<
			laborPool[i].getEmployeeDailyOTPay() << '\t' <<
			laborPool[i].getEmployeeDailyDTHours() << '\t' <<
			laborPool[i].getEmployeeDailyDTPay() << '\t' << '\t' <<
			laborPool[i].getEmployeeDailyShows() << '\t' <<
			laborPool[i].getEmployeeApplicableShowRate() << '\t' <<
			laborPool[i].getEmployeeDailyShowPay() << '\t' <<
			laborPool[i].getEmployeeDailyMPPay() << '\t' <<
			laborPool[i].getEmployeeDailyPayTotal() << '\n';
	}
		//output same values to screen
		//It was just too much to fit on console screen. Abridged accordingly.
		cout << "Name" << '\t'<<'\t' << "Assg" << '\t' << "Rate" << "  " << "Hours" << "  " << "#Shows" << "  " << "Show $" << '\t' << "Day $" << '\n';
		cout << resetiosflags(ios::fixed | ios::showpoint);
	for (int i = 0; i < SIZE; i++)
	{
		cout<< laborPool[i].getEmployeeName() << '\t' <<
			laborPool[i].getEmployeeDailyAssignment() << '\t'<<"$" <<
			laborPool[i].getEmployeeApplicableHourlyRate() << "   " <<
			laborPool[i].getEmployeeDailyTotalHours()<<"     "<<
			laborPool[i].getEmployeeDailyShows() << "       $" << fixed << showpoint << setprecision(2)<<
			laborPool[i].getEmployeeDailyShowPay() << "\t$" <<
			laborPool[i].getEmployeeDailyPayTotal() << resetiosflags(ios::fixed | ios::showpoint) << '\n';
	}




}