#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

void task1()
{
    int a, b;
    cin >> a >> b;

	while (a != 0 && b != 0)
	{
		if (a > b)
		{
			a = a % b;
		}
		else
		{
			b = b % a;
		}
	}

	cout << a + b;
}

void task2()
{
	int N;
	cin >> N;

	vector<int> numbers;

	for (int i = 0; i <= N; i++)
	{
		numbers.push_back(i);
	}

	numbers[1] = 0;

	int m, j;
	m = 2;
	j = 0;

	while (m <= N)
	{
		if (numbers[m] != 0)
		{
			j = m + m;
			
			while (j <= N)
			{
				numbers[j] = 0;
				j = j + m;
			}
		}

		m += 1;
	}

	vector<int> newVec;

	for (int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] != 0)
		{
			newVec.push_back(numbers[i]);
		}
	}

	for (int i = 0; i < newVec.size(); i++)
	{
		cout << newVec[i] << " ";
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	short taskNum;
	cin >> taskNum;

	switch (taskNum)
	{
	case 1:
		task1();
		break;
	case 2:
		task2();
	default:
		break;
	}
    return 0;
}
