#include "Car.h"
#include <set>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;
const int NO_SPEED_LIMIT = -1;


typedef std::pair<int, int> SpeedRange;
typedef std::pair<int, SpeedRange> GearSpeedRange;
typedef std::set<GearSpeedRange> GearSpeedRangeSet;
const GearSpeedRangeSet GEAR_SPEED_RANGES
{
	{ MIN_GEAR, { 0, 20 } },
	{ 0, { NO_SPEED_LIMIT, NO_SPEED_LIMIT } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ MAX_GEAR, { 50, 150 } },
}

