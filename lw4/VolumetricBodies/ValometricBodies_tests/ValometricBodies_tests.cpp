#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../../catch2/catch.hpp"

#include "../VolumetricBodies/BodyController.h"
#include "../VolumetricBodies/CBody.h"
#include "../VolumetricBodies/CSphere.h"

SCENARIO("Incorrect input")
{
	GIVEN("Empty input")
	{
		std::istringstream strm;
		strm.setstate(std::ios_base::eofbit);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);
		BController.InitBodies();

		WHEN("Trying to find out the body with the largest mass and the smallest weight in the water")
		{
			BController.PrintBodyWithMaxMass();
			BController.PrintBodyWithLeastWeightInWater();

			THEN("It didn't work out, because there are no bodies")
			{
				REQUIRE(out.str() == "Missing bodies\nMissing bodies\n");
			}
		}
	}

	GIVEN("Input with missing number of arguments")
	{
		std::string commandLine = "Sphere 1";
		std::istringstream strm(commandLine);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);
		WHEN("Try to init bodies")
		{
			BController.InitBodies();

			THEN("The shape is not added and an error message is displayed")
			{
				REQUIRE(shapes.size() == 0);
				REQUIRE(out.str() == "Invalid arguments\n");
			}
		}
	}

	GIVEN("Input with incorrect figure")
	{
		std::string commandLine = "UnknownFigure 1";
		std::istringstream strm(commandLine);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);
		WHEN("Try to init bodies")
		{
			BController.InitBodies();

			THEN("The shape is not added and an error message is displayed")
			{
				REQUIRE(shapes.size() == 0);
				REQUIRE(out.str() == "Invalid shape type\n");
			}
		}
	}

	GIVEN("Input figure with density <= 0")
	{
		std::string commandLine = "Sphere -11 5";
		std::istringstream strm(commandLine);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);
		WHEN("Try to init bodies")
		{
			BController.InitBodies();

			THEN("The shape is not added and an error message is displayed")
			{
				REQUIRE(shapes.size() == 0);
				REQUIRE(out.str() == "Density can't be negative or zero\n");
			}
		}
	}
}

SCENARIO("Multiple bodies")
{
	GIVEN("Sphere, parallelepiped, cone, cylinder")
	{
		std::string commandLine = "Sphere 10 5\nParallelepiped 10 10 10 10\nCone 10 5 5\nCylinder 10 5 5";
		std::istringstream strm(commandLine);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);

		WHEN("Init bodies")
		{
			BController.InitBodies();
			THEN("The parallelepiped has a maximum mass and a minimum weight in water")
			{
				out.str("");
				out.clear();
				BController.PrintBodyWithMaxMass();
				REQUIRE(out.str() == "Body with max mass:\nParallelepiped:\n\tdensity = 10\n\tvolume = 1000\n\tmass = 10000\n\twidth = 10\n\theight = 10\n\tdepth = 10\n");

				out.str("");
				out.clear();
				BController.PrintBodyWithLeastWeightInWater();
				REQUIRE(out.str() == "A body with a minimum weight in water equal to -9.9e+06:\nParallelepiped:\n\tdensity = 10\n\tvolume = 1000\n\tmass = 10000\n\twidth = 10\n\theight = 10\n\tdepth = 10\n");
			}
		}
	}
}

SCENARIO("Input with compound bodies")
{
	GIVEN("Compound body without shapes")
	{
		std::string commandLine = "Compound";
		std::istringstream strm(commandLine);
		std::ostringstream out;
		std::vector<std::shared_ptr<CBody>> shapes;
		BodyController BController(shapes, strm, out);

		WHEN("Try to init")
		{
			BController.InitBodies();

			THEN("The shape is not added and an error message is displayed")
			{
				REQUIRE(shapes.size() == 0);
				REQUIRE(out.str() == "The compound body must contain shapes\n");
			}
		}
	}
}