#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

struct Symbol
{
	wchar_t character;
	int count;
	std::string code;

	Symbol(wchar_t ch, int count) : character(ch), count(count) {}
};

bool compareSymbols(Symbol& a, Symbol& b)
{
	return a.count > b.count;
}

void shannonFano(int start, int end, std::vector<Symbol>& symbols)
{
	if (start >= end) return;

	int split = start;
	long long total = 0;

	for (int i = start; i <= end; i++)
	{
		total += symbols[i].count;
	}

	long long currentSum = 0;
	long long diff = total;

	for (int i = start; i < end; i++)
	{
		currentSum += symbols[i].count;
		if (std::abs(total - 2 * currentSum) < diff)
		{
			diff = abs(total - 2 * currentSum);
			split = i;
		}
		else
		{
			break;
		}
	}

	for (int i = start; i <= split; i++)
	{
		symbols[i].code += '0';
	}

	for (int i = split + 1; i <= end; i++)
	{
		symbols[i].code += '1';
	}

	shannonFano(start, split, symbols);
	shannonFano(split + 1, end, symbols);
}

void processFano(std::wstring text)
{
	std::map<wchar_t, int> frequency;
	for (wchar_t c : text)
	{
		frequency[c]++;
	}

	std::vector<Symbol> symbols;
	for (const auto& pair : frequency)
	{
		symbols.emplace_back(pair.first, pair.second);
	}

	std::sort(symbols.begin(), symbols.end(), compareSymbols);
	shannonFano(0, symbols.size() - 1, symbols);

	std::wcout << L"Результаты Шеннон-Фано" << std::endl;
	std::wcout << L"Символ | Количество | Код | Биты" << std::endl;

	for (const auto& s : symbols) {
		if (s.character == L' ') std::wcout << L"пробел";
		else std::wcout << s.character;

		std::wcout << L" | " << s.count << L" | ";
		for (const auto& c : s.code) std::wcout << c;
		std::wcout << L" | " << s.code.length() * s.count << std::endl;
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	processFano(L"Зуба зуба, зуба зуба, Зуба дони дони мэ, А шарли буба раз два три, А ми раз два три замри.");
	return 0;
}