#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void task1()
{
	cout << "YourName";
}

void task2()
{
	int a, b;
	cout << "Enter (a, b): ";
	cin >> a >> b;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	if (b != 0) cout << "a / b = " << a / b << endl;
}

void task3()
{
	int b, c;
	cout << "Enter (b, c): ";
	cin >> b >> c;
	if (b == 0)
	{
		cout << "No solutions";
		return;
	}

	cout << "x = " << - c / b;
}

void task4()
{
	double a, b, c;

	cout << "Enter (a, b, c): ";
	cin >> a >> b >> c;
	double D = b * b - 4 * a * c;

	if (D > 0)
	{
		if (a == 0)
		{
			if (b != 0)
			{
				cout << "x = " << -c / b << endl;
			}

			else if (b == 0)
			{
				cout << "No solutions";
			}
		}

		else if (a != 0 && b == 0 && c == 0)
		{
			cout << "x = " << 0 << endl;
		}

		else if (b == 0)
		{
			if (a == 0)
			{
				cout << "No solutions";
			}
			
			else
			{
				if ((-c / a) > 0)
				{
					cout << "x1 = " << sqrt(((-c) / a)) << endl;
					cout << "x2 = " << -(sqrt((-c) / a)) << endl;
				}
			}
		}

		else if (c == 0)
		{
			cout << "x1 = " << 0 << endl;
			cout << "x2 = " << -b / a << endl;
		}

		else
		{
			cout << "x1 = " << (-b - sqrt(D)) / (2 * a) << endl;
			cout << "x2 = " << (-b + sqrt(D)) / (2 * a) << endl;
		}
	}

	else if (D == 0)
	{
		cout << "x1 = " << -b / (2 * a) << endl;
	}

	else if (D < 0)
	{
		cout << "No roots" << endl;
	}
}

void task5()
{
	bool isCurtainOpened, isLampOn, isDark;

	cout << "Enter states (curtain, lamp, darkness): ";
	cin >> isCurtainOpened >> isLampOn >> isDark;

	if (isCurtainOpened == true && isDark == false || isLampOn == true)
	{
		cout << "It`s bright in the room." << endl;
	}
	else
	{
		cout << "It`s dark in the room." << endl;
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
