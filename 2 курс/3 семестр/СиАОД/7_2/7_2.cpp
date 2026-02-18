#include <iostream>
#include <iomanip>
#include <windows.h>

#include "BellmanFord.h"

void printMenu()
{
    std::cout << "\n--- МЕНЮ (Вариант 16) ---\n";
    std::cout << "1. Ввести произвольный граф с клавиатуры.\n";
    std::cout << "2. Загрузить тестовый граф из задания.\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Graph graph;
    short choice;

    printMenu();
    std::cin >> choice;

    if (choice == 1)
    {
        graph.inputGraph();
    }
    else if (choice == 2)
    {
        graph.loadTestData();
    }
    else
    {
        std::cout << "Некорректный выбор. Загружен граф по умолчанию." << std::endl;
        graph.loadTestData();
    }

    if (graph.getVertices() > 0)
    {
        int startNode;
        std::cout << "Введите стартовую вершину для поиска кратчайшего " <<
                     "пути (от 1 до " << graph.getVertices() << "): " << std::endl;
        std::cin >> startNode;

        startNode--;

        if (startNode >= 0 && startNode < graph.getVertices())
        {
            graph.BellmanFord(startNode);
        }
        else
        {
            std::cout << "Некорректная стартовая вершина." << std::endl;
        }
    }
    else
    {
        std::cout << "Граф не был создан." << std::endl;
    }

    system("pause");

    return 0;
}