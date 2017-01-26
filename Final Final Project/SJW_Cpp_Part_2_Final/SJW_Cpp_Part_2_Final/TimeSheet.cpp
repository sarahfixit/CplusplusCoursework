#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "TimeSheet.h"
#include "Employee.h"

EmployeeList::~EmployeeList()
{
	IndivEmployeeNode *nodePtr; //traverse list
	IndivEmployeeNode *nextNode; 
		
	nodePtr = head;
	//while nodeptr is not at the end of the list
	while (nodePtr != nullptr)
	{
		//point to the next node
		nextNode = nodePtr->next;
		//delete current node
		delete nodePtr;
		//position nodePtr at next node
		nodePtr = nextNode;
	}
}

void EmployeeList::appendNode(Employee emp)
{
	IndivEmployeeNode *newNode;
	IndivEmployeeNode *nodePtr;

	//make a new node and store "num"

	newNode = new IndivEmployeeNode;
	newNode->assignedStageHand = emp;
	newNode->next = nullptr;

	//make newNode the first node if we have none.

	if (!head)
		head = newNode;
	else    //else, is end of list
	{
		//nodePtr to head of list
		nodePtr = head;

		//traverse to last in list

		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}

		//insert newNode as last node

		nodePtr->next = newNode;
	}	//close "else"
	
}

void EmployeeList::insertNode(Employee emp)
{
	IndivEmployeeNode *newNode; // A new node
	IndivEmployeeNode *nodePtr; // To traverse the list
	IndivEmployeeNode *previousNode = nullptr; // The previous node

									  // Allocate a new node and store num there.
	newNode = new IndivEmployeeNode;
	newNode->assignedStageHand = emp;

	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else // Otherwise, insert newNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose pointer value is less than emp.
		while (nodePtr != nullptr && nodePtr->assignedStageHand.employeeNumber < emp.employeeNumber)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}

}

void EmployeeList::deleteNode(Employee emp)
{
	IndivEmployeeNode *nodePtr; //traverse-r
	IndivEmployeeNode *previousNode; //point to previous node
	previousNode = head; //make the "previous" node point to something to start with

						 //if list empty, do nothing

	if (!head)
		return;

	//is the first node the one we need to delete?
	if (head->assignedStageHand.employeeNumber == emp.employeeNumber)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		//let's look for the node we want
		nodePtr = head;

		//skip the ones we don't want
		while (nodePtr != nullptr && nodePtr->assignedStageHand.employeeNumber != emp.employeeNumber)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		//if nodePtr is not end of list, link previous to node after "this one", then delete "this one"

		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}

	} //close else

}

void EmployeeList::displayList() const
{
	IndivEmployeeNode *nodePtr; //  move through the list

					   //NodePtr at the head of the list.
	nodePtr = head;


	//  traverse the list.
	while (nodePtr)
	{
		// Display the value in this node.
		cout << nodePtr->assignedStageHand.employeeName<<'\t'<<nodePtr->assignedStageHand.employeeNumber<<'\t'<<nodePtr->assignedStageHand.employeeBaseQualificationSHORT << endl;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}

}

int EmployeeList::search(Employee emp)
{
	int count = 0; //the node we're looking at
	IndivEmployeeNode *tempPtr;
	tempPtr = head;
	cout << '\n' << "Searching. Head of list is position 0." << '\n';


	while (tempPtr != NULL)
	{
		if (tempPtr->assignedStageHand.employeeNumber == emp.employeeNumber)
		{
			cout << '\n' << '\n' << tempPtr->assignedStageHand.employeeName<<"  "<<tempPtr->assignedStageHand.employeeNumber << " was found at position " << count << '\n';
			return tempPtr->assignedStageHand.employeeNumber;
		}

		count++;
		tempPtr = tempPtr->next;
	}

	return -1; //if we don't find it, return -1 as per spec

	
}
