#include <iostream>
#include <cmath>
#include <fstream>
#include <Windows.h>

#define PI 3.14

using namespace std;

// TODO
// tasks: 6, 7, 8, 9

void task1()
{
    double input;
    cout << "Enter 10 numbers to find sum: " << endl;

    ofstream fout("task1.txt");
    if (fout.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            cin >> input;
            fout << input << endl;
        }
        fout.close();
    }

    ifstream fin("task1.txt");
    double number;
    double summ = 0.0f;
    if (fin.is_open())
    {
        while (fin >> number)
        {
            summ += number;
        }
    }
    cout << "Result: " << summ;
}

void task2()
{
    double x;
    cout << "Enter x: ";
    cin >> x;

    if (x > 0) x = 1;
    else if (x == 0) x = 0;
    else if (x < 0) x = -1;

    cout << x;
}

void rectangle()
{
    double a, b;
    cout << "Enter sides (a, b): ";
    cin >> a >> b;
    if (a <= 0 || b <= 0) { cout << "Rectangle does not exist"; return; }
    cout << a * b;
}

void triangle()
{
    double a, b, c;
    cout << "Enter (a, b, c): ";
    cin >> a >> b >> c;

    if (((a + b <= c) || (a + c <= b) || (b + c <= a)))
    {
        cout << "Triangle does not exist";
    }
    else
    {
        double p = (a + b + c) / 2;
        cout << sqrt(p * (p - a) * (p - b) * (p - c));
    }
}

void circle()
{
    cout << "Enter radius: ";
    double R;
    cin >> R;
    if (R <= 0) { cout << "Circle does not exist"; return; }

    cout << PI * pow(R, 2);
}

void task3()
{
    cout << "Enter the number of the shape: 1 - rectangle, 2 - triangle, 3 - circle: ";
    short shape;
    cin >> shape;
    switch (shape)
    {
    case 1:
        rectangle();
        break;
    case 2:
        triangle();
        break;
    case 3:
        circle();
        break;
    default:
        cout << "Invalid shape";
        break;
    }
}

void task4()
{
    for (int i = 0; i < 13; i++)
    {
        if (i < 6)
        {
            for (int j = 0; j < 30; j++)
            {
                if (j < 8) cout << "* ";
                else cout << '_';
            }
            cout << '\n';
        }
        else
        {
            for (int k = 0; k < 38; k++)
            {
                cout << '_';
            }
            cout << '\n';
        }
    }
}

void task5()
{
    HWND hWnd = GetConsoleWindow();
    HDC hDC = GetDC(hWnd);

    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(194, 209, 29));
    SelectObject(hDC, Pen);

    for (double x = -13.0f; x <= 37.0f; x += 0.001f)
    {
        MoveToEx(hDC, 20 * x + 250, -20 * sin(x) + 200, NULL);
        LineTo(hDC, 20 * x + 250, -20 * sin(x) + 200);
    }

    Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    SelectObject(hDC, Pen);
    MoveToEx(hDC, 0, 200, NULL);
    LineTo(hDC, 1000, 200);
    MoveToEx(hDC, 500, 0, NULL);
    LineTo(hDC, 500, 500);

    ReleaseDC(hWnd, hDC);
    
    while (true) { Sleep(0); }
}

int main()
{
    short taskNumber;
    cin >> taskNumber;

    switch (taskNumber)
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
    }

    return 0;
}
