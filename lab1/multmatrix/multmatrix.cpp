#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

const int SQUARE_MATRIX_SIZE = 3;
typedef double Matrix3x3[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE];

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
				std::cout << "Couldn't read a double from the file." << std::endl;
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
			//std::cout << std::fixed << std::setprecision(3) << result[row][column] << "  ";
		}
		//std::cout << "\n";
	}
	//std::cout << "\n";
}

void PrintMatrix3x3(const Matrix3x3 matrix)
{
	for (int row = 0; row < SQUARE_MATRIX_SIZE; row++)
	{
		for (int column = 0; column < SQUARE_MATRIX_SIZE; column++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[row][column] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main(int argc, char* argv[])
{


	// добавить функцию парсинга 
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage multmatrix.exe <matrix file1> <matrix file2>";

		return 1;
	}

	std::string leftMatrixFileName = argv[1];
	std::string rightMatrixFileName = argv[2];

	Matrix3x3 aMat;
	Matrix3x3 bMat;
	if (!(ReadMatrix3x3(leftMatrixFileName, aMat) && ReadMatrix3x3(rightMatrixFileName, bMat)))
	{
		return 1;
	}
	
	Matrix3x3 rMat;
	MultiplyMatrix3x3(aMat, bMat, rMat);

	return 0;
}
//автоматически запувкать тесты после сборки


//добавить сравнение правильного результата: перенаправить результат перемножения в отдельный файл и сравнить этот файл с правильным