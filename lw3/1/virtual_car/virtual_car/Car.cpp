#include "Car.h";

bool Car::TurnOnEngine()
{
	if (m_speed == 0 && m_gear == Gear::NEUTRAL)
	{
		m_direction = Direction::STOP;
		m_isEngineOn = true;
		return true;
	}

	return false;
}

bool Car::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == Gear::NEUTRAL)
	{
		m_direction = Direction::STOP;
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool Car::SetGear(Gear gear)
{
	if (static_cast<int>(gear) - 1 < MIN_GEAR || static_cast<int>(gear) - 1 > MAX_GEAR)
	{
		return false;
	}

	if (!m_isEngineOn && gear != Gear::NEUTRAL)
	{
		return false;
	}

	if (gear == Gear::REVERSE && m_direction != Direction::STOP)
	{
		return false;
	}

	if (m_direction == Direction::BACKWARD && gear != Gear::REVERSE && gear != Gear::NEUTRAL)
	{
		return false;
	}

	//вместо пар хранить структуры
	//поиск производить один раз, файнд может вернуть неразыменованный итератор, проверять диапазон
	if (gearSpeedInterval.find(gear)->second.first > m_speed || gearSpeedInterval.find(gear)->second.second < m_speed)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	//добавить комментарий или сделать лучше код, чтобы было лучше читать
	//проверка на нейтралке и с выключенным двигателем это разные проверки
	if ((m_gear == Gear::NEUTRAL || !m_isEngineOn) && speed > m_speed)
	{
		return false;
	}

	if (gearSpeedInterval.find(m_gear)->second.first > speed || gearSpeedInterval.find(m_gear)->second.second < speed)
	{
		return false;
	}

	m_speed = speed;

	if (m_direction == Direction::STOP && m_gear == Gear::REVERSE)
	{
		m_direction = Direction::BACKWARD;
	}

	if (m_direction == Direction::STOP && m_gear != Gear::REVERSE && m_gear != Gear::NEUTRAL)
	{
		m_direction = Direction::FORWARD;
	}

	if (m_speed == MIN_SPEED)
	{
		m_direction = Direction::STOP;
	}
	return true;
}

bool Car::IsTurnedOn()const
{
	return m_isEngineOn;
}

Direction Car::GetDirection()const
{
	return m_direction;
}

int Car::GetSpeed()const
{
	return m_speed;
}

Gear Car::GetGear()const
{
	return m_gear;
}