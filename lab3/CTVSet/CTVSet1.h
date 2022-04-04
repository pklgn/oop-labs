#pragma once
class CTVSet
{
public:
	bool TurnOn();
	bool TurnOff();
	bool SetChannel(int channel);
	bool isTurnedOn() const;
	int GetChannel() const;

private:
	int m_selectedChannel = 1;
	bool m_isWorking = false;
};
