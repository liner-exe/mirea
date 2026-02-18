#include <iostream>
#include <vector>
#include <windows.h>

bool isAllZeroes(
	const std::vector<std::vector<int>>& matrix, int row, int column, int s)
{
	for (int i = row; i < row + s; i++)
	{
		for (int j = column; j < column + s; j++)
		{
			if (matrix[i][j] != 0) return false;
		}
	}

	return true;
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	int M, N;
	std::cout << "Введите размеры матрицы (M, N): ";
	std::cin >> M >> N;

	std::vector<std::vector<int>> matrix(M, std::vector<int>(N));
	std::cout << "Введите элементы матрицы (0 или 1): " << std::endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> matrix[i][j];
		}
	}

	int maxS = 0;
	int bestRow = -1, bestColumn = -1;
	long long branchAndBoundSteps = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i + maxS >= M || j + maxS >= N) continue;

			int s = maxS + 1;
			while (i + s <= M && j + s <= N)
			{
				branchAndBoundSteps++;
				if (isAllZeroes(matrix, i, j, s))
				{
					maxS = s;
					bestRow = i;
					bestColumn = j;
					s++;
				} else
				{
					break;
				}
			}
		}
	}

	std::cout << std::endl << "Результаты" << std::endl;

	if (maxS > 0)
	{
		std::cout << "Максимальный размер квадрата: " << maxS << "x" << maxS << std::endl;
		std::cout << "Координаты верхнего левого угла: (" << bestRow + 1 << ", " << bestColumn + 1 << ")" << std::endl;
	}
	else
	{
		std::cout << "Не найдены квадраты из нулей";
	}

	long long bruteForceSteps = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int s = 1; i + s <= M && j + s <= N; s++)
			{
				bruteForceSteps++;
			}
		}
	}

	std::cout << "Количество итераций брутфорсом: " << bruteForceSteps << std::endl;
	std::cout << "Количество итераций методом ветвей и границ: " << branchAndBoundSteps << std::endl;

	return 0;
}
