#include "BST.h"

#include <windows.h>

void printMenu()
{
    std::cout << "\n--- МЕНЮ (Вариант 16) ---\n";
    std::cout << "1. Добавить элемент.\n";
    std::cout << "2. Симметричный обход.\n";
    std::cout << "3. Найти сумму значений листьев.\n";
    std::cout << "4. Найти среднее арифметическое всех узлов.\n";
    std::cout << "5. Тестовые значения (10 предзаготовленных).\n";
    std::cout << "6. Вывести дерево.\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    BinarySearchTree tree;
    short choice;
    double value;

    do
    {
        printMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Введите вещественное число";
            std::cin >> value;
            tree.insert(value);
            break;
        case 2:
            tree.printInOrder();
            break;
        case 3:
            tree.printSumLeaves();
            break;
        case 4:
            tree.printAverage();
            break;
        case 5:
            tree.fillTestData();
            break;
        case 6:
            tree.visualize();
            break;
        case 0:
            std::cout << "Выход из программы...";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}