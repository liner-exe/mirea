#include <iostream>
#include <string>
#include <cmath>

#define PI 3.14

using namespace std;

void task1()
{
	int R, r, h;

	cout << "Enter radius (R): ";
	cin >> R;

	cout << "Enter radius (r): ";
	cin >> r;

	cout << "Enter height (h): ";
	cin >> h;

	if (R == 0 || r == 0 || h == 0 || R <= r)
	{
		cout << "Truncated cone does not exist.";
		return;
	}

	double volume = (1.0 / 3.0) * h * PI * (pow(R, 2) + R * r + pow(r, 2));
	double l = sqrt(pow(h, 2) + pow(R - r, 2));
	double surfaceArea = PI * (pow(R, 2) + pow(r, 2)) + PI * (R + r) * l;

	cout << "Volume of the truncated cone: " << volume << endl;
	cout << "Total surface area of the truncated cone: " << surfaceArea << endl;
}

void task2()
{
	int x, a;

	cout << "Enter x: ";
	cin >> x;

	cout << "Enter a: ";
	cin >> a;

	if (abs(x) < 1)
	{
		if (x > 0)
		{
			cout << "The solution is: " << a * log(abs(x));
		}
		else
		{
			cout << "No solutions.";
		}
	}
	else if (abs(x) >= 1)
	{
		if ((a - x * x) >= 0)
		{
			cout << "The solution is: " << sqrt(a - x * x);
		}
		else
		{
			cout << "No solutions.";
		}
	}
}

void task3()
{
	int x, y, b;

	cout << "Enter x: ";
	cin >> x;

	cout << "Enter y: ";
	cin >> y;

	cout << "Enter b: ";
	cin >> b;

	if ((b - y) > 0 && (b - x) >= 0)
	{
		cout << "The solution is: " << log(b - y) * sqrt(b - x);
	}
	else
	{
		cout << "No solutions";
	}
}

void task4()
{
	unsigned long long N;
	string s;

	cout << "Enter N: ";
	cin >> s;

	if ((s.find(".") != -1))
	{
		cout << "Invalid number";
		return;
	}
	else
	{
		N = stoull('0' + s);
	}

	if (N == 0)
	{
		cout << "Invalid number.";
		return;
	}
	else if (0 < N < pow(2, 64) - 1)
	{
		for (unsigned long long i = N; i <= N + 9; i++)
		{
			cout << i << " ";
		}
	}
	else
	{
		cout << "The number is too big.";
	}
}

void task5()
{
	cout << "x  y" << endl;

	for (double x = -4.0; x <= 4.0; x += 0.5)
	{
		if ((x - 1) == 0)
		{
			cout << "undefined" << endl;
		}
		else
		{
			cout << x << "  " << (x * x - 2 * x + 2) / (x - 1) << endl;
		}
	}
}

int main()
{
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
