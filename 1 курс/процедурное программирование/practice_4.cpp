#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>
#include <Windows.h>

#define PI 3.14

void task1()
{
    std::cout << "Enter 10 numbers to find sum: " << std::endl;

    std::ofstream fout("task1.txt");
    if (fout.is_open())
    {
        double input;
        for (int i = 0; i < 10; i++)
        {
            std::cin >> input;
            fout << input << std::endl;
        }
        fout.close();
    }

    std::ifstream fin("task1.txt");
    double number;
    double summ = 0.0f;
    if (fin.is_open())
    {
        while (fin >> number)
        {
            summ += number;
        }
    }
    std::cout << "Result: " << summ;
}

void task2()
{
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    if (x > 0) x = 1;
    else if (x == 0) x = 0;
    else if (x < 0) x = -1;

    std::cout << x;
}

void rectangle()
{
    double a, b;
    std::cout << "Enter sides (a, b): ";
    std::cin >> a >> b;
    if (a <= 0 || b <= 0) { std::cout << "Rectangle does not exist"; return; }
    std::cout << a * b;
}

void triangle()
{
    double a, b, c;
    std::cout << "Enter (a, b, c): ";
    std::cin >> a >> b >> c;

    if (((a + b <= c) || (a + c <= b) || (b + c <= a)))
    {
        std::cout << "Triangle does not exist";
    }
    else
    {
        double p = (a + b + c) / 2;
        std::cout << sqrt(p * (p - a) * (p - b) * (p - c));
    }
}

void circle()
{
    std::cout << "Enter radius: ";
    double R;
    std::cin >> R;
    if (R <= 0) { std::cout << "Circle does not exist"; return; }

    std::cout << PI * pow(R, 2);
}

void task3()
{
    std::cout << "Enter the number of the shape: 1 - rectangle, 2 - triangle, 3 - circle: ";
    short shape;
    std::cin >> shape;
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
        std::cout << "Invalid shape";
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
                if (j < 8) std::cout << "* ";
                else std::cout << '_';
            }
            std::cout << '\n';
        }
        else
        {
            for (int k = 0; k < 38; k++)
            {
                std::cout << '_';
            }
            std::cout << '\n';
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

bool ValidationOfRomanNumerals(std::string str)
{

    const std::regex pattern("^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");


    if (str.empty()) {
        return false;
    }


    if (regex_match(str, pattern)) {
        return true;
    }
    else {
        return false;
    }
}

int value(char r)
{
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;

    return -1;
}

int romanToDecimal(std::string& str)
{
    int res = 0;


    for (int i = 0; i < str.length(); i++)
    {

        int s1 = value(str[i]);

        if (i + 1 < str.length())
        {

            int s2 = value(str[i + 1]);


            if (s1 >= s2)
            {

                res = res + s1;
            }
            else
            {

                res = res + s2 - s1;
                i++;
            }
        }
        else {
            res = res + s1;
        }
    }
    return res;
}

void task6()
{
    std::cout << "Enter roman number: ";
    std::string str;
    std::cin >> str;
    if (ValidationOfRomanNumerals(str)) {
        std::cout << "Result: " << romanToDecimal(str) << std::endl;
    }
    else {
        std::cout << "Wrong data entered.";
    }
}

void random_num(int m, int i, int c) {
    int si = 0;
    int quantity;
    std::cin >> quantity;
    if (quantity < 0) {
        std::cout << "Wrong data entered";
        exit(0);
    }
    for (int b = 0; b < quantity; b++) {
        si = (m * si + i) % c;
        std::cout << si << std::endl;
    }
}

void task7()
{
    std::cout << "Enter random mode (1 or 2): ";
    int mode;
    std::cin >> mode;
    if (mode != 1 and mode != 2) {
        std::cout << "Wrong data entered";
        exit(0);
    }
    if (mode == 1) {
        random_num(37, 3, 64);
    }
    if (mode == 2) {
        random_num(25173, 849, 65537);
    }
}

void task8()
{
    double A[3][4]{}, B[4][2]{}, C[3][2]{};

    std::cout << "Enter matrix A:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cin >> A[i][0] >> A[i][1] >> A[i][2] >> A[i][3];

        if (A[i][0] < 0 or A[i][1] < 0 or A[i][2] < 0 or A[i][3] < 0)
        {
            std::cout << "Values must be positive.";
            return;
        }
    }

    std::cout << "Enter matrix B:" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cin >> B[i][0] >> B[i][1];

        if (B[i][0] < 0 or B[i][1] < 0)
        {
            std::cout << "Values must be positive.";
            return;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    std::cout << "Matrix C: " << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << C[i][0] << " " << C[i][1] << std::endl;
    }

    double biggestIncome = std::max(std::max(C[0][0], C[1][0]), C[2][0]);
    double lowestIncome = std::min(std::min(C[0][0], C[1][0]), C[2][0]);

    for (int i = 0; i < 3; i++)
    {
        if (C[i][0] == biggestIncome) std::cout << "The merchant with the biggest income n: " << i + 1 << std::endl;
        if (C[i][0] == lowestIncome) std::cout << "The merchant with the lowest income n: " << i + 1 << std::endl;
    }

    double biggestFees = std::max(std::max(C[0][1], C[1][1]), C[2][1]);
    double lowestFees = std::min(std::min(C[0][1], C[1][1]), C[2][01]);

    for (int i = 0; i < 3; i++)
    {
        if (C[i][1] == biggestFees) std::cout << "The merchant with the biggest comission fees n: " << i + 1 << std::endl;
        if (C[i][1] == lowestFees) std::cout << "The merchant with the lowest comission fees n: " << i + 1 << std::endl;
    }

    std::cout << "Total income: " << C[0][0] + C[1][0] + C[2][0] << std::endl;
    std::cout << "Total commision fees: " << C[0][1] + C[1][1] + C[2][1] << std::endl;
    std::cout << "Total: " << C[0][0] + C[1][0] + C[2][0] + (C[0][1] + C[1][1] + C[2][1]) << std::endl;
}

