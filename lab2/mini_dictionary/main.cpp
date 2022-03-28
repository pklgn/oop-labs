#include <iostream>
#include "mini_dictionary_lib/mini_dictionary_lib.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	if (!LaunchDictionarySession(argc, argv, std::cin, std::cout))
	{
		return 1;
	}

	return 0;
}
