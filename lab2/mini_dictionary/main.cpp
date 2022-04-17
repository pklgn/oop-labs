#include <iostream>
#include <windows.h>
#include "mini_dictionary_lib/mini_dictionary_lib.h"

constexpr int CONSOLE_ENCODING = 1251;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(CONSOLE_ENCODING);
	SetConsoleOutputCP(CONSOLE_ENCODING);
	std::string dictFileName = GetDictionaryFileName(argc, argv);
	if (!HandleDictionarySession(dictFileName, std::cin, std::cout))
	{
		return 1;
	}

	return 0;
}
