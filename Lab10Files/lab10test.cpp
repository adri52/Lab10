#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include"bank.h"
#include<iostream>
#include<queue>


using std::queue;


TEST_CASE("Functions")
{
	//CostumerGeneratior Function
	SECTION("nextMinute from CostumerGenerator")
	{
		FixedCG frontDoor(queue<int>({ 2 }), queue<int>({ 3 }));
		REQUIRE(frontDoor.nextMinute() == nullptr);
		REQUIRE(frontDoor.nextMinute() == nullptr);
		Customer * next = frontDoor.nextMinute();
		REQUIRE(next != nullptr);
		REQUIRE(next->helpTime == 3); 
		REQUIRE(frontDoor.nextMinute() == nullptr);


	}



	//*****************************************
	//Bank functions 

	SECTION("nextMin from Bank")
	{
		




	}


	SECTION("Simulate from Bank")
	{

	}
}
