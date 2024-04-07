#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(Matrix&);
Matrix fillRandomMatrix(int, int);

auto findMax{ [](Matrix& matrix) {int max = matrix[0][0];
	for (int i = 0; i < matrix.size(); i++)
	for (int j = 0; j < matrix[i].size(); j++)
	{
		max = (matrix[i][j] > max) ? matrix[i][j] : max;
	}
	return max;
} };

auto decrement{ []() {

}
};

void main() {
	Matrix matrix = fillRandomMatrix(9, 20);
	printMatrix(matrix);

	int max = findMax(matrix);
	cout << max;
}

void printMatrix(Matrix& matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix fillRandomMatrix(int counRow, int countColumn) {
	Matrix matrix(counRow, vector<int>(countColumn, 0));

	for (int i = 0; i < counRow; i++)
	{
		vector<int> row(countColumn, 0);
		for (int j = 0; j < countColumn; j++)
		{
			row[j] = rand() % 10;
		}
		matrix[i] = row;;
	}

	return matrix;
}