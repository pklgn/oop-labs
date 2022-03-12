#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iterator>
#include <optional>

constexpr short MIN_NOTATION = 2;
constexpr short MAX_NOTATION = 36;

struct Params
{
	short srcNotation;
	short destNotation;
	int value;
};

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);
std::optional<Params> GetParams(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	const auto params = GetParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}
	bool wasError = false;

	std::string convertedNumber = IntToString(params.value().value, params.value().destNotation, wasError);
	if (wasError)
	{
		return 1;
	}
	std::cout << convertedNumber << std::endl;

	return 0;
}

bool IsValidNotation(short notation)
{
	return ((notation <= MAX_NOTATION) && (notation >= MIN_NOTATION));
}

std::optional<Params> GetParams(int argc, char* argv[])
{
	Params params;

	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage radix.exe <source notation> <destination notation> <value>\n";

		return std::nullopt;
	}
	bool wasError = false;
	params.srcNotation = StringToInt(argv[1], 10, wasError);
	params.destNotation = StringToInt(argv[2], 10, wasError);
	if (wasError)
	{
		std::cout << "Invalid number notation was found\n";

		return std::nullopt;
	}

	if (!(IsValidNotation(params.srcNotation) && IsValidNotation(params.destNotation)))
	{
		std::cout << "Number notation is out of range\n";

		return std::nullopt;
	}

	params.value = StringToInt(argv[3], params.srcNotation, wasError);
	if (wasError)
	{
		std::cout << "Overflow found during reading param\n";

		return std::nullopt;
	}

	return params;
}

int AppendDigitToPositiveNumber(int digit, int radix, int& number, bool& wasError)
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

int AppendDigitToNegativeNumber(int digit, int radix, int& number, bool& wasError)
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

short GetDigitFromChar(char ch, int radix, bool& wasError)
{
	short currDigit = 0;
	if (ch >= '0' && ch <= '9')
	{
		currDigit = ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		currDigit = ch - 'A' + 10;
		currDigit = ch - 'A' + 10;
	}
	else
	{
		wasError = true;
	}

	return currDigit;
}

int ConvertNegativeNumberString(size_t startPos, const std::string& str, int radix, bool& wasError)
{
	int result = 0;
	for (size_t pos = startPos; pos < str.length(); ++pos)
	{
		short currDigit = GetDigitFromChar(str[pos], radix, wasError);
		AppendDigitToNegativeNumber(currDigit, radix, result, wasError);

		if (wasError)
		{
			break;
		}
	}
	return result;
}

int ConvertPositiveNumberString(size_t startPos, const std::string& str, int radix, bool& wasError)
{
	int result = 0;
	for (size_t pos = startPos; pos < str.length(); ++pos)
	{
		short currDigit = GetDigitFromChar(str[pos], radix, wasError);
		AppendDigitToPositiveNumber(currDigit, radix, result, wasError);

		if (wasError)
		{
			break;
		}
	}

	return result;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result;
	size_t startPos = 0;
	bool negative = false;
	if (!IsValidNotation(radix))
	{
		wasError = true;

		return 1;
	}

	if (str[0] == '-')
	{
		negative = true;
		startPos = 1;
	}

	return result = negative
		? ConvertNegativeNumberString(startPos, str, radix, wasError)
		: ConvertPositiveNumberString(startPos, str, radix, wasError);
}

std::string IntToString(int n, int radix, bool& wasError)
{
	if (!IsValidNotation(radix))
	{
		wasError = true;

		return "";
	}

	bool negative = n < 0;
	std::string result = n == 0 ? "0" : "";

	while (n != 0)
	{
		char ch;
		short currDigit = abs(n % radix);
		if (currDigit > 9)
		{
			ch = 'A' + (currDigit - 10);
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