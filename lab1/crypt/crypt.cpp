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
constexpr auto CRYPT = "crypt";
constexpr auto DECRYPT = "decrypt";

enum class Mode
{
	Crypt,
	Decrypt,
};

struct CryptParams
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

std::optional<CryptParams> GetCryptParams(int argc, char* argv[]);
bool EncryptFile(std::ifstream& inputFile, std::ofstream& outputFile, const CryptParams& params);
bool DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, const CryptParams& params);
bool ValidateFiles(std::ifstream& inputFile, std::ofstream& outputFile);

int main(int argc, char* argv[])
{
	std::optional<CryptParams> params = GetCryptParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}

	std::ifstream inputFile(params.value().inputFileName, std::ios_base::binary);
	std::ofstream outputFile(params.value().outputFileName, std::ios_base::binary);
	if (!ValidateFiles(inputFile, outputFile))
	{
		return 1;
	}

	bool status;
	if (params.value().mode == Mode::Crypt)
	{
		status = EncryptFile(inputFile, outputFile, params.value());
	}
	else
	{
		status = DecryptFile(inputFile, outputFile, params.value());
	}
	////разделить на две функции encrypt decrypt
	//bool status = EncryptFile(params.value());
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
	//constexpr crypt decrypt
	if (std::string(argv[1]) == CRYPT)
	{
		params.mode = Mode::Crypt;
	}
	else if (std::string(argv[1]) == DECRYPT)
	{
		params.mode = Mode::Decrypt;
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

char ShuffleBits(char currByte, Mode mode)
{
	char resultByte = 0;
	for (int i = 0; i < 8; i++)
	{
		char currMask = pow(2, i);
		unsigned char maskedByte = currByte & currMask;


		// либо обобщить работу с mode либо вынести перемещение битов  в отдельную функцию
		if (mode == Mode::Crypt)
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

//const params
char EncryptByte(char currByte, int key)
{
	currByte ^= key;
	char resultByte = ShuffleBits(currByte, Mode::Crypt);

	return resultByte;
}

char DecryptByte(char currByte, int key)
{
	char resultByte = ShuffleBits(currByte, Mode::Decrypt);
	resultByte ^= key;

	return resultByte;
}

//const params
//заменить ifstream на istream
void HandleEncription(std::istream& inputFile, std::ostream& outputFile, const CryptParams& params)
{
	while (!inputFile.eof())
	{
		//читать здесь
		//encrypt byte с конкретным байтом
		char currByte;
		inputFile.read(&currByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currByte = EncryptByte(currByte, params.key);

		//outputFile.write(&currByte.value(), 1);
		outputFile << currByte;
	}

	return;
}


bool ValidateFiles(std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input file for reading\n";

		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file for reading\n";

		return false;
	}

	return true;
}

//const params
bool EncryptFile(std::ifstream& inputFile, std::ofstream& outputFile, const CryptParams& params)
{
	HandleEncription(inputFile, outputFile, params);

	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return false;
	}

	return true;
}

void HandleDecription(std::istream& inputFile, std::ostream& outputFile, const CryptParams& params)
{
	while (!inputFile.eof())
	{
		//читать здесь
		//encrypt byte с конкретным байтом
		char currByte;
		inputFile.read(&currByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currByte = DecryptByte(currByte, params.key);

		//outputFile.write(&currByte.value(), 1);
		outputFile << currByte;
	}

	return;
}

bool DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, const CryptParams& params)
{
	HandleDecription(inputFile, outputFile, params);

	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return false;
	}

	return true;
}