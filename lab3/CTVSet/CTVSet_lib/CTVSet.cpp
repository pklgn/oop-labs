#include "pch.h"
#include "CTVSet.h"

constexpr int MIN_CHANNEL = 1;
constexpr int MAX_CHANNEL = 99;

bool CTVSet::TurnOn()
{
	m_isWorking = true;

	return true;
}

bool CTVSet::TurnOff()
{
	m_isWorking = false;

	return true;
}

bool CTVSet::SetChannel(int channel)
{
	if (!m_isWorking)
	{
		return false;
	}

	if (channel <= MIN_CHANNEL || channel >= MAX_CHANNEL)
	{
		return false;
	}

	m_selectedChannel = channel;

	return true;
}

bool CTVSet::IsTurnedOn() const
{
	return m_isWorking;
}

int CTVSet::GetChannel() const
{
	return m_selectedChannel;
}