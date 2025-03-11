#include <iostream>
#include <vector>
#include <random>
#include <chrono>

enum class Case {
	WORST,
	AVERAGE,
	BEST
};

int n[11] { 100, 200, 500, 1000, 2000, 5000, 10000, 100000, 200000, 500000, 1000000 };

void copyArray(char* originArray, char* copyTo, int size)
{
	for (int i = 0; i < size; i++)
	{
		copyTo[i] = originArray[i];
	}
}

void fillArray(int size, Case _case, char* arr, char key)
{
	char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'D', 'H', 'I', 'G' };

	for (int i = 0; i < size; i++)
	{
		if (_case == Case::WORST)
		{
			arr[i] = key;
		}
		else if (_case == Case::AVERAGE)
		{
			if (rand() % 2 == 0)
			{
				arr[i] = key;
			}
			else
			{
				arr[i] = letters[rand() % 10];
			}
		}
		else if (_case == Case::BEST)
		{
			arr[i] = letters[rand() % 9];
		}
	}
}

void printArray(char* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void delFirstMethod(char x[], int n, char key)
{
	unsigned long long counterC = 0;
	unsigned long long counterM = 0;

	auto start = std::chrono::high_resolution_clock::now();

	int i = 0;
	while (i < n)
	{
		if (x[i] == key)
		{
			for (int j = i; j < n - 1; j++)
			{
				x[j] = x[j + 1];
				counterM++;
			}
			n--;
		}
		else
		{
			i++;
		}
		counterC++;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	std::cout << "Sorted array: ";
	printArray(x, 10);
	std::cout << std::endl;

	std::cout << "Time elapsed: " << deltaTime.count() / 1'000'000.0 << " ms" << std::endl;
	std::cout << "M: " << counterM << std::endl
		<< "C: " << counterC << std::endl
		<< "T: " << counterM + counterC << std::endl;
}

void delOtherMethod(char x[], int n, char key)
{
	unsigned long long counterC = 0;
	unsigned long long counterM = 0;


	auto start = std::chrono::high_resolution_clock::now();

	int j = 0;
	for (int i = 0; i < n; i++)
	{
		x[j] = x[i];
		counterM++;
		if (x[i] != key)
		{
			j++;
		}
		counterC++;
	}

	if (x[1] == key) n = 0;
	else n = j - 1;
	counterC++;

	auto end = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	std::cout << "Sorted array: ";
	printArray(x, 10);
	std::cout << std::endl;

	std::cout << std::endl << "Time elapsed: " << deltaTime.count() / 1'000'000.0 << " ms" << std::endl;
	std::cout << "M: " << counterM << std::endl << 
		"C: " << counterC << std::endl << 
		"T: " << counterM + counterC << std::endl;
}

int main()
{
	srand(time(NULL));

	char key;
	std::cin >> key;

	for (int size : n)
	{
		char* arr = new char[size];
		char* arr2 = new char[size];

		fillArray(size, Case::WORST, arr, key);
		copyArray(arr, arr2, size);
		
		std::cout << "--------------------" << std::endl;
		std::cout << "n = " << size << std::endl;

		std::cout << "First algorithm" << std::endl;
		std::cout << "Origin array: ";
		printArray(arr, 10);
		delFirstMethod(arr, size, key);

		std::cout << std::endl;

		std::cout << "Second algorithm" << std::endl;
		std::cout << "Origin array: ";
		printArray(arr2, 10);
		delOtherMethod(arr2, size, key);

		delete[] arr;
		delete[] arr2;
	}

	return 0;
}