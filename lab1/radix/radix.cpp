#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iterator>

constexpr short MIN_NOTATION = 2;
constexpr short MAX_NOTATION = 36;

bool IsValidNotation(short notation)
{
	return ((notation <= MAX_NOTATION) && (notation >= MIN_NOTATION));
}

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage radix.exe <source notation> <destination notation> <value>\n";

		return 1;
	}
	bool wasError = false;
	short sourceNotation = StringToInt(argv[1], 10, wasError);
	short destinationNotation = StringToInt(argv[2], 10, wasError);

	if (!(IsValidNotation(sourceNotation) && IsValidNotation(destinationNotation)))
	{
		std::cout << "Number's notation is out of range\n";

		return 1;
	}
	
	int value = StringToInt(argv[3], sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "Overflow found during reading param" << std::endl;

		return 1;
	}

	std::cout << IntToString(value, destinationNotation, wasError) << std::endl;

	return 0;
}

int AppendDigitToPositiveNumber(int digit, int radix, int number, bool& wasError)
{
	if ((INT_MAX / radix) >= number)
	{
		number *= radix;
	}
	else
	{
		wasError = true;
	}

	if ((INT_MAX - number) >= digit)
	{
		number += digit;
	}
	else
	{
		wasError = true;
	}

	return number;
}

int AppendDigitToNegativeNumber(int digit, int radix, int number, bool& wasError)
{
	if ((INT_MIN / radix) <= number)
	{
		number *= radix;
	}
	else
	{
		wasError = true;
	}

	if ((INT_MIN - number) <= -digit)
	{
		number -= digit;
	}
	else
	{
		wasError = true;
	}

	return number;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	bool negative = false;
	int result = 0;
	short pos = 0;

	for (char ch : str)
	{
		if (ch >= '0' && ch <= '9')
		{
			// имеется в виду разряд числа
			short currDigit = ch - '0';
			result = negative
				? AppendDigitToNegativeNumber(currDigit, radix, result, wasError)
				: AppendDigitToPositiveNumber(currDigit, radix, result, wasError);
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			short currDigit = ch - 'A' + 10;
			result = negative
				? AppendDigitToNegativeNumber(currDigit, radix, result, wasError)
				: AppendDigitToPositiveNumber(currDigit, radix, result, wasError);
		}
		else if (pos == 0 && ch == '-')
		{
			negative = true;
			pos += 1;
		}
		else
		{
			wasError = true;
		}

		if (wasError)
		{
			break;
		}
	}

	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	bool negative = n < 0;
	std::string result = n == 0 ? "0" : "";

	while (n != 0)
	{
		char ch;
		short currDigit = abs(n % radix);
		if (currDigit > 9)
		{
			ch = 'A' + currDigit - 10;
		}
		else
		{
			ch = '0' + currDigit;
		}
		result = ch + result;
		n /= radix;
	}

	if (negative)
	{
		result = "-" + result;
	}

	return result;
}