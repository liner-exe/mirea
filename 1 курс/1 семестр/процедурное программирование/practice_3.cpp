#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cctype>
#include <Windows.h>

void task1()
{
	double S, n, p;
	double m;

	std::cout << "Enter S: ";
	std::cin >> S;

	std::cout << "Enter p: ";
	std::cin >> p;

	std::cout << "Enter n: ";
	std::cin >> n;

	if ((n > 0 && n <= 30) && (p > 0 && p < 101))
	{
		double r = p / 100;
		m = (S * r * pow((1 + r), n)) / (12 * (pow((1 + r), n) - 1));
		
		std::cout << "m = " << m;
	}
	else
	{
		if (p == 0)
		{
			m = S / (12 * n);
			std::cout << "m = " << m;
		}
		else
		{
			std::cout << "Error!";
		}
	}
}

void task2()
{
	double S, m0, n;
	double r, m;

	std::cout << "Enter S: ";
	std::cin >> S;

	std::cout << "Enter m0: ";
	std::cin >> m0;

	std::cout << "Enter n: ";
	std::cin >> n;

	for (double p = 0; p < 101; p += 0.1)
	{
		r = p / 100;
		m = (S * r * pow((1 + r), n)) / (12 * (pow((1 + r), n) - 1));

		if (abs(m - m0) < 0.01)
		{
			std::cout << p;
			return;
		}
	}

	std::cout << "Error!";
}

void task3()
{
	std::cin.ignore();

	char buffer[1000];
	std::string input;
	
	std::cout << "Enter string: ";
	getline(std::cin, input);

	std::ofstream fout("task3_4.txt");

	if (fout.is_open())
	{
		fout << input;
		fout.close();
	}
	else
	{
		std::cout << "Error";
		return;
	}

	std::ifstream fin("task3_4.txt");

	if (fout.is_open())
	{
		fin.getline(buffer, 1000);
		fin.close();
	}
	else
	{
		std::cout << "Error";
		return;
	}

	std::cout << "Result: " << buffer;
}

void task4()
{
	std::string digits = "0123456789";
	char buffer[1000];

	std::ifstream fin("task3_4.txt");

	if (fin.is_open())
	{
		fin.getline(buffer, 1000);
		fin.close();
	}
	else
	{
		std::cout << "Error";
		return;
	}

	std::cout << "Filtered string: ";

	for (int i = 0; i <= 1000; i++)
	{
		if (buffer[i] == '\0')
		{
			return;
		}

		if (digits.find(buffer[i]) != -1)
		{
			std::cout << buffer[i];
		}
	}
}

void task5()
{
	std::cin.ignore();

	std::string str;

	std::cout << "Enter string: ";
	getline(std::cin, str);

	int length = str.length();

	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (tolower(str[j]) > tolower(str[j + 1]))
			{
				char temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}

	std::cout << "Sorted string: " << str;
}

int main()
{
	system("chcp 1251");

	std::cout << "Enter number of task: ";

	short task;
	std::cin >> task;

	switch (task)
	{
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		case 4:
			task4();
			break;
		case 5:
			task5();
			break;
		default:
			std::cout << "Invalid task";
	}

	return 0;
}
