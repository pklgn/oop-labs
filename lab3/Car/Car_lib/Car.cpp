#include "pch.h"
#include "Car.h"
#include <map>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;
const int MIN_SPEED = 0;
const int MAX_SPEED = 150;

typedef std::pair<int, int> SpeedRange;
typedef std::map<int, SpeedRange> GearSpeedRangeMap;

const GearSpeedRangeMap GEAR_SPEED_RANGES{
	{ MIN_GEAR, { MIN_SPEED, 20 } },
	{ 0, { MIN_SPEED, MAX_SPEED } },
	{ 1, { MIN_SPEED, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ MAX_GEAR, { 50, MAX_SPEED } },
};

bool Car::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}

	m_isEngineOn = true;

	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_isEngineOn || !(m_speed == 0 && m_gear == 0))
	{
		return false;
	}

	m_isEngineOn = false;

	return true;
}

bool Car::SetGear(int gear)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (gear < MIN_GEAR || MAX_GEAR < gear)
	{
		return false;
	}

	SpeedRange speedRange = GEAR_SPEED_RANGES.at(gear);

	if (std::abs(m_speed) < speedRange.first || speedRange.second < std::abs(m_speed))
	{
		return false;
	}

	if (gear == MIN_GEAR && m_speed != 0)
	{
		return false;
	}

	if (m_gear == MIN_GEAR && gear == 1 && m_speed != 0)
	{
		return false;
	}

	if (m_speed < 0 && m_gear == 0 && gear == 1)
	{
		return false;
	}

	m_gear = gear;

	return true;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	SpeedRange speedRange = GEAR_SPEED_RANGES.at(m_gear);

	if (speed < speedRange.first || speedRange.second < speed)
	{
		return false;
	}

	if (m_gear == -1)
	{
		speed = -speed;
	}

	int dSpeed = std::abs(speed) - std::abs(m_speed);
	if (dSpeed > 0 && m_gear == 0)
	{
		return false;
	}

	m_speed = speed;

	return true;
}

Car::Direction Car::GetDirection() const
{
	if (m_speed < 0)
	{
		return Car::Direction::Backwards;
	}
	else if (m_speed > 0)
	{
		return Car::Direction::Forwards;
	}

	return Car::Direction::InPlace;
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	return std::abs(m_speed);
}

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}