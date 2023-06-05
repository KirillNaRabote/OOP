#include "BodyController.h"
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <map>

BodyController::BodyController(std::vector<std::shared_ptr<CBody>>& shapes, std::istream& input, std::ostream& output)
	: m_shapes(shapes)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Sphere", bind(&BodyController::CreateSphere, this, std::placeholders::_1)},
		{"Parallelepiped", bind(&BodyController::CreateParallelepiped, this, std::placeholders::_1)},
		{"Cone", bind(&BodyController::CreateCone, this, std::placeholders::_1)},
		{"Cylinder", bind(&BodyController::CreateCylinder, this, std::placeholders::_1)},
		{"Compound", bind(&BodyController::CreateCompound, this, std::placeholders::_1)}
		})
{
}

void BodyController::InitBodies()
{
	while (!m_input.eof() && !m_input.fail())
	{
		try
		{
			m_shapes.push_back(CreateBody());
		}
		catch (std::exception e)
		{
			m_output << e.what() << std::endl;
		}
	}

	ShowShapesInfo();
}

std::shared_ptr<CBody> BodyController::CreateBody()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	throw std::invalid_argument("Invalid shape type");
}

std::shared_ptr<CSphere> BodyController::CreateSphere(std::istream& args)
{
	double density, radius;
	args >> density >> radius;
	if (args.fail())
	{
		throw std::invalid_argument("Invalid arguments");
	}

	if (density <= 0)
	{
		throw std::invalid_argument("Density can't be negative or zero");
	}

	if (radius <= 0)
	{
		throw std::invalid_argument("Radius can't be negative or zero");
	}

	return std::shared_ptr<CSphere>(new CSphere(density, radius));
}

std::shared_ptr<CParallelepiped> BodyController::CreateParallelepiped(std::istream& args)
{
	double density, width, height, depth;
	args >> density >> width >> height >> depth;

	if (args.fail())
	{
		throw std::invalid_argument("Invalid arguments");
	}

	if (density <= 0)
	{
		throw std::invalid_argument("Density can't be negative or zero");
	}

	if (width <= 0)
	{
		throw std::invalid_argument("Width can't be negative or zero");
	}

	if (height <= 0)
	{
		throw std::invalid_argument("Height can't be negative or zero");
	}

	if (depth <= 0)
	{
		throw std::invalid_argument("Depth can't be negative or zero");
	}

	return std::shared_ptr<CParallelepiped>(new CParallelepiped(density, width, height, depth));
}

std::shared_ptr<CCone> BodyController::CreateCone(std::istream& args)
{
	double density, baseRadius, height;
	args >> density >> baseRadius >> height;

	if (args.fail())
	{
		throw std::invalid_argument("Invalid arguments");
	}

	if (density <= 0)
	{
		throw std::invalid_argument("Density can't be negative or zero");
	}

	if (baseRadius <= 0)
	{
		throw std::invalid_argument("Base radius can't be negative or zero");
	}

	if (height <= 0)
	{
		throw std::invalid_argument("Height can't be negative or zero");
	}

	return std::shared_ptr<CCone>(new CCone(density, baseRadius, height));
}

std::shared_ptr<CCylinder> BodyController::CreateCylinder(std::istream& args)
{
	double density, baseRadius, height;
	args >> density >> baseRadius >> height;

	if (args.fail())
	{
		throw std::invalid_argument("Invalid arguments");
	}

	if (density <= 0)
	{
		throw std::invalid_argument("Density can't be negative or zero");
	}

	if (baseRadius <= 0)
	{
		throw std::invalid_argument("Base radius can't be negative or zero");
	}

	if (height <= 0)
	{
		throw std::invalid_argument("Height can't be negative or zero");
	}

	return std::shared_ptr<CCylinder>(new CCylinder(density, baseRadius, height));
}

std::shared_ptr<CCompound> BodyController::CreateCompound(std::istream& args)
{
	std::shared_ptr<CCompound> compound(new CCompound);

	while (!args.eof())
	{
		std::string action;
		args >> action;

		auto it = m_actionMap.find(action);
		if (it->first == "Compound")
		{
			continue;
		}
		if (it != m_actionMap.end())
		{
			compound->AddChildBody(it->second(args));
		}
		else
		{
			throw std::invalid_argument("Invalid shape type");
		}
	}

	if (compound->GetMass() == 0)
	{
		throw std::invalid_argument("The compound body must contain shapes");
	}

	return compound;
}

void BodyController::ShowShapesInfo()
{
	for (const auto& shapePtr : m_shapes)
	{
		m_output << shapePtr->ToString() << std::endl;
	}
}

void BodyController::PrintBodyWithMaxMass()
{
	double maxMass = -1;
	std::shared_ptr<CBody> bodyWithMaxMassPtr = nullptr;

	for (const auto& body : m_shapes)
	{
		double bodyMass = body->GetMass();
		if (bodyMass > maxMass)
		{
			maxMass = bodyMass;
			bodyWithMaxMassPtr = body;
		}
	}

	if (bodyWithMaxMassPtr != nullptr)
	{
		m_output << "Body with max mass:" << std::endl << bodyWithMaxMassPtr->ToString();
	}
	else
	{
		m_output << "Missing bodies" << std::endl;
	}
}

void BodyController::PrintBodyWithLeastWeightInWater()
{
	double minForcesDifference = std::numeric_limits<double>::max();
	std::shared_ptr<CBody> bodyWithLeastWeightInWaterPtr = nullptr;

	for (const auto& bodyPtr : m_shapes)
	{
		const double bodyForcesDifference = (bodyPtr->GetDensity() - m_DENSITY_OF_WATER) * m_ACCELERATION_OF_FREE_FALL * bodyPtr->GetVolume();
		if (bodyForcesDifference < minForcesDifference)
		{
			minForcesDifference = bodyForcesDifference;
			bodyWithLeastWeightInWaterPtr = bodyPtr;
		}
	}

	if (bodyWithLeastWeightInWaterPtr != nullptr)
	{
		m_output << "A body with a minimum weight in water equal to " << minForcesDifference << ":" << std::endl
			<< bodyWithLeastWeightInWaterPtr->ToString();
	}
	else
	{
		m_output << "Missing bodies" << std::endl;
	}
}