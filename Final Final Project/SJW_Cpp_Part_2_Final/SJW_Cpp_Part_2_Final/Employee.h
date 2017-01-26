#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>	//raw time entry might come in a later release
#include <time.h>


#include "Structures.h"


using namespace std;

//make an Employee class
//employee specialties may inherit from this class as needed
const int DAY = 32;

class Employee
{
protected:
		

public:
	int employeeNumber;
	string employeeName;
	string employeeBaseQualification;
	string employeeBaseQualificationSHORT;
	string employeeDailyAssignment;
	//we can add other qualifications as needed

	//employee time-related members
	double employeeDailySTHours;
	double employeeDailyOTHours;
	double employeeDailyDTHours;
	double employeeDailyMPHours;
	double employeeDailyShows;		
	double employeeDailyTotalHours;

	//employee pay-related members
	double employeeApplicableRateHourly;
	double employeeApplicableRateShow;
	
	double employeeDailySTPay;
	double employeeDailyOTPay;
	double employeeDailyDTPay;
	double employeeDailyMPPay;
	double employeeDailyShowPay;
	double employeeDailyOtherPay;
	double employeeDailyTotalPay;

	/* will track ongoing employee hours later
	(adapt from part 1 final project)
	double employeeDailySTHours[DAY];
	double employeeDailyOTHours[DAY];
	double employeeDailyDTHours[DAY];
	double employeeDailyMPHours[DAY];
	double employeeDailyShows[DAY];

	
	double employeeDailySTPay[DAY];
	double employeeDailyOTPay[DAY];
	double employeeDailyDTPay[DAY];
	double employeeDailyMPPay[DAY];
	double employeeDailyShowPay[DAY];
	double employeeDailyOtherPay[DAY];
	*/

	//default constructor 
	

	Employee()
	{
		employeeNumber = 99999;
		employeeName = " ";
		employeeBaseQualification = "Hand";
		employeeBaseQualificationSHORT = "H";
		employeeDailyAssignment = "Grip";

		//employee time-related members
		employeeDailySTHours = 0;
		employeeDailyOTHours = 0;
		employeeDailyDTHours = 0;
		employeeDailyMPHours = 0;
		employeeDailyShows = 0;
		employeeDailyTotalHours = 0;

		
		//employee pay-related members
		employeeApplicableRateHourly = 0;
		employeeApplicableRateShow = 0;
		
		employeeDailySTPay = 0;
		employeeDailyOTPay = 0;
		employeeDailyDTPay = 0;
		employeeDailyMPPay = 0;
		employeeDailyShowPay = 0;
		employeeDailyOtherPay = 0;
		employeeDailyTotalPay = 0;

		
		

		/* will track ongoing employee pay later
		(adapt from Part 1 final project)
		employeeDailySTHours[DAY] = {};
		employeeDailyOTHours[DAY] = {};
		employeeDailyDTHours[DAY] = {};
		employeeDailyMPHours[DAY] = {};
		employeeDailyShows[DAY] = {};

		employeeDailySTPay[DAY] = {};
		employeeDailySTPay[DAY] = {};
		employeeDailySTPay[DAY] = {};
		employeeDailySTPay[DAY] = {};
		employeeDailyShowPay[DAY] = {};
		employeeDailyOtherPay[DAY] = {};
		*/
	}

	//contructor
	Employee(int number, string name, string qualification, string shortQual, string assign)
	{
		employeeNumber = number;
		employeeName = name;
		employeeBaseQualification = qualification;
		employeeBaseQualificationSHORT = shortQual;
		employeeDailyAssignment = assign;
		

	}

	//mutators & accessors  for basic info
	void setEmployeeNumber(int);
	void setEmployeeName(string);
	void setEmployeeQualification(string);
	void setEmployeeQualificationSHORT(string);
	void setEmployeeDailyAssignment(string);
	

	int getEmployeeNumber();
	string getEmployeeName();
	string getEmployeeQualification();
	string getEmployeeQualificationSHORT();
	string getEmployeeDailyAssignment();

	//mutators & accessors for hours
	void setEmployeeDailyWork(EmployerContract, EmployerJobPayRates, Employee);
	void setEmployeeDailySTHours(double);
	void setEmployeeDailyOTHours(double);
	void setEmployeeDailyDTHours(double);
	void setEmployeeDailyMPHours(double);
	void setEmployeeDailyShows(double);
	void setEmployeeDailyTotalHours(double);

	double getEmployeeDailySTHours();
	double getEmployeeDailyOTHours();
	double getEmployeeDailyDTHours();
	double getEmployeeDailyMPHours();
	double getEmployeeDailyShows();
	double getEmployeeDailyTotalHours();

	//mutators & accessors for pay
	void setEmployeeApplicableRateHourly(double);
	void setEmployeeApplicableRateShow(double);
	
	void setEmployeeDailySTPay(double);
	void setEmployeeDailyOTPay(double);
	void setEmployeeDailyDTPay(double);
	void setEmployeeDailyMPPay(double);
	void setEmployeeDailyShowPay(double);
	void setEmployeeDailyOtherPay(double);
	void setEmployeeDailyPayTotal(double);

	double getEmployeeApplicableHourlyRate();
	double getEmployeeApplicableShowRate();
	
	double getEmployeeDailySTPay();
	double getEmployeeDailyOTPay();
	double getEmployeeDailyDTPay();
	double getEmployeeDailyMPPay();
	double getEmployeeDailyShowPay();
	double getEmployeeDailyOtherPay();
	double getEmployeeDailyPayTotal();

	//other member functions as needed

	//destructor declaration
	~Employee();

};












#endif // !EMPLOYEE_H