double convertToDecimal(std::string number, short base)
{
    std::map<char, int> values{
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
        {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},
        {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
    };

    double result = 0.0;
    bool isFraction = false;
    double fraction = 0.0;

    size_t dotPosition = number.find('.');

    for (int i = 0; i < (dotPosition == std::string::npos ? number.size() : dotPosition); i++)
    {
        result = result * base + values[number[i]];
    }
    
    if (dotPosition != std::string::npos)
    {
        for (int i = dotPosition + 1; i < number.size(); i++)
        {
            fraction += values[number[i]] * (1 / pow(base, i - dotPosition));
        }
    }

    return result + fraction;
}

std::string convertFromDecimal(double number, short base)
{
    std::vector<char> values = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    std::string result;
    auto intPart = static_cast<long long>(number);
    double fracPart = number - intPart;

    if (intPart == 0)
    {
        result += "0";
    }
    else
    {
        while (intPart > 0)
        {
            result += values[intPart % base];
            intPart /= base;
        }
    }

    reverse(result.begin(), result.end());

    if (fracPart > 0)
    {
        result += ".";
        
        while (fracPart > 0)
        {
            fracPart *= base;
            int FracDigit = static_cast<int>(fracPart);
            result += values[FracDigit];
            fracPart -= FracDigit;
        }
    }

    return result;
}

void task9()
{
    std::string num;
    short oldBase;
    short newBase;
    std::cin >> num >> oldBase >> newBase;

    if ((oldBase > 16 || oldBase < 2) || (newBase > 16 || newBase < 2))
    {
        std::cout << "Base must be from 2 to 16";
        return;
    } 

    if (num[0] == '0') {
        std::cout << "Wrong number";
        return;
    }

    if (num == "0") {
        std::cout << "0";
        return;
    }

    int countOfDots = 0;
    std::string chars = "0123456789ABCDEF";
    for (auto c : num)
    {
        if (chars.find(c) == std::string::npos && c != '.')
        {
            std::cout << "Wrong character found";
            return;
        }

        if (isdigit(c)) {
            if (c - '0' >= oldBase) {
                std::cout << "Wrong character found";
                return;
            }
        }
        else if (isalpha(c)) {
            if (toupper(c) - 'A' + 10 >= oldBase) {
                std::cout << "Wrong character found";
                return;
            }
        }

        if (c == '.')
        {
            countOfDots++;
        }
    }

    if (countOfDots > 1)
    {
        std::cout << "Wrong number";
        return;
    }


    double decNumber = convertToDecimal(num, oldBase);

    if (newBase == 10)
    {
        std::cout << decNumber;
        return;
    }
    else
    {
        std::string newBaseNumber = convertFromDecimal(decNumber, newBase);
        std::cout << newBaseNumber;
    }
}

int main()
{
    std::cout << "Enter number of task: ";
    short taskNumber;
    std::cin >> taskNumber;

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
    case 6:
        task6();
        break;
    case 7:
        task7();
        break;
    case 8:
        task8();
        break;
    case 9:
        task9();
        break;
    }

    return 0;
}
