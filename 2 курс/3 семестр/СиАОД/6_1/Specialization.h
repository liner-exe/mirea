#ifndef SPECIALIZATION_H
#define SPECIALIZATION_H

#include <iostream>
#include <ostream>
#include <string>
#include <utility>

struct Specialization
{
	std::string code;
	std::string university;

	Specialization(std::string code, std::string university) : code(std::move(code)), university(std::move(university)) {}

	void print() const
	{
		std::cout << "ВУЗ: " << university << ", СПЕЦИАЛИЗАЦИЯ: " << code << std::endl;
	}
};

#endif //SPECIALIZATION_H