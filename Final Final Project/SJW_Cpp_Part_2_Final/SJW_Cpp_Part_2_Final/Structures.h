#include <iostream>
#include <fstream>
#include <string>
#include <ctime>	//raw time entry might come in a later release
#include <time.h>




using namespace std;

/*	declare and define structures:
-Time & Date
-EmployerContract
-EmployerRates
-

*/

//structure declarations & default constructors




struct EmployerContract
{
	string EmployerName;
	string EmployerShortName;
	bool FourHrMini;				//Industry Standard is a four-hour minimum for all field assignments
	int HrsBeforeMP;				//Number of hours before Meal Penalty is incurred
	int HrsBeforeOTdaily;			//Number of daily hours before Overtime (time-and-a-half) is incurred
	int HrsBeforeOTweekly;			//Number of weekly hours before OT is incurred
	string otherOTconditions;		//Might there be any other condition that would incur Overtime(i.e., is Sunday OT on this contract?)
	int DaysOfWeekOTApplicable1;		//Days of the week that OT applies
	int DaysOfWeekOTApplicable2;		//Days of the week that OT applies
	int HrsBeforeDTdaily;			//Number of daily hours before Double Time is incurred	
	string otherDTconditions;		//Might there be any other condition that would incur Double Time (i.e., insufficient turnaround)
	int MinHoursOffToAvoidTurnaroundPay;
	int NumberOfContractualHolidays;
	int HolidayDateCodes2016[11];		//Jan 1 is day 1
	double HolidayRatePremium;	//1.5 base rate if OT on holiday, 2 if DT on holiday

	//Construct default values

	EmployerContract()
	{
		EmployerName = "default";
		EmployerShortName = "Def";
		FourHrMini = true;
		HrsBeforeMP = 5;
		HrsBeforeOTdaily = 8;
		HrsBeforeOTweekly = 40;
		otherOTconditions = "none";
		DaysOfWeekOTApplicable1 = 0;
		DaysOfWeekOTApplicable2 = 0;
		HrsBeforeDTdaily = 16;
		otherDTconditions = "none";
		MinHoursOffToAvoidTurnaroundPay = 8;
		NumberOfContractualHolidays = 0;
		HolidayRatePremium = 1.5;
		HolidayDateCodes2016[11] = 0;
		
	}
};
struct EmployerJobPayRates
{
	
	double MealPenaltyPercentageAsDec;  //Some Meal Penalties are a percentage added to hourly pay
	double StewardRateHourly;			//Job classifications for hourly and "Show Call" pay
	double StewardRateShow;
	double RiggerRateHourly;
	double RiggerRateShow;
	double SpecialistRateHourly;
	double SpecialistRateShow;
	double HeadRateHourly;
	double HeadRateShow;
	double JourneymanRateHourly;
	double JourneymanRateShow;
	double ApprenticeRateHourly;
	double ApprenticeRateShow;
	double HandRateHourly;
	double HandRateShow;
	double ProgrammerRateHourly;
	double ProgrammerRateShow;

	//construct defaults   
	EmployerJobPayRates()
	{
		
		MealPenaltyPercentageAsDec = 2;
		StewardRateHourly = 22;
		StewardRateShow = 110;
		RiggerRateHourly = 24;
		RiggerRateShow = 0;
		SpecialistRateHourly = 20;
		SpecialistRateShow = 95;
		HeadRateHourly = 19;
		HeadRateShow = 85;
		JourneymanRateHourly = 18;
		JourneymanRateShow = 80;
		ApprenticeRateHourly = 14;
		ApprenticeRateShow = 60;
		HandRateHourly = 12;
		HandRateShow = 50;
		ProgrammerRateHourly = 60;
		ProgrammerRateShow = 0;
		
	}
};

#pragma once
