#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

namespace utils5_1
{
	void create_test_file()
	{
		std::ofstream test_file("input.bin", std::ios::binary);

		const int NUM_COUNT = 1000000;

		for (int i = NUM_COUNT; i > 0; i--) {
			test_file << i << std::endl;
		}
		test_file.close();

		std::cout << "Создан тестовый файл с " << NUM_COUNT << " числами" << std::endl;
	}
} // utils5_1

#endif // __UTILS_H__