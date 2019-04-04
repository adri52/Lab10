#include<iostream>
#include<string>
#include<queue>
#include <random>
#include <ctime>
#include "bank.h" 

using namespace std; 

/*Write a main driver that simulates the sequence of events at the bank
(customers arriving, being helped, and leaving) over a work day, printing
out the events as they happen and finally reporting the maximum length of 
the queue during the day and the maximum wait time.*/

int main()
{
	int time;
	cout << "This program will be simulating the sequence id events at the bank" << endl;
	cout << "(customers arriving, being helped, and leaving) over a work day" << endl; 
	cout << "then it will report the amount of costumertss and what was the maximun wait time." << endl;

	//We get the data from the user to know the amount of minutes the bank will be running
	cout << "/n Enter how long the bank wll be open ";
	cin >> time; 
	

	Bank firstTest(time);
	firstTest.simulate();


}