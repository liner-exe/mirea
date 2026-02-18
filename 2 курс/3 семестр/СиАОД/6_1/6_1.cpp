#include <iostream>
#include <windows.h>

#include "HashTable.h"

void fill_demo(HashTable& table)
{
	table.insert("09.03.01", "МГТУ ИМ БАУМАНА");
	table.insert("38.03.02", "ВШЭ");
	table.insert("40.05.01", "МГУ");
	table.insert("09.03.03", "ИТМО");
	table.insert("01.03.01", "СПбГУ");
}

void show_menu()
{
	std::cout << "\n*** МЕНЮ ХЕШ-ТАБЛИЦЫ (Цепное хеширование) ***\n";
	std::cout << "1. Вставить запись (Код, ВУЗ)\n";
	std::cout << "2. Поиск по Коду специальности\n";
	std::cout << "3. Удаление по Коду специальности\n";
	std::cout << "4. Вывести таблицу\n";
	std::cout << "5. Заполнить таблицу тестовыми данными.\n";
	std::cout << "6. Выход\n";
	std::cout << "Выберите действие (1-6): ";
}

void pause()
{
	std::cout << std::endl << "Нажмите Enter, чтобы продолжить...";
	std::cin.ignore(256, '\n');
	std::cin.get();
	system("cls");
}

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(CP_UTF8);

	HashTable table(8);

	short choice;
	std::string key, name;

	while (true)
	{
		show_menu();
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
			case 1:
				std::cout << "Введите код специальности: ";
				std::cin >> key;
				std::cout << "Введите название вуза: ";
				std::cin >> name;

				table.insert(key, name);
				pause();
				break;
			case 2:
				std::cout << "Введите код специальности, который необходимо найти: ";
				std::cin >> name;
				table.search(name);
				pause();
				break;
			case 3:
				std::cout << "Введите код специальности, который необходимо удалить: ";
				std::cin >> name;
				table.remove(name);
				pause();
				break;
			case 4:
				table.display();
				pause();
				break;
			case 5:
				fill_demo(table);
				pause();
				break;
			case 6:
				std::cout << "Завершение работы..." << std::endl;
				pause();
				return 0;
			default:
				std::cout << "Неизвестная команда. Попробуйте ещё раз." << std::endl;
				pause();
		}
	}
}