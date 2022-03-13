#include <iostream>
#include <stack>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <vector>

constexpr int MIN_POS = 0;
constexpr int MAX_POS = 100;
constexpr char BORDER = '#';
constexpr char BLANK = ' ';
constexpr char START_POINT = 'O';
constexpr char FILLED_POINT = '.';

struct Point
{
	int x;
	int y;
};

struct FillParams
{
	std::string inputFileName;
	std::string outputFileName;
};

typedef std::stack<Point> StartPoints;

struct Map
{
	int ySize;
	std::array<std::string, MAX_POS> lines;
};

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
	params.outputFileName = argv[2];

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

bool AppendLine(size_t linePos, std::string& line, Map& map, std::stack<Point>& startPoints)
{
	for (size_t posX = 0; posX < MAX_POS && posX < line.length(); ++posX)
	{
		std::optional<char> mapElement = ValidateMapElement(line[posX]);
		if (!mapElement.has_value())
		{
			return false;
		}
		if (mapElement.value() == START_POINT)
		{
			Point point = { posX, linePos };
			startPoints.push(point);
		}

		map.lines[linePos].push_back(mapElement.value());
	}
	if (map.lines[linePos].length() < MAX_POS)
	{
		map.lines[linePos].resize(MAX_POS, BLANK);
	}

	return true;
}

std::optional<Map> GetMap(std::ifstream& inputFile, std::stack<Point>& startPoints)
{
	Map map;
	size_t linePos = 0;
	std::string line;
	while (!inputFile.eof() && linePos < MAX_POS)
	{
		std::getline(inputFile, line);
		bool status = AppendLine(linePos, line, map, startPoints);
		if (!status)
		{
			return std::nullopt;
		}

		++linePos;
	}
	std::string blankString;
	for (size_t y = linePos; y < MAX_POS; ++y)
	{
		map.lines[y].resize(MAX_POS, BLANK);
	}
	map.ySize = MAX_POS;
	return map;
}

void FillLine(Map& map, std::stack<Point>& startPoints, bool& isFilled)
{
	if (startPoints.empty())
	{
		isFilled = true;

		return;
	}
	Point point = startPoints.top();
	startPoints.pop();
	Point startPoint;
	auto [posX, posY] = point;
	while (posX >= MIN_POS && map.lines[posY][posX] != BORDER)
	{
		if (map.lines[posY][posX] != START_POINT)
		{
			map.lines[posY][posX] = FILLED_POINT;
		}

		if (posY > 0 && map.lines[posY - 1][posX] == BORDER && map.lines[posY - 1][posX + 1] != BORDER && map.lines[posY - 1][posX + 1] != FILLED_POINT && map.lines[posY][posX + 1] != BORDER)
		{
			startPoint = { posX + 1, posY - 1 };
			startPoints.push(startPoint);
		}
		if (posY < map.ySize - 1 && map.lines[posY + 1][posX] == BORDER && map.lines[posY + 1][posX + 1] != BORDER && map.lines[posY + 1][posX + 1] != FILLED_POINT && map.lines[posY][posX + 1] != BORDER)
		{
			startPoint = { posX + 1, posY + 1 };
			startPoints.push(startPoint);
		}
		--posX;
	}
	if (posY > MIN_POS && map.lines[posY - 1][posX + 1] != BORDER && map.lines[posY - 1][posX + 1] != FILLED_POINT && map.lines[posY][posX + 1] != BORDER)
	{
		startPoint = { posX + 1, posY - 1 };
		startPoints.push(startPoint);
	}
	if (posY < map.ySize - 1 && map.lines[posY + 1][posX + 1] != BORDER && map.lines[posY + 1][posX + 1] != FILLED_POINT && map.lines[posY][posX + 1] != BORDER)
	{
		startPoint = { posX + 1, posY + 1 };
		startPoints.push(startPoint);
	}

	posX = point.x;
	while (posX < map.lines[posY].size() && map.lines[posY][posX] != BORDER)
	{
		if (map.lines[posY][posX] != START_POINT)
		{
			map.lines[posY][posX] = FILLED_POINT;
		}

		if (posY > MIN_POS && posX > MIN_POS && map.lines[posY - 1][posX - 1] != BORDER && map.lines[posY - 1][posX] == BORDER && map.lines[posY - 1][posX - 1] != FILLED_POINT && map.lines[posY][posX - 1] != BORDER)
		{
			startPoint = { posX - 1, posY - 1 };
			startPoints.push(startPoint);
		}
		if (posY < map.ySize - 1 && posX > MIN_POS && map.lines[posY + 1][posX - 1] != BORDER && map.lines[posY + 1][posX] == BORDER && map.lines[posY + 1][posX - 1] != FILLED_POINT && map.lines[posY][posX - 1] != BORDER)
		{
			startPoint = { posX - 1, posY + 1 };
			startPoints.push(startPoint);
		}
		++posX;
	}
	if (posY > MIN_POS && map.lines[posY - 1][posX - 1] != BORDER && map.lines[posY - 1][posX - 1] != FILLED_POINT && map.lines[posY][posX - 1] != BORDER)
	{
		startPoint = { posX - 1, posY - 1 };
		startPoints.push(startPoint);
	}
	if (posY < MAX_POS - 1 && map.lines[posY + 1][posX - 1] != BORDER && map.lines[posY + 1][posX - 1] != FILLED_POINT && map.lines[posY][posX - 1] != BORDER)
	{
		startPoint = { posX - 1, posY + 1 };
		startPoints.push(startPoint);
	}
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

	StartPoints startPoints;
	std::optional<Map> map = GetMap(inputFile, startPoints);
	if (!map.has_value())
	{
		return 1;
	}
	Map resultMap = map.value();
	bool isFilled = false;
	while(!isFilled)
	{
		FillLine(resultMap, startPoints, isFilled);
		if (isFilled)
		{
			break;
		}
	}
	for (std::string line : resultMap.lines)
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