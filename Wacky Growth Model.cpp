// Wacky Growth Model.cpp 
// Levi Seibert
// CS 372
// This program models the erratic growth of a new organism based on a wacky formula, based off of the Fibonacci sequence with a few changes

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//open the output file
ofstream outFile("Wacky Growth Results.txt");

//link list definition
class LList
{
public:
	int v;
	LList *next;
	LList *prev;
};

//global link list declaration
LList *head = NULL;

//function prototypes
LList * newNode();
void printLL(LList *current);
void insertNew(LList *current, int number);
void fibNext(LList *current);
LList * randomMove(LList *current, int &randNumber);
void replaceBack3(LList *current, LList *endNode);
void delList(LList *endNode);

//the newNode function returns a new node for the link list and sets the value to 0 and points next and prev to NULL
LList * newNode()
{
	LList *temp;
	temp = new LList;
	temp->v = 0;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

//the printLL function prints the link list to the output file
void printLL(LList *current)
{
	while (current)
	{
		outFile << current->v << " ";
		current = current->next;
	}
}

//the insertNew function inserts a new node (given a number to in isnert) into the link list.
void insertNew(LList *current, int number)
{
	//check if link list is empty
	if (head == NULL)
	{
		head = newNode();
		head->v = number;
	}

	//define previous and temporary and set to NULL
	LList *previous, *temporary;
	previous = NULL;
	temporary = NULL;

	//get to end of the list 
	while (current != NULL)
	{
		previous = current;
		current = current->next;
	}
	
	//if previous has moved, create a new node with its value set to number and its prev value pointed to previous
	if (previous != NULL)
	{
		temporary = newNode();
		temporary->v = number;
		previous->next = temporary;
		temporary->next = current;
		temporary->prev = previous;
	}

	//if not, create a new node with its value set to number and set head equal to the new node
	else
	{
		temporary = newNode();
		temporary->v = number;
		temporary->next = current;
		head = temporary;
	}
}

//the fibNext function calculates the next number in the Fibonacci sequence and inserts it to the end of the link list
void fibNext(LList *current)
{
	//define variables and set pointers equal to NULL
	int number;
	LList *previous = NULL, *back2 = NULL;

	//get to end of link list
	while (current)
	{
		previous = current;
		current = current->next;
	}

	//get 2 previous values, add together, and insert on end of the link list
	back2 = previous->prev;
	number = back2->v + previous->v;
	insertNew(head, number);
}

//the randomMove function picks a random node from the 5 previous nodes and returns the node equal to it
LList * randomMove(LList *current, int &randNumber)
{
	//calculate random number
	randNumber = (rand() % 5) + 1;

	//define pointers and set to NULL
	LList *previous = NULL, *back1 = NULL, *back2 = NULL, *back3 = NULL, *back4 = NULL, *endNode = NULL;

	//get to end of link list
	while (current)
	{
		previous = current;
		current = current->next;
	}

	//go back proper number of nodes based on the random number
	switch (randNumber)
	{
	case 1:
		endNode = previous->prev;
		break;
	case 2:
		back1 = previous->prev;
		endNode = back1->prev;
		break;
	case 3:
		back1 = previous->prev;
		back2 = back1->prev;
		endNode = back2->prev;
		break;
	case 4:
		back1 = previous->prev;
		back2 = back1->prev;
		back3 = back2->prev;
		endNode = back3->prev;
		break;
	case 5:
		back1 = previous->prev;
		back2 = back1->prev;
		back3 = back2->prev;
		back4 = back3->prev;
		endNode = back4->prev;
		break;
	}

	//return the endNode
	return endNode;
}

//the replaceBack3 function replaces the value in endNode with the value from 3 nodes back
void replaceBack3(LList *current, LList *endNode)
{
	//define pointers and set to NULL
	LList *previous = NULL, *back2 = NULL, *back3 = NULL;

	//get to endNode
	while (current != endNode)
	{
		previous = current;
		current = current->next;
	}

	//set the value in endNOde equal to the value in back3
	back2 = previous->prev;
	back3 = back2->prev;
	current->v = back3->v;
}

//the delList function deletes the nodes following endNode by simply setting endNode's next pointer to NULL
void delList(LList *endNode)
{
	endNode->next = NULL;
}

int main()
{
	//declare random number variable and link list end node
	int randNumber = 0;
	LList *endNode;

	//set the first two nodes of the link list
	insertNew(head, 2);
	insertNew(head, 2);

	//generate the next 13 weeks by the Fibonacci equation
	for (int i = 0; i < 13; i++)
		fibNext(head);

	//display header
	outFile << "Initial weeks:   (note: these are biological reandom numbers shown here)" << endl;

	//perform the given calcualtion 15 times
	for (int i = 0; i < 15; i++)
	{
		//randomly pick a node from one of the previous 5 nodes
		endNode = randomMove(head, randNumber);

		//print the link list, random number, and EndNode
		printLL(head);
		outFile << " random #: " << randNumber << "  (endNode is " << endNode->v << ")" << endl;

		//replace the value in endNode with the value from 3 nodes back
		replaceBack3(head, endNode);

		//delete the rest of the link list
		delList(endNode);

		//generate the next 4 weeks by the Fibonacci equation
		for (int i = 0; i < 4; i++)
			fibNext(head);
	}

	//close the output file
	outFile.close();
	return 0;
}