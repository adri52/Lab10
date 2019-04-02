#ifndef BANK_H
#define BANK_H
#include<iostream>
#include<string>
#include<queue>



struct Customer
{
	//record the time when the customer arrived in line
	int arrivalTime=0; //in minutes
	//keeps track of how many more minutes of help that customer will require.
	int helpTime=0; 

};




//It represents the stream of customers arriving at the front door of the bank 
class CustomerGenerator
{
private: 
	// it indicates the number of minutes left before the next customer
	int remainingTime =0; 

public:
	// It decrements the number of minutes left  till the next customer
	Customer* nextMinute();



	
};


 

class Bank
{
private: 
	int workDay; //in minutes 
	int timeSinceBO; //in minutes 
	Customer * cur; //a pointer to a current Customer being helped (or null if none is being helped)
	std::queue<Customer*> cosLine; 
	CustomerGenerator frontDoor;  //a reference to a CustomerGenerator object
	int costumerCount;  //integer tracking the maximum queue length seen during the day
	int maxWTime;  //integer tracking the maximum wait time

public:
	Bank(const int & workDayLength ); //give a work dy length 
	void nextMin();
	void simulate(); //loop over minutes and work day 
};









#endif // !BANK_H
