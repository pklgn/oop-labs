#pragma once
class Car
{
public:
	enum class Direction
	{
		Backwards,
		InPlace,
		Forwards,
	};

	bool IsTurnedOn();
	Direction GetDirection();
	int GetSpeed();
	int GetGear();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	int m_speed = 0;
	int m_gear = 0;
	bool m_isEngineRunning = false;
};
