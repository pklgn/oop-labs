#include <iostream>
#include <stack>
#include <optional>
#include <string>
#include <fstream>
#include <array>

constexpr short MIN_POS = 0;
constexpr short MAX_POS = 100;
constexpr char BORDER = '#';
constexpr char BLANK = ' ';
constexpr char START_POINT = 'O';
constexpr char FILLED_POINT = '.';

struct Point
{
	short x;
	short y;
};

struct FillParams
{
	std::string inputFileName;
	std::string outputFileName;
};

typedef std::array<std::string, MAX_POS> Map;

std::optional<FillParams> GetFillParams(int argc, char* argv[])
{
	FillParams params;

	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage fill.exe <input file> <output file>\n";

		return std::nullopt;
	}

	params.inputFileName = argv[1];
	params. outputFileName = argv[2];

	return params;
}

std::optional<char> ValidateMapElement(char ch)
{
	if (ch != BORDER && ch != START_POINT && ch != BLANK)
	{
		std::cout << "Invalid map element\n";

		return std::nullopt;
	}

	return ch;
}

bool AppendLine(size_t posY, std::string& line, Map& map, std::stack<Point>& startPoints)
{
	for (size_t posX = 0; posX < MAX_POS && posX < line.length(); ++posX)
	{
		std::optional<char> mapElement = ValidateMapElement(line[posX]);
		if (!mapElement.has_value())
		{
			std::cout << line[posX] << std::endl;
			std::cout << posX << " " << posY << std::endl;
			return false;
		}
		if (mapElement.value() == START_POINT)
		{
			Point point = { posX, posY };
			startPoints.push(point);
		}

		map[posY].push_back(mapElement.value());
	}

	return true;
}

std::optional<Map> GetMap(std::ifstream& inputFile, std::stack<Point>& startPoints)
{
	Map map;
	size_t posY = 0;
	std::string line;
	bool status = true;
	while (!inputFile.eof() && posY < MAX_POS)
	{
		std::getline(inputFile, line);
		if (!line.empty())
		{
			status = AppendLine(posY, line, map, startPoints);
		}
		if (!status)
		{
			return std::nullopt;
		}
		++posY;
	}

	return map;
}

void FillLine(size_t posX, std::string& currLine, std::stack<Point>& prevLines)
{

}

int main(int argc, char* argv[])
{
	std::optional<FillParams> params = GetFillParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}

	std::ifstream inputFile(params.value().inputFileName);
	std::ofstream outputFile(params.value().outputFileName);
	//читаем карту
	std::stack<Point> startPoints;
	std::optional<Map> map = GetMap(inputFile, startPoints);
	if (!map.has_value())
	{
		return 1;
	}
	for (std::string line : map.value())
	{
		outputFile << line << std::endl;
	}
	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return 1;
	}
	

	return 0;
}