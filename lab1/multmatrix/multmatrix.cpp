#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

const int SQUARE_MATRIX_SIZE = 3;
typedef double Matrix3x3[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE];

bool ReadMatrix3x3(const std::string& fileName, Matrix3x3& result)
{
	bool status = true;
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << fileName << " for reading" << std::endl;
		status = false;
		//return и убрать else
	}
	else
	{
		for (int currRow = 0; currRow < SQUARE_MATRIX_SIZE && status; currRow++)
		{
			for (int currColumn = 0; currColumn < SQUARE_MATRIX_SIZE && status; currColumn++)
			{
				double d;
				if (inputFile.bad() || inputFile.eof())
				{
					std::cout << "Cannot read matrix from file" << std::endl;
					status = false;
					break;
					//return false
				}
				try
				{
					//определять значение бита ошибки и убрать try catch

					std::string matrixElement;
					inputFile >> matrixElement;
					d = std::stod(matrixElement);
					result[currRow][currColumn] = d;
				}
				catch (...)
				{
					std::cout << "Error while reading an element" << std::endl;

					exit(EXIT_FAILURE);
					//не использовать exit 

					
				}
			}
		}
	}

	return status;
}
//разделить умножение и печать + убрать инициализцию и принимать по const &
void MultiplyMatrix3x3(Matrix3x3 aMatrix, Matrix3x3 bMatrix)
{
	Matrix3x3 result = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	for (int row = 0; row < SQUARE_MATRIX_SIZE; row++) {
		for (int column = 0; column < SQUARE_MATRIX_SIZE; column++) {
			for (int inter = 0; inter < SQUARE_MATRIX_SIZE; inter++) {
				result[row][column] += aMatrix[row][inter] * bMatrix[inter][column];
			}
			std::cout << std::fixed << std::setprecision(3) << result[row][column] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	//перенести к функции
	Matrix3x3 leftMatrix;
	Matrix3x3 rightMatrix;

	// добавить функцию парсинга 
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage multmatrix.exe <matrix file1> <matrix file2>";

		return 1;
	}

	std::string leftMatrixFileName = argv[1];
	std::string rightMatrixFileName = argv[2];

	if (!(ReadMatrix3x3(leftMatrixFileName, leftMatrix) && ReadMatrix3x3(rightMatrixFileName, rightMatrix)))
	{
		return 1;
	}
	
	MultiplyMatrix3x3(leftMatrix, rightMatrix);

	return 0;
}
//автоматически запувкать тесты после сборки


//добавить сравнение правильного результата: перенаправить результат перемножения в отдельный файл и сравнить этот файл с правильным