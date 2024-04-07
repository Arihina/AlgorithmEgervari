#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(Matrix&);
Matrix copy(Matrix&);
Matrix fillRandomMatrix(int, int);
void leadByRows(Matrix&);
void leadByColumns(Matrix&);
pair<Matrix, Matrix> findLargestMatch(Matrix&);
void fillDigraph(Matrix&, Matrix&);
void solveByEgervari();

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

auto invert{ [](Matrix& matrix) {
for (int i = 0; i < matrix.size(); i++)
{
	for (int j = 0; j < matrix[i].size(); j++)
	{
		matrix[i][j] = (matrix[i][j] == 0) ? 1: 0;
	}
}
} };

auto countMatches{ [](Matrix& matrix) {int count = 0;
for (int i = 0; i < matrix.size(); i++)
{
	for (int j = 0; j < matrix[i].size(); j++)
	{
		if (matrix[i][j] == 1)
		{
			count++;
		}
	}
}

	return count;
} };


void main() {
	Matrix matrix = fillRandomMatrix(9, 10);
	Matrix saveMatrix = copy(matrix);
	printMatrix(matrix);

	int max = findMax(matrix);
	cout << max << endl << endl;

	decrement(matrix, max);
	printMatrix(matrix);

	leadByRows(matrix);
	printMatrix(matrix);

	leadByColumns(matrix);
	printMatrix(matrix);

	invert(matrix);
	printMatrix(matrix);

	Matrix copyInvertMatrix = copy(matrix);

	pair<Matrix, Matrix> matrices = findLargestMatch(matrix);

	Matrix matchMatrix = matrices.first;
	printMatrix(matchMatrix);

	Matrix digraph = matrices.second;
	fillDigraph(digraph, copyInvertMatrix);
	printMatrix(digraph);

	int count = countMatches(matchMatrix);

	if (count >= matrix.size())
	{
		cout << "" << endl;
	}
	else
	{

	}
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

pair<Matrix, Matrix> findLargestMatch(Matrix& matrix)
{
	Matrix matchMatrix(matrix.size(), vector<int>(matrix[0].size(), 0));
	Matrix digraph(matrix.size(), vector<int>(matrix[0].size(), 0));

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				matchMatrix[i][j] = 1;
				digraph[i][j] = 1;

				for (int k = i; k < matrix.size(); k++)
				{
					if (matrix[k][j] == 1)
					{
						matrix[k][j] = 0;
					}
				}

				break;
			}
		}
	}

	return make_pair(matchMatrix, digraph);
}

void fillDigraph(Matrix& digraph, Matrix& invert)
{
	for (int i = 0; i < digraph.size(); i++)
	{
		for (int j = 0; j < digraph[i].size(); j++)
		{
			if (invert[i][j] == 1 && digraph[i][j] == 0)
			{
				digraph[i][j] = -1;
			}
		}
	}
}

Matrix copy(Matrix& matrix)
{
	Matrix copyMatrix(matrix.size(), vector<int>(matrix[0].size(), 0));
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			copyMatrix[i][j] = matrix[i][j];
		}
	}

	return copyMatrix;
}