#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <optional>

const int SQUARE_MATRIX_SIZE = 3;
typedef double Matrix3x3[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE];
//объявить как std::array массив фиксированного размера и возвращать массив как результат работы функции

bool ReadMatrix3x3(const std::string& fileName, Matrix3x3& result)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << fileName << " for reading" << std::endl;
		return false;
	}
	for (int currRow = 0; currRow < SQUARE_MATRIX_SIZE; currRow++)
	{
		for (int currColumn = 0; currColumn < SQUARE_MATRIX_SIZE; currColumn++)
		{
			//перенести условие после чтения
			if (inputFile.bad() || inputFile.eof())
			{
				std::cout << "Cannot read matrix from file" << std::endl;
				return false;
			}
			
			//определять значение бита ошибки и убрать try catch
			double elt;
			inputFile >> elt;
			if (inputFile.fail())
			{
				std::cout << "Couldn't read a matrix element from the file" << std::endl;
				return false;
			}
			result[currRow][currColumn] = elt;
		}
	}

	return true;
}
//разделить умножение и печать + убрать инициализцию и принимать по const &
void MultiplyMatrix3x3(const Matrix3x3& aMatrix, const Matrix3x3& bMatrix, Matrix3x3& result)
{
	for (int row = 0; row < SQUARE_MATRIX_SIZE; row++) {
		for (int column = 0; column < SQUARE_MATRIX_SIZE; column++) {
			for (int inter = 0; inter < SQUARE_MATRIX_SIZE; inter++) {
				result[row][column] += aMatrix[row][inter] * bMatrix[inter][column];
			}
		}

	}
}

void PrintMatrix3x3(const Matrix3x3 matrix)
{
	for (int row = 0; row < SQUARE_MATRIX_SIZE; row++)
	{
		for (int column = 0; column < SQUARE_MATRIX_SIZE; column++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

struct Params 
{
	Matrix3x3 aMat;
	Matrix3x3 bMat;
};

std::optional<Params> getParams(int argc, char* argv[])
{
	Params result;
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage multmatrix.exe <matrix file1> <matrix file2>";
		return std::nullopt;
	}

	std::string aMatFileName = argv[1];
	std::string bMatFileName = argv[2];
	if (!(ReadMatrix3x3(aMatFileName, result.aMat) && ReadMatrix3x3(bMatFileName, result.bMat)))
	{
		return std::nullopt;
	}
	else
	{
		return result;
	}
}

int main(int argc, char* argv[])
{
	//заменить имя с большой букву
	std::optional<Params> matrices = getParams(argc, argv);
	if (!matrices.has_value())
	{
		return 1;
	}
	Matrix3x3 rMat = { };
	MultiplyMatrix3x3(matrices.value().aMat, matrices.value().bMat, rMat);
	PrintMatrix3x3(rMat);

	return 0;
}
//автоматически запувкать тесты после сборки


//добавить сравнение правильного результата: перенаправить результат перемножения в отдельный файл и сравнить этот файл с правильным