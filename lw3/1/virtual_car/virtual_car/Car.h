#pragma once
#include <map>

//спрятать в приватную часть класса, если это не нужно в других файлах
const int MIN_SPEED = 0;
const int MAX_SPEED = 150;
const int REVERSE_GEAR_MIN_SPEED = MIN_SPEED;
const int REVERSE_GEAR_MAX_SPEED = 20;
const int NEUTRAL_GEAR_MIN_SPEED = MIN_SPEED;
const int NEUTRAL_GEAR_MAX_SPEED = MAX_SPEED;
const int FIRST_GEAR_MIN_SPEED = MIN_SPEED;
const int FIRST_GEAR_MAX_SPEED = 30;
const int SECOND_GEAR_MIN_SPEED = 20;
const int SECOND_GEAR_MAX_SPEED = 50;
const int THIRD_GEAR_MIN_SPEED = 30;
const int THIRD_GEAR_MAX_SPEED = 60;
const int FOURTH_GEAR_MIN_SPEED = 40;
const int FOURTH_GEAR_MAX_SPEED = 90;
const int FIFTH_GEAR_MIN_SPEED = 50;
const int FIFTH_GEAR_MAX_SPEED = 150;

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

enum class Gear
{//можно значениям присвоить целочисленные значения
	REVERSE,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

enum class Direction
{
	BACKWARD,
	STOP,
	FORWARD
};

using SpeedInterval = std::pair<int, int>;
using GearSpeedInterval = std::map<Gear, SpeedInterval>;

const GearSpeedInterval gearSpeedInterval = {
	{Gear::REVERSE, {REVERSE_GEAR_MIN_SPEED, REVERSE_GEAR_MAX_SPEED}},
	{Gear::NEUTRAL, {NEUTRAL_GEAR_MIN_SPEED, NEUTRAL_GEAR_MAX_SPEED}},
	{Gear::FIRST, {FIRST_GEAR_MIN_SPEED, FIRST_GEAR_MAX_SPEED}},
	{Gear::SECOND, {SECOND_GEAR_MIN_SPEED, SECOND_GEAR_MAX_SPEED}},
	{Gear::THIRD, {THIRD_GEAR_MIN_SPEED, THIRD_GEAR_MAX_SPEED}},
	{Gear::FOURTH, {FOURTH_GEAR_MIN_SPEED, FOURTH_GEAR_MAX_SPEED}},
	{Gear::FIFTH, {FIFTH_GEAR_MIN_SPEED, FIFTH_GEAR_MAX_SPEED}},
};

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

private:
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
	Direction m_direction = Direction::STOP;
	bool m_isEngineOn = false;
};