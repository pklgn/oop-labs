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
typedef std::array<std::string, MAX_POS> Map;

std::optional<FillParams> GetFillParams(int argc, char* argv[]);
std::optional<Map> GetMap(std::ifstream& inputFile, std::stack<Point>& startPoints);
void Fill(Map& map, std::stack<Point>& startPoints, bool& isFilled);
bool ValidateFiles(const std::ifstream& inputFile, const std::ofstream& outputFile);

int main(int argc, char* argv[])
{
	std::optional<FillParams> params = GetFillParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}

	std::ifstream inputFile(params.value().inputFileName);
	std::ofstream outputFile(params.value().outputFileName);
	ValidateFiles(inputFile, outputFile);

	StartPoints startPoints;
	std::optional<Map> map = GetMap(inputFile, startPoints);
	if (!map.has_value())
	{
		return 1;
	}

	bool isFilled = false;
	while (!isFilled)
	{
		Fill(map.value(), startPoints, isFilled);
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

bool AppendLineToMap(size_t linePos, const std::string& line, Map& map, std::stack<Point>& startPoints)
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

		map[linePos].push_back(mapElement.value());
	}

	if (map[linePos].length() < MAX_POS)
	{
		map[linePos].resize(MAX_POS, BLANK);
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
		bool status = AppendLineToMap(linePos, line, map, startPoints);
		if (!status)
		{
			return std::nullopt;
		}

		++linePos;
	}
	std::string blankString;
	for (size_t y = linePos; y < MAX_POS; ++y)
	{
		map[y].resize(MAX_POS, BLANK);
	}

	return map;
}

bool LeftStartPointFound(short offsetY, Point& p, Map& map)
{
	return map[p.y + offsetY][p.x + 1] != BORDER && map[p.y + offsetY][p.x + 1] != FILLED_POINT;
}

bool LeftLinkFound(Point& p, Map& map)
{
	return map[p.y][p.x + 1] != BORDER;
}

void AddLeftStartPoint(short offset, Point& p, Map& map, StartPoints& startPoints)
{
	Point startPoint;
	if (LeftStartPointFound(offset, p, map) && LeftLinkFound(p, map))
	{
		startPoint = { p.x + 1, p.y + offset };
		startPoints.push(startPoint);
	}

	return;
}

void FillToLeft(const Point& point, Map& map, StartPoints& startPoints)
{
	Point p = point;
	short offsetUp = -1;
	short offsetDown = 1;
	while (p.x >= MIN_POS && map[p.y][p.x] != BORDER)
	{
		if (map[p.y][p.x] != START_POINT)
		{
			map[p.y][p.x] = FILLED_POINT;
		}

		if (p.y > MIN_POS && map[p.y + offsetUp][p.x] == BORDER)
		{
			AddLeftStartPoint(offsetUp, p, map, startPoints);
		}
		if (p.y < MAX_POS - 1 && map[p.y + offsetDown][p.x] == BORDER)
		{
			AddLeftStartPoint(offsetDown, p, map, startPoints);
		}

		--p.x;
	}
	
	if (p.y > MIN_POS)
	{
		AddLeftStartPoint(offsetUp, p, map, startPoints);
	}
	if (p.y < MAX_POS - 1)
	{
		AddLeftStartPoint(offsetDown, p, map, startPoints);
	}
	
	return;
}

bool RightStartPointFound(short offsetY, Point& p, Map& map)
{
	return map[p.y + offsetY][p.x - 1] != BORDER && map[p.y + offsetY][p.x - 1] != FILLED_POINT;
}

bool RightLinkFound(Point& p, Map& map)
{
	return map[p.y][p.x - 1] != BORDER;
}

void AddRightStartPoint(short offset, Point& p, Map& map, StartPoints& startPoints)
{
	Point startPoint;
	if (RightStartPointFound(offset, p, map) && RightLinkFound(p, map))
	{
		startPoint = { p.x - 1, p.y + offset };
		startPoints.push(startPoint);
	}

	return;
}
// TODO: поправить все предупреждения
void FillToRight(const Point& point, Map& map, StartPoints& startPoints)
{
	short offsetUp = -1;
	short offsetDown = 1;
	Point p = point;
	// TODO: привести тип к Int
	while (p.x < map[p.y].size() && map[p.y][p.x] != BORDER)
	{
		if (map[p.y][p.x] != START_POINT)
		{
			map[p.y][p.x] = FILLED_POINT;
		}

		if (p.y > MIN_POS && p.x > MIN_POS && map[p.y + offsetUp][p.x] == BORDER)
		{
			AddRightStartPoint(offsetUp, p, map, startPoints);
		}
		if (p.y < MAX_POS - 1 && p.x > MIN_POS && map[p.y + offsetDown][p.x] == BORDER)
		{
			AddRightStartPoint(offsetDown, p, map, startPoints);
		}

		++p.x;
	}

	if (p.y > MIN_POS)
	{
		AddRightStartPoint(offsetUp, p, map, startPoints);
	}
	if (p.y < MAX_POS - 1)
	{
		AddRightStartPoint(offsetDown, p, map, startPoints);
	}
}

void Fill(Map& map, std::stack<Point>& startPoints, bool& isFilled)
{
	if (startPoints.empty())
	{
		isFilled = true;

		return;
	}
	Point point = startPoints.top();
	startPoints.pop();

	FillToLeft(point, map, startPoints);
	FillToRight(point, map, startPoints);

	return;
}

bool ValidateFiles(const std::ifstream& inputFile, const std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input file for reading\n";

		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file for writing\n";

		return false;
	}

	return true;
}