#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(Matrix&);
Matrix copy(Matrix&);
Matrix fillRandomMatrix(int, int);
void leadByRows(Matrix&);
void leadByColumns(Matrix&);
pair<Matrix, Matrix> findLargestMatch(Matrix&);
void fillDigraph(Matrix&, Matrix&);
void solveByEgervari(Matrix&, Matrix&, Matrix&, Matrix&);
vector<int> fillUnvisited1(Matrix&);
vector<int> fillUnvisited2(Matrix&);
Matrix getRelatedNodes(vector<int>&, Matrix&);
int getColumnIndex(Matrix&, int, vector<int>&);
int getRowIndex(Matrix&, int, vector<int>&);

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
	cout << "Start matrix" << endl;
	printMatrix(matrix);

	int max = findMax(matrix);
	cout << max << endl << endl;

	decrement(matrix, max);
	cout << "Decrement max matrix" << endl;
	printMatrix(matrix);

	leadByRows(matrix);
	cout << "Lead By Rows matrix" << endl;
	printMatrix(matrix);

	leadByColumns(matrix);
	Matrix saveLeadMatrix = copy(matrix);
	cout << "Lead By Columns matrix" << endl;
	printMatrix(matrix);

	invert(matrix);
	cout << "Invert matrix" << endl;
	printMatrix(matrix);

	Matrix invertMatrix = copy(matrix);

	pair<Matrix, Matrix> matrices = findLargestMatch(matrix);

	Matrix matchMatrix = matrices.first;
	cout << "Match matrix" << endl;
	printMatrix(matchMatrix);

	Matrix digraph = matrices.second;
	fillDigraph(digraph, invertMatrix);
	cout << "Digraph" << endl;
	printMatrix(digraph);

	int count = countMatches(matchMatrix);

	if (count >= matrix.size())
	{
		cout << "" << endl;
		// TODO: makePairs() & countResultNum() funcs
		// makePairs()
		// countResultNum()
	}
	else
	{
		// TODO: solveByEgervari func
		solveByEgervari(saveLeadMatrix, matchMatrix, digraph, invertMatrix);
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

vector<int> fillUnvisited1(Matrix& matrix)
{
	vector<int> result;
	for (int i = 0; i < matrix.size(); i++)
	{
		int count = 0;
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				count++;
			}
		}
		if (count == 0)
		{
			result.push_back(i);
		}
	}

	return result;
}

vector<int> fillUnvisited2(Matrix& matrix)
{
	vector<int> result;
	for (int i = 0; i < matrix[0].size(); i++)
	{
		int count = 0;
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[j][i] == 1)
			{
				count++;
			}
		}
		if (count == 0)
		{
			result.push_back(i);
		}
	}

	return result;
}

bool check(int node, vector<int>& nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] == node)
		{
			return true;
		}
	}

	return false;
}

int getColumnIndex(Matrix& matrix, int index, vector<int>& chain)
{
	if (index >= matrix.size())
	{
		return INT_MAX;
	}
	for (int i = 0; i < matrix[index].size(); i++)
	{
		if (matrix[index][i] == 1 && !check(i, chain))
		{
			return i;
		}
	}
}

int getRowIndex(Matrix& matrix, int index, vector<int>& chain)
{
	if (index >= matrix[0].size())
	{
		return INT_MAX;
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		if (matrix[i][index] == 1 && !check(i, chain))
		{
			return i;
		}
	}

}

Matrix getRelatedNodes(vector<int>& nodes, Matrix& matrix)
{
	Matrix chains;

	for (int k = 0; k < nodes.size(); k++)
	{
		int node = nodes[k];
		vector<int> chain = { node };

		while (true)
		{

			int index1 = getColumnIndex(matrix, node, chain);

			if (index1 == INT_MAX)
			{
				break;
			}

			chain.push_back(index1);
			int index2 = getRowIndex(matrix, index1, chain);

			if (index2 == INT_MAX)
			{
				break;
			}

			if (check(index2, nodes))
			{
				break;
			}
			else
			{
				chain.push_back(index2);
				node = index2;
			}
		}

		chains.push_back(chain);
	}

	return chains;
}

void solveByEgervari(Matrix& leadMatrix, Matrix& matchMatrix, Matrix& digraph, Matrix& invert)
{
	//TODO: solveByEgervari body
	vector<int> unvisited1 = fillUnvisited1(matchMatrix);
	vector<int> unvisited2 = fillUnvisited2(matchMatrix);
	
	Matrix chains = getRelatedNodes(unvisited1, invert);
	printMatrix(chains);
}