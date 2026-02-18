#include "HashTable.h"

#include <iomanip>

HashTable::HashTable(int initialCapacity) : size(0), capacity(initialCapacity)
{
	table.resize(capacity);
}

unsigned int HashTable::hashFunction(const std::string &key) const
{
	unsigned int hash = 0;
	const int p = 31;

	for (char c : key)
	{
		hash = hash * p + c;
	}

	return hash % capacity;
}

void HashTable::rehash() {
	size_t oldCapacity = capacity;
	capacity *= 2;

	std::cout << "Рехеширование. Достигнут максимальный коэффициент нагрузки: " << MAX_LOAD_FACTOR << std::endl;

	std::vector<Bucket> newTable(capacity);

	for (size_t i = 0; i < oldCapacity; ++i)
	{
		for (auto& entry : table[i])
		{
			size_t newIndex = hashFunction(entry.code);
			newTable[newIndex].push_back(std::move(entry));
		}
	}

	table = std::move(newTable);
}

void HashTable::insert(const std::string &code, const std::string &university)
{
	if (static_cast<double>(size) / static_cast<double>(capacity) > MAX_LOAD_FACTOR)
	{
		rehash();
	}

	const size_t index = hashFunction(code);

	for (auto& entry : table[index])
	{
		if (entry.code == code)
		{
			std::cout << "Элемент с заданным ключом уже существует." << std::endl;
			return;
		}
	}

	table[index].emplace_back(code, university);
	size++;

	if (table[index].size() > 1)
	{
		std::cout << "Элемент вставлен в ячейку " << index << " (КОЛЛИЗИЯ разрешена цепным методом).\n";
	}
	else
	{
		std::cout << "Элемент вставлен в ячейку " << index << ".\n";
	}
}

void HashTable::remove(const std::string &code)
{
	const size_t index = hashFunction(code);
	auto& chain = table[index];

	for (auto it = chain.begin(); it != chain.end(); ++it)
	{
		if (it->code == code)
		{
			chain.erase(it);
			size--;
			std::cout << "\n>>> Запись с ключом '" << code << "' успешно удалена из ячейки " << index << ".\n";
			return;
		}
	}

	std::cout << "Ошибка удаления. Запись с ключом " << code << " не найдена.";
}

void HashTable::search(const std::string &code) const
{
	const size_t index = hashFunction(code);
	int probe_count = 0;

	for (const auto& entry : table[index])
	{
		probe_count++;
		if (entry.code == code) {
			std::cout << "\n*** НАЙДЕНА ЗАПИСЬ *** (ячейка " << index << ", "
					  << probe_count << " проб(а) в списке):\n   ";
			entry.print();
			std::cout << std::endl;
			return;
		}
	}

	std::cout << "\n*** ОШИБКА ПОИСКА *** Запись с ключом '" << code
			  << "' не найдена (проверена ячейка " << index << ").\n";
}

void HashTable::display() const
{
	std::cout << "\n======================================================\n";
	std::cout << "           СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ (ЦЕПНОЕ ХЕШИРОВАНИЕ)\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "Записей (n): " << size
			  << ", Размер массива (m): " << capacity
			  << ", Коэф. нагрузки (n/m): " << std::fixed << std::setprecision(2) << (double)size / capacity << "\n";
	std::cout << "======================================================\n";


	for (size_t i = 0; i < capacity; ++i)
	{
		std::cout << std::setw(3) << i << ": ";
		if (table[i].empty())
		{
			std::cout << "Пусто" << std::endl;
		}
		else
		{
			bool first = true;
			for (const auto& entry : table[i])
			{
				if (!first)
				{
					std::cout << " -> ";
				}

				entry.print();
				first = false;
			}

			std::cout << " (Длина: " << table[i].size() << ")\n";
		}

		std::cout << "======================================" << std::endl;
	}
}