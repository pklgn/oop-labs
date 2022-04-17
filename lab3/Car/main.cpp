#include "Car_lib/CarControlConsole.h"

int main()
{
	Car car;
	CarControlConsole controlConsole(std::cin, std::cout, car);
	controlConsole.ProcessSession();

	return 0;
}