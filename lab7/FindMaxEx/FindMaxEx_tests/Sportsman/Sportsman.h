#pragma once
#include "pch.h"

struct Sportsman
{
	std::string name;
	unsigned char height;
	unsigned char weight;
};

bool HeightLessThan(Sportsman const& first, Sportsman const& second);

bool WeightLessThan(Sportsman const& first, Sportsman const& second);