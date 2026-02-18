#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <windows.h>

std::vector<int> wordToIntegers(const std::string& sentence)
{
	std::vector<int> result;
	std::stringstream ss(sentence);
	std::string word;

	while (ss >> word)
	{
		try
		{
			int num = std::stoi(word);
			result.push_back(num);
		}
		catch (const std::invalid_argument& e)
		{
			// строка не число. Пропускаем
		}
		catch (const std::out_of_range& e)
		{
			// число слишком большое. Пропускаем
		}
	}

	return result;
}

std::vector<int> buildGoodSuffixTable(const std::string& pattern)
{
	int m = pattern.length();
	std::vector<int> goodSuffix(m + 1, m);
	std::vector<int> borderPos(m + 1, 0);

	int i = m, j = m + 1;
	borderPos[i] = j;

	while (i > 0)
	{
		while (j <= m && pattern[i - 1] != pattern[j - 1])
		{
			if (goodSuffix[j] == m)
				goodSuffix[j] = j - i;
			j = borderPos[j];
		}
		i--;
		j--;
		borderPos[i] = j;
	}

	j = borderPos[0];
	for (i = 0; i <= m; i++)
	{
		if (goodSuffix[i] == m)
			goodSuffix[i] = j;
		if (i == j)
			j = borderPos[j];
	}

	return goodSuffix;
}

std::vector<int> boyerMooreGoodSuffix(const std::string& text, const std::string& pattern, int& comparisons)
{
	std::vector<int> result;
	int n = text.length();
	int m = pattern.length();

	if (m == 0 || n == 0 || m > n)
		return result;

	std::vector<int> goodSuffix = buildGoodSuffixTable(pattern);

	int s = 0; // позиция сдвига
	comparisons = 0;

	while (s <= n - m)
	{
		int j = m - 1;

		while (j >= 0 && ++comparisons >= 0 && pattern[j] == text[s + j])
			j--;

		if (j < 0)
		{
			result.push_back(s);
			s += goodSuffix[0];
		}
		else
		{
			s += goodSuffix[j + 1];
		}
	}

	return result;
}

struct Test
{
	std::string name;
	std::string text;
	std::string pattern;

	Test(std::string name, std::string text, std::string pattern) : name(name), text(text), pattern(pattern) {}
};

void runTest(const std::string& name, const std::string& text, const std::string &pattern)
{
	std::cout << "\n--- " << name << " ---\n";

	int comparisons = 0;

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int> positions = boyerMooreGoodSuffix(text, pattern, comparisons);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	std::cout << "Текст: " << text << "\n";
	std::cout << "Паттерн: " << pattern << "\n";
	std::cout << "Найдено вхождений: " << positions.size() << "\n";

	if (!positions.empty()) {
		std::cout << "Позиции: ";
		for (int pos : positions) std::cout << pos << " ";
		std::cout << "\n";
	}

	std::cout << "Количество сравнений: " << comparisons << "\n";
	std::cout << "Время выполнения: " << duration.count() << " нс\n";
}

void runTask1Demo()
{
	std::cout << "=== Задание 1 ===" << std::endl;

	std::vector<std::string> testSentences =
	{
		"123 45 678 900 1 42",
		"100 200 триста 400 пять 600",
		"999 -50 0 75",
		"один 2 3 четыре 5"
	};

	for (const auto& sentence : testSentences)
	{
		std::cout << "Предложение: \"" << sentence << "\"" << std::endl;

		std::vector<int> numbers = wordToIntegers(sentence);

		std::cout << "Массив чисел: ";
		for (int num : numbers)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
		std::cout << "Количество чисел: " << numbers.size() << std::endl;
		std::cout << "---" << std::endl;
	}
}

void runTask2Demo()
{
	std::cout << "=== Задание 2 ===" << std::endl;

	std::vector<Test> tests = {
        {"Успешный поиск (середина)", "abcxabcdabxabcdabcdabcy", "abcdabcy" },
        {"Успешный поиск (начало)", "abcdefghijklmnop", "abc" },
        {"Успешный поиск (конец)", "abcdefghijklmnop", "nop" },
        {"Неуспешный поиск", "abcdefghijklmnop", "xyz" },
        {"Повторяющиеся символы", "aaaaaaaaaa", "aaaa" },
        {"Длинный текст", "abcabcabcabcabcabcabcabcabcabc", "abcabc" }
    };

	for (const Test& test : tests)
	{
		runTest(test.name, test.text, test.pattern);
	}
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	runTask1Demo();
	runTask2Demo();

	system("pause");

	return 0;
}