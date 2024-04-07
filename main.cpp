#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(Matrix&);
Matrix fillRandomMatrix(int, int);
void leadByRows(Matrix&);
void leadByColumns(Matrix&);

auto findMax{ [](Matrix& matrix) {int max = matrix[0][0];
for (int i = 0; i < matrix.size(); i++)
{
	for (int j = 0; j < matrix[i].size(); j++)
	{
		max = (matrix[i][j] > max) ? matrix[i][j] : max;
	}
}
	return max;
} };

auto findMin{ [](vector<int>& row) { int min = row[0];
for (int i = 0; i < row.size(); i++)
{
	min = (row[i] < min) ? row[i] : min;
}

	return min;
} };

auto decrement{ [](Matrix& matrix, int num) {
for (int i = 0; i < matrix.size(); i++) {
	for (int j = 0; j < matrix[i].size(); j++)
	{
		matrix[i][j] = num - matrix[i][j];
	}
}
} };

void main() {
	Matrix matrix = fillRandomMatrix(9, 20);
	printMatrix(matrix);

	int max = findMax(matrix);
	cout << max << endl;

	decrement(matrix, max);
	printMatrix(matrix);

	leadByRows(matrix);
	printMatrix(matrix);

	leadByColumns(matrix);
	printMatrix(matrix);
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
	cout << endl;
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

void leadByRows(Matrix& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		int min = findMin(matrix[i]);
		for (int j = 0; j < matrix[i].size(); j++)
		{
			matrix[i][j] -= min;
		}
	}
}

void leadByColumns(Matrix& matrix)
{

	for (int i = 0; i < matrix[0].size(); i++)
	{
		int min = matrix[0][i];
		for (int j = 0; j < matrix.size(); j++)
		{
			min = (matrix[j][i] < min) ? matrix[j][i] : min;
		}

		for (int j = 0; j < matrix.size(); j++)
		{
			matrix[j][i] -= min;
		}
	}
}