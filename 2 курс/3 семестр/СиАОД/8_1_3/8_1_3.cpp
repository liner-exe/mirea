#include <string>
#include <iostream>
#include <map>
#include <windows.h>

void encodeL78(std::string text)
{
	std::map<std::string, int> dict;
	int dictSize = 1;
	std::string current = "";

	std::cout << "Результат метода LZ78" << std::endl;

	for (int i = 0; i < text.length(); i++)
	{
		current += text[i];
		if (dict.find(current) == dict.end())
		{
			std::string prefix = current.substr(0, current.length() - 1);
			int index = prefix == "" ? 0 : dict[prefix];

			std::cout << "(" << index << ',' << text[i] << ')' << std::endl;

			dict[current] = dictSize++;
			current = "";
		}
	}

	if (!current.empty())
	{
		std::string prefix = current.substr(0, current.length() - 1);
		int index = prefix == "" ? 0 : dict[prefix];
		std::cout << "(" << index << ',' << "EOF" << ')' << std::endl;
	}
}

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::string data = "roporopoterropoterter";
	encodeL78(data);
	return 0;
}