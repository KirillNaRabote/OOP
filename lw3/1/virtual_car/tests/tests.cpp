#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../virtual_car/Car.h"

SCENARIO("The engine can be switched on or off")
{
	GIVEN("A turned off engine")
	{
		Car car;
		INFO("The engine must be initially turned off");
		REQUIRE(!car.IsTurnedOn());

		WHEN("The engine turns on")
		{
			car.TurnOnEngine();
			THEN("It's on")
			{
				REQUIRE(car.IsTurnedOn());
			}
		}
	}
}

SCENARIO("At each gear, it is possible to develop a speed within the range allotted to this gear.")
{
	GIVEN("A car with first gear engaged")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("Are you trying to gain more speed than for a given gear")
		{
			car.SetSpeed(31);
			THEN("The speed does not change")
			{
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("You are trying to gain the speed corresponding to this transmission")
		{
			car.SetSpeed(30);
			THEN("It's changing")
			{
				REQUIRE(car.GetSpeed() == 30);
			}
		}
	}

	GIVEN("A car with neutral gear engaged")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::NEUTRAL);

		WHEN("Trying to increase the speed")
		{
			car.SetSpeed(31);
			THEN("It doesn't change")
			{
				REQUIRE(car.GetSpeed() == 30);
			}
		}
		WHEN("Trying to reduce the speed")
		{
			car.SetSpeed(29);
			THEN("It's changing")
			{
				REQUIRE(car.GetSpeed() == 29);
			}
		}
	}
}

SCENARIO("When the engine is switched on, you can switch from any gear to any one,"
	"provided that the current speed of the car is in the speed range of the new gear,"
	"and the direction of movement of the car allows the inclusion of this gear.")
{
	GIVEN("A car with a neutral gear and with a backward speed of 10")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("Trying to reverse gear")
		{
			car.SetGear(Gear::REVERSE);
			THEN("It doesn't change")
			{
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
			}
		}
		WHEN("Stop and trying to reverse gear")
		{
			car.SetSpeed(0);
			car.SetGear(Gear::REVERSE);
			THEN("It's changing")
			{
				REQUIRE(car.GetGear() == Gear::REVERSE);
			}
		}
	}

	GIVEN("A car with reverse gear engaged, speed 10 and direction of movement backwards")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);

		WHEN("Trying to switch to first gear")
		{
			car.SetGear(Gear::FIRST);
			THEN("It doesn't change")
			{
				REQUIRE(car.GetGear() == Gear::REVERSE);
			}
		}

		WHEN("Stop and try to switch to first gear")
		{
			car.SetSpeed(0);
			car.SetGear(Gear::FIRST);
			THEN("It's changing")
			{
				REQUIRE(car.GetGear() == Gear::FIRST);
			}
		}
	}

	GIVEN("A car with neutral gear engaged, speed 10 and direction of movement backwards")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("Trying to switch to first gear")
		{
			car.SetGear(Gear::FIRST);
			THEN("It doesn't change")
			{
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
			}
		}

		WHEN("Stop and try to switch to first gear")
		{
			car.SetSpeed(0);
			car.SetGear(Gear::FIRST);
			THEN("It's changing")
			{
				REQUIRE(car.GetGear() == Gear::FIRST);
			}
		}
	}
}

SCENARIO("The engine of car can only be turned off at zero speed in neutral gear.")
{
	GIVEN("Car with non-zero speed and non-neutral gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(10);

		WHEN("Trying to turn off the engine")
		{
			car.TurnOffEngine();
			THEN("It doesn't change")
			{
				REQUIRE(car.IsTurnedOn());
			}
		}
	}
	GIVEN("Car with zero speed and neutral gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(0);

		WHEN("Trying to turn off the engine")
		{
			car.TurnOffEngine();
			THEN("It's changing")
			{
				REQUIRE(!car.IsTurnedOn());
			}
		}
	}
}

SCENARIO("When the engine is switched off, you can only switch to neutral gear.")
{
	GIVEN("Car with engine off")
	{
		Car car;
		WHEN("trying to switch to a non-neutral gear")
		{
			car.SetGear(Gear::FIRST);
			THEN("It doesn't change")
			{
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
			}
		}
	}
}