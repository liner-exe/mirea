#include <iostream>
#include <string>
#include <cmath>

void task1()
{
	int R, r, h;

	std::cout << "Enter radius (R): ";
	std::cin >> R;

	std::cout << "Enter radius (r): ";
	std::cin >> r;

	std::cout << "Enter height (h): ";
	std::cin >> h;

	if (R == 0 || r == 0 || h == 0 || R <= r)
	{
		std::cout << "Truncated cone does not exist.";
		return;
	}

	double volume = (1.0 / 3.0) * h * M_PI * (pow(R, 2) + R * r + pow(r, 2));
	double l = sqrt(pow(h, 2) + pow(R - r, 2));
	double surfaceArea = M_PI * (pow(R, 2) + pow(r, 2)) + M_PI * (R + r) * l;

	std::cout << "Volume of the truncated cone: " << volume << std::endl;
	std::cout << "Total surface area of the truncated cone: " << surfaceArea << std::endl;
}

void task2()
{
	int x, a;

	std::cout << "Enter x: ";
	std::cin >> x;

	std::cout << "Enter a: ";
	std::cin >> a;

	if (abs(x) < 1)
	{
		if (x > 0)
		{
			std::cout << "The solution is: " << a * log(abs(x));
		}
		else
		{
			std::cout << "No solutions.";
		}
	}
	else if (abs(x) >= 1)
	{
		if ((a - x * x) >= 0)
		{
			std::cout << "The solution is: " << sqrt(a - x * x);
		}
		else
		{
			std::cout << "No solutions.";
		}
	}
}

void task3()
{
	int x, y, b;

	std::cout << "Enter x: ";
	std::cin >> x;

	std::cout << "Enter y: ";
	std::cin >> y;

	std::cout << "Enter b: ";
	std::cin >> b;

	if ((b - y) > 0 && (b - x) >= 0)
	{
		std::cout << "The solution is: " << log(b - y) * sqrt(b - x);
	}
	else
	{
		std::cout << "No solutions";
	}
}

void task4()
{
	unsigned long long N;
	std::string s;

	std::cout << "Enter N: ";
	std::cin >> s;

	if ((s.find(".") != -1))
	{
		std::cout << "Invalid number";
		return;
	}
	else
	{
		N = stoull('0' + s);
	}

	if (N == 0)
	{
		std::cout << "Invalid number.";
		return;
	}
	else if (0 < N < pow(2, 64) - 1)
	{
		for (unsigned long long i = N; i <= N + 9; i++)
		{
			std::cout << i << " ";
		}
	}
	else
	{
		std::cout << "The number is too big.";
	}
}

void task5()
{
	std::cout << "x  y" << std::endl;

	for (double x = -4.0; x <= 4.0; x += 0.5)
	{
		if ((x - 1) == 0)
		{
			std::cout << "undefined" << std::endl;
		}
		else
		{
			std::cout << x << "  " << (x * x - 2 * x + 2) / (x - 1) << std::endl;
		}
	}
}

int main()
{
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
