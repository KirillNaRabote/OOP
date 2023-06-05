#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <map>
#include "CarControl.h"
#include "Car.h"

CarControl::CarControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{"Info", bind(&CarControl::Info, this, std::placeholders::_1)},
		{"EngineOn", bind(&CarControl::EngineOn, this, std::placeholders::_1)},
		{"EngineOff", bind(&CarControl::EngineOff, this, std::placeholders::_1)},
		{"SetGear", bind(&CarControl::SetGear, this, std::placeholders::_1)},
		{"SetSpeed", bind(&CarControl::SetSpeed, this, std::placeholders::_1)}
		})
{
}

bool CarControl::HandleCommand()
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

	return false;
}

bool CarControl::Info(std::istream& args)
{
	std::string info = "Engine is turned ";
	info += (m_car.IsTurnedOn())
		? "on"
		: "off";

	info += "\nDirection is ";
	switch (m_car.GetDirection())
	{
	case Direction::BACKWARD:
		info += "backward";
		break;
	case Direction::STOP:
		info += "stop";
		break;
	case Direction::FORWARD:
		info += "forward";
		break;
	}

	info += "\nSpeed is " + std::to_string(m_car.GetSpeed());

	info += "\nGear is " + std::to_string(static_cast<int>(m_car.GetGear()) - 1);

	m_output << info << std::endl;

	return true;
}

bool CarControl::EngineOn(std::istream& args)
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine is turned on" << std::endl;
		return true;
	}
	m_output << "The engine cannot be turned on" << std::endl;

	return false;
}

bool CarControl::EngineOff(std::istream& args)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine is turned off" << std::endl;
		return true;
	}
	m_output << "The engine cannot be turned off" << std::endl;

	return false;
}

bool CarControl::SetGear(std::istream& args)
{
	if (args.eof())
	{
		m_output << "After the command there should be a number" << std::endl;
		return false;
	}

	std::string str;
	args >> str;
	int gear = std::stoi(str);

	if (m_car.SetGear(static_cast<Gear>(gear + 1)))
	{
		m_output << "The gear is switched on " << gear << std::endl;
	}
	else
	{
		m_output << "The gear cannot be switched" << std::endl;
		return false;
	}

	return true;
}

bool CarControl::SetSpeed(std::istream& args)
{
	if (args.eof())
	{
		m_output << "After the command there should be a number" << std::endl;
		return false;
	}

	std::string str;
	args >> str;
	int speed = std::stoi(str);

	if (m_car.SetSpeed(speed))
	{
		m_output << "Speed changed to " << speed << std::endl;
	}
	else
	{
		m_output << "The speed cannot be changed" << std::endl;
		return false;
	}

	return true;
}