#include "CTVSet_lib/CTVSetControlConsole.h"

int main()
{
	CTVSet TVSet;
	CTVSetControlConsole controlConsole(std::cin, std::cout, TVSet);
	controlConsole.ProcessSession();

	return 0;
}