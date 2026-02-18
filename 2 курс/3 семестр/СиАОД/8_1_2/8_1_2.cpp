#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

struct LZ77Code
{
	int offset;
	int length;
	char nextChar;

	LZ77Code(int offset, int len, char nextChar) : offset(offset), length(len), nextChar(nextChar) {}
};

void encodeL77(std::string text, int slidingWindowSize)
{
	int n = text.length();
	std::vector<LZ77Code> result;
	int cursor = 0;

	while (cursor < n)
	{
		int best_length = 0;
		int best_offset = 0;

		int start = std::max(0, cursor - slidingWindowSize);
		for (int i = start; i < cursor; i++)
		{
			int length = 0;
			while (cursor + length < n && text[i + length] == text[cursor + length])
			{
				length++;
			}

			if (length >= best_length)
			{
				best_length = length;
				best_offset = cursor - i;
			}
		}

		char next = (cursor + best_length < n) ? text[cursor + best_length] : '#';
		result.emplace_back(best_offset, best_length, next);
		cursor += best_length + 1;
	}

	std::cout << "Результат метода LZ77" << std::endl;
	for (LZ77Code code : result)
	{
		std::cout << "(" << code.offset << ',' << code.length << ',' << code.nextChar << ")" << std::endl;
	}
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	int windowSize = 100;
	std::string data = "0100101010010000101";
	encodeL77(data, windowSize);
	return 0;
}