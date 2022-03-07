#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <ios>

constexpr int MIN_KEY = 0;
constexpr int MAX_KEY = 255;
constexpr std::array<int, 8> OFFSET_ENCRYPT = { 2, 3, 4, 6, 7, 0, 1, 5 };
constexpr std::array<int, 8> OFFSET_DECRYPT = { 5, 6, 0, 1, 2, 7, 3, 4 };

enum Mode
{
	CRYPT,
	DECRYPT,
};

struct CryptParams
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

std::optional<CryptParams> GetCryptParams(int argc, char* argv[]);
bool Encrypt(CryptParams& params);

int main(int argc, char* argv[])
{
	std::optional<CryptParams> params = GetCryptParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}

	bool status = Encrypt(params.value());
	if (!status)
	{
		return 1;
	}

	return 0;
}

std::optional<CryptParams> GetCryptParams(int argc, char* argv[])
{
	CryptParams params;

	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage crypt.exe crypt <input file> <output file> <key> \n"
			<< "or\n Usage crypt.exe decrypt <input file> <output file> <key>\n";

		return std::nullopt;
	}
	if (std::string(argv[1]) == "crypt")
	{
		params.mode = Mode::CRYPT;
	}
	else if (std::string(argv[1]) == "decrypt")
	{
		params.mode = Mode::DECRYPT;
	}
	else
	{
		std::cout << "Invalid program mode\n";

		return std::nullopt;
	}

	params.inputFileName = argv[2];
	params.outputFileName = argv[3];

	try
	{
		params.key = std::stoi(argv[4]);
	}
	catch (...)
	{
		std::cout << "Invalid key value\n";

		return std::nullopt;
	}


	if (params.key > MAX_KEY || params.key < MIN_KEY)
	{
		std::cout << "Key value is out of range\n";

		return std::nullopt;
	}

	return params;
}

char ShuffleBits(char currByte, CryptParams& params)
{
	char resultByte = 0;
	for (int i = 0; i < 8; i++)
	{
		char currMask = pow(2, i);
		unsigned char maskedByte = currByte & currMask;

		if (params.mode == Mode::CRYPT)
		{
			if ((OFFSET_ENCRYPT[i] - i) >= 0)
			{
				maskedByte <<= OFFSET_ENCRYPT[i] - i;
			}
			else
			{
				maskedByte >>= i - OFFSET_ENCRYPT[i];
			}
		}
		else
		{
			if ((OFFSET_DECRYPT[i] - i) >= 0)
			{
				maskedByte <<= OFFSET_DECRYPT[i] - i;
			}
			else
			{
				maskedByte >>= i - OFFSET_DECRYPT[i];
			}

		}
		resultByte |= maskedByte;
	}

	return resultByte;
}

std::optional<char> EncryptByte(std::ifstream& inputFile, std::ofstream& outputFile, CryptParams& params)
{
	char currByte;
	inputFile.read(&currByte, 1);
	if (inputFile.eof())
	{
		return std::nullopt;
	}

	if (params.mode == Mode::CRYPT)
	{
		currByte = currByte ^ params.key;
	}

	char resultByte = ShuffleBits(currByte, params);

	if (params.mode == Mode::DECRYPT)
	{
		resultByte = resultByte ^ params.key;
	}

	return resultByte;
}

void HandleEncription(std::ifstream& inputFile, std::ofstream& outputFile, CryptParams& params)
{
	while (!inputFile.eof())
	{
		std::optional<char> currByte = EncryptByte(inputFile, outputFile, params);
		if (!currByte.has_value())
		{
			break;
		}

		outputFile.write(&currByte.value(), 1);
	}

	return;
}

bool Encrypt(CryptParams& params)
{
	std::ifstream inputFile(params.inputFileName, std::ios_base::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << params.inputFileName << " for reading\n";

		return false;
	}

	std::ofstream outputFile(params.outputFileName, std::ios_base::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << params.outputFileName << " for reading\n";

		return false;
	}

	HandleEncription(inputFile, outputFile, params);

	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return false;
	}

	inputFile.close();
	outputFile.close();

	return true;
}

