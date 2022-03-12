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

short createDigitFromChar(char ch)
{
	return ch - 'A' + 10;
}

short createDigitFromDigit(char ch)
{
	return ch - '0';
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	bool negative = false;
	int result = 0;
	size_t startPos = 0;
	if (!IsValidNotation(radix))
	{
		wasError = true;

		return result;
	}

	if (str[0] == '-')
	{
		negative = true;
		startPos = 1;
	}


	if (negative)
	{
		for (size_t pos = startPos; pos < str.length(); ++pos)
		{
			char ch = str[pos];
			if (ch >= '0' && ch <= '9')
			{
				short currDigit = createDigitFromDigit(ch);
				AppendDigitToNegativeNumber(currDigit, radix, result, wasError);
			}
			else if (ch >= 'A' && ch <= 'Z')
			{
				short currDigit = createDigitFromChar(ch);
				AppendDigitToNegativeNumber(currDigit, radix, result, wasError);
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
	}
	else
	{
		for (size_t pos = startPos; pos < str.length(); ++pos)
		{
			char ch = str[pos];
			if (ch >= '0' && ch <= '9')
			{
				short currDigit = createDigitFromDigit(ch);
				AppendDigitToPositiveNumber(currDigit, radix, result, wasError);
			}
			else if (ch >= 'A' && ch <= 'Z')
			{
				short currDigit = createDigitFromChar(ch);
				AppendDigitToPositiveNumber(currDigit, radix, result, wasError);
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
	}

	return result;
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