#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cctype>
#include <Windows.h>

using namespace std;

void task1()
{
	double S, n, p;
	double m;

	cout << "Enter S: ";
	cin >> S;

	cout << "Enter p: ";
	cin >> p;

	cout << "Enter n: ";
	cin >> n;

	if ((n > 0 && n <= 30) && (p > 0 && p < 101))
	{
		double r = p / 100;
		m = (S * r * pow((1 + r), n)) / (12 * (pow((1 + r), n) - 1));
		
		cout << "m = " << m;
	}
	else
	{
		if (p == 0)
		{
			m = S / (12 * n);
			cout << "m = " << m;
		}
		else
		{
			cout << "Error!";
		}
	}
}

void task2()
{
	double S, m0, n;
	double r, m;

	cout << "Enter S: ";
	cin >> S;

	cout << "Enter m0: ";
	cin >> m0;

	cout << "Enter n: ";
	cin >> n;

	for (double p = 0; p < 101; p += 0.1)
	{
		r = p / 100;
		m = (S * r * pow((1 + r), n)) / (12 * (pow((1 + r), n) - 1));

		if (abs(m - m0) < 0.01)
		{
			cout << p;
			return;
		}
		else
		{
			continue;
		}

		cout << "Error has occurred";
	}
}

void task3()
{
	cin.ignore();

	char buffer[1000];
	string input;
	
	cout << "Enter string: ";
	getline(cin, input);

	ofstream fout("task3_4.txt");

	if (fout.is_open())
	{
		fout << input;
		fout.close();
	}
	else
	{
		cout << "Error";
	}

	ifstream fin("task3_4.txt");

	if (fout.is_open())
	{
		fin.getline(buffer, 1000);
		fin.close();
	}
	else
	{
		cout << "Error";
	}

	cout << "Result: " << buffer;
}

void task4()
{
	string digits = "0123456789";
	char buffer[1000];

	ifstream fin("task3_4.txt");

	if (fin.is_open())
	{
		fin.getline(buffer, 1000);
		fin.close();
	}
	else
	{
		cout << "Error";
		return;
	}

	cout << "Filtered string: ";

	for (int i = 0; i <= 1000; i++)
	{
		if (buffer[i] == '\0')
		{
			return;
		}
		else
		{
			if (digits.find(buffer[i]) != -1)
			{
				cout << buffer[i];
			}
		}
	}
}

void task5()
{
	cin.ignore();

	string str;

	cout << "Enter string: ";
	getline(cin, str);

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

	cout << "Sorted string: " << str;
}

int main()
{
	system("chcp 1251");
	cout << "Enter number of task: ";

	short task;
	cin >> task;

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
			cout << "Invalid task";
	}

	return 0;
}
