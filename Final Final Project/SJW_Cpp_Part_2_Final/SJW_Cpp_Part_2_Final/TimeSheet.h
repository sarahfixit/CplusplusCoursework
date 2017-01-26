#include <iostream>
#include <fstream>
#include <string>
#include <ctime>	//raw time entry might come in a later release
#include <time.h>


#include "Employee.h"



using namespace std;

class EmployeeList
{
private:
	struct IndivEmployeeNode
	{
		Employee assignedStageHand;
		struct IndivEmployeeNode *next;
	};
	IndivEmployeeNode *head;

public:
	//constructor, head pts to NULL
	EmployeeList()
	{
		head = nullptr;
	}

	//destructor
	~EmployeeList();

	//operations
	void appendNode(Employee);
	void insertNode(Employee);
	void deleteNode(Employee);
	void displayList() const;
	int search(Employee);

};