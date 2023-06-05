#pragma once
#include <stdio.h>
#include <functional>

class Car;

class CarControl
{
public:
	CarControl(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();


private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	ActionMap m_actionMap;
};