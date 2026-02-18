#include <bitset>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <vector>
#include <fstream>

#include "utils.hpp"

void task1_a()
{
	unsigned char x = 255;
	unsigned char mask = 1;
	x = x & (~(mask << 4));
	std::cout << (int)x << std::endl;
}

void task1_b()
{
	unsigned char x = 0;
	unsigned char mask = 1;
	x = x | (mask << 7);
	std::cout << (int)x << std::endl;
}

void task1_c()
{
	unsigned int x = 25;
	const int n = sizeof(int) * 8;
	unsigned int mask = (1 << n - 1);

	std::cout << "Начальный вид маски: " << std::bitset<n>(mask) << std::endl;
	std::cout << "Результат: ";
	for (int i = 1; i <= n; i++)
	{
		std::cout << ((x & mask) >> (n - i));
		mask = mask >> 1;
	}
	std::cout << std::endl;
}

void task2_a()
{
	unsigned char bitArray = 0;

	std::cout << "Введите числа от 0 до 7 (закончить ввод отрицательным числом): ";
	int num;
	while (std::cin >> num && num >= 0)
	{
		if (num < 7)
		{
			bitArray |= (1 << num);
		}
	}

	std::cout << "Отсортированные числа: " << std::endl;
	for (int i = 0; i < 8; i++)
	{
		if (bitArray & (1 << i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}

void task2_b()
{
	unsigned long long bitArray = 0;

	std::cout << "Введите числа от 0 до 63 (закончить ввод отрицательным числом): ";
	int num;
	while (std::cin >> num && num >= 0)
	{
		if (num < 64)
		{
			bitArray |= (1ULL << num);
		}
	}

	std::cout << "Отсортированные числа: " << std::endl;
	for (int i = 0; i < 64; i++)
	{
		if (bitArray & (1ULL << i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}

void task2_c()
{
	const int ARRAY_SIZE = 8;
	unsigned char bitArray[ARRAY_SIZE] = {0};

	std::cout << "Введите числа от 0 до 63 (закончить ввод отрицательным числом): ";
	int num;
	while (std::cin >> num && num >= 0)
	{
		if (num < 64)
		{
			int byteIndex = num / 8;
			int bitIndex = num % 8;
			bitArray[byteIndex] |= (1 << bitIndex);
		}
	}

	std::cout << "Отсортированные числа: " << std::endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (bitArray[i] & (1 << j))
			{
				std::cout << (i * 8 + j) << " ";
			}
		}
	}
	std::cout << std::endl;
}

void task3_a()
{
	const size_t MAX_NUM = 10000000;
	const size_t BIT_ARRAY_SIZE = (MAX_NUM + 7) / 8;

	std::vector<unsigned char> bitArray(BIT_ARRAY_SIZE, 0);

	std::ifstream input_file("input.txt");
	if (!input_file)
	{
		std::cerr << "Ошибка открытия файла input.txt" << std::endl;
		return;
	}

	auto start = std::chrono::high_resolution_clock::now();

	int num;
	while (input_file >> num)
	{
		if (num >= 0 && num < MAX_NUM)
		{
			size_t byteIndex = num / 8;
			size_t bitIndex = num % 8;
			bitArray[byteIndex] |= (1 << bitIndex);
		}
	}
	input_file.close();

	std::ofstream output_file("output.txt");
	if (!output_file)
	{
		std::cerr << "Ошибка создания файла output.txt" << std::endl;
		return;
	}

	for (int i = 0; i < MAX_NUM; i++)
	{
		size_t byteIndex = i / 8;
		size_t bitIndex = i % 8;
		if (bitArray[byteIndex] & (1 << bitIndex))
		{
			output_file << i << std::endl;
		}
	}
	output_file.close();

	auto end = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	std::cout << "Время сортировки: " << deltaTime.count() / 1'000'000 << " мс" << std::endl;
}

void task3_b()
{
	const size_t MAX_NUM = 10000000;
	const size_t BIT_ARRAY_SIZE = (MAX_NUM + 7) / 8;

	std::vector<unsigned char> bitArray(BIT_ARRAY_SIZE, 0);

	std::cout << "Размер битового массива: " << BIT_ARRAY_SIZE << " байт" << std::endl;
	std::cout << "Размер в килобайтах: " << BIT_ARRAY_SIZE / 1'024.0 << " КБ" << std::endl;
	std::cout << "Размер в мегабайтах: " << BIT_ARRAY_SIZE / (1'024.0 * 1'024.0) << " МБ" << std::endl;

	std::cout << "Размер vector<unsigned char>: " << sizeof(bitArray) + bitArray.capacity()
													* sizeof(unsigned char) << " байт" << std::endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(CP_UTF8);

	// Задание 1
	// task1_a();
	// task1_b();
	// task1_c();

	// Задание 2
	// task2_a();
	// task2_b();
	// task2_c();

	// Задание 3
	utils5_1::create_test_file();
	// task3_a();
	// task3_b();

	return 0;
}