#define CATCH_CONFIG_MAIN

#include "../../../../catch2/catch.hpp"

#include "../vector/AddToEach.h"
#include "../vector/FillVector.h"
#include "../vector/Print.h"

SCENARIO("Adding to an empty vector returns an empty vector")
{
	GIVEN("An empty vector")
	{
		std::vector<double> vector;
		std::vector<double> resultVector;
		WHEN("Adding")
		{
			AddArithmeticMeanOfPositiveNumbers(vector);

			THEN("Empty == empty")
			{
				REQUIRE(vector == resultVector);
			}
		}
	}
}

SCENARIO("Adding to a vector consisting of zeros")
{
	GIVEN("A vector consisting of zeros")
	{
		std::vector<double> vector = { 0, 0, 0, 0 };
		std::vector<double> resultVector = { 0, 0, 0, 0 };
		WHEN("Adding")
		{
			AddArithmeticMeanOfPositiveNumbers(vector);

			THEN("{ 0, 0, 0, 0 } = { 0, 0, 0, 0 }")
			{
				REQUIRE(vector == resultVector);
			}
		}
	}
}

SCENARIO("Adding to a vector consisting of negative numbers")
{
	GIVEN("A vector consisting of negative numbers")
	{
		std::vector<double> vector = { -1, -2, -3 };
		std::vector<double> resultVector = { -1, -2, -3 };
		WHEN("Adding")
		{
			AddArithmeticMeanOfPositiveNumbers(vector);

			THEN("{ -1, -2, -3 } = { -1, -2, -3 }")
			{
				REQUIRE(vector == resultVector);
			}
		}
	}
}

SCENARIO("Adding to a vector consisting of negative and positive numbers")
{
	GIVEN("A vector consisting of negative and positive numbers")
	{
		std::vector<double> vector = { -1, 2, -3 };
		std::vector<double> resultVector = { 1, 4, -1 };
		WHEN("Adding")
		{
			AddArithmeticMeanOfPositiveNumbers(vector);

			THEN("{ -1, -2, -3 } -> { 1, 4, -1 }")
			{
				REQUIRE(vector == resultVector);
			}
		}
	}
}

SCENARIO("Adding to a vector consisting of positive numbers")
{
	GIVEN("A vector consisting of positive numbers")
	{
		std::vector<double> vector = { 1, 2, 1 };
		std::vector<double> resultVector = { 1 + 4.0 / 3.0, 2 + 4.0 / 3.0, 1 + 4.0 / 3.0 };
		WHEN("Adding")
		{
			AddArithmeticMeanOfPositiveNumbers(vector);

			THEN("{ 1, 1, 2 } -> { 2.(3), 3.(3), 2.(3) }")
			{
				REQUIRE(vector == resultVector);
			}
		}
	}
}

SCENARIO("Filling a vector")
{
	WHEN("input stream is empty")
	{
		std::istringstream input("");
		std::vector<double> vector = FillVectorWithNumbers(input);
		std::vector<double> resultVector;

		THEN("vector is empty")
		{
			REQUIRE(vector == resultVector);
		}
	}

	WHEN("input stream contains values")
	{
		std::istringstream input("0 1 2");
		std::vector<double> vector = FillVectorWithNumbers(input);
		std::vector<double> resultVector = { 0, 1, 2 };

		THEN("vector = { 0, 1, 2 }")
		{
			REQUIRE(vector == resultVector);
		}
	}
}

SCENARIO("Output vector")
{
	std::ostringstream output;

	WHEN("vector is empty")
	{
		std::vector<double> vector;

		PrintVector(output, vector);

		THEN("output = """)
		{
			REQUIRE(output.str() == "");
		}
	}

	WHEN("vector is not empty")
	{
		std::vector<double> vector = { 5, -3, 10 };

		PrintVector(output, vector);

		THEN("output = 5, -3, 10 \n")
		{
			REQUIRE(output.str() == "5 -3 10 \n");
		}
	}
}