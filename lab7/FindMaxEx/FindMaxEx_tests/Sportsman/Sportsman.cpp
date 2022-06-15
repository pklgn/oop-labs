// Sportsman.cpp : Defines the functions for the static library.
//
#include "pch.h"
#include "Sportsman.h"

bool HeightLessThan(Sportsman const& first, Sportsman const& second)
{
	return first.height < second.height;
}

bool WeightLessThan(Sportsman const& first, Sportsman const& second)
{
	return first.weight < second.weight;
}
