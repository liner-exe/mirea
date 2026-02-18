#include "BellmanFord.h"

void Graph::addEdge(int u, int v, double w)
{
    edges.emplace_back(u, v, w);
}

bool Graph::BellmanFord(int startNode)
{
    std::vector<double> distance(vertices, INF);
    distance[startNode] = 0;

    for (int i = 1; i <= vertices; ++i)
    {
        bool updated = false;
        for (const auto& edge : edges)
        {
            int u = edge.source;
            int v = edge.destination;
            double w = edge.weight;

            if (distance[u] != INF &&
                distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                updated = true;
            }
        }

        if (!updated) break;
    }

    for (const auto& edge : edges)
    {
        int u = edge.source;
        int v = edge.destination;
        double w = edge.weight;

        if (distance[u] != INF && distance[u] + w < distance[v])
        {
            std::cout << "Граф содержит отрицательный цикл!" << std::endl;
            return false;
        }
    }

    printDistances(startNode, distance);
    return true;
}

void Graph::printDistances(int startNode, const std::vector<double>& dist)
{
    std::cout << "\n--- Результаты алгоритма Беллмана-Форда ---\n";
    std::cout << "Начальная вершина: " << startNode + 1 << std::endl;
    std::cout << "------------------------------------------\n";

    for (int i = 0; i < vertices; ++i) {
        std::cout << "Кратчайший путь до вершины " << i + 1 << ": ";
        if (dist[i] == INF) {
            std::cout << "НЕДОСТИЖИМ" << std::endl;
        } else {
            std::cout << std::fixed << std::setprecision(2) << dist[i] << std::endl;
        }
    }
}

void Graph::loadTestData()
{
    std::cout << "Создание тестового графа..." << std::endl;

    vertices = 8;

    addEdge(0, 1, 23.0); addEdge(1, 0, 23.0);
    addEdge(0, 2, 12.0); addEdge(2, 0, 12.0);
    addEdge(1, 2, 25.0); addEdge(2, 1, 25.0);
    addEdge(1, 4, 22.0); addEdge(4, 1, 22.0);
    addEdge(1, 7, 35.0); addEdge(7, 1, 35.0);
    addEdge(2, 3, 18.0); addEdge(3, 2, 18.0);
    addEdge(3, 5, 20.0); addEdge(5, 3, 20.0);
    addEdge(4, 6, 14.0); addEdge(6, 4, 14.0);
    addEdge(4, 5, 23.0); addEdge(5, 4, 23.0);
    addEdge(5, 6, 24.0); addEdge(6, 5, 24.0);
    addEdge(6, 7, 16.0); addEdge(7, 6, 16.0);
}

void Graph::inputGraph()
{
    int edgesCount;
    double weight;
    int u, v;

    std::cout << "--- Ввод произвольного графа ---" << std::endl;
    std::cout << "Введите общее количество вершин: ";
    std::cin >> vertices;

    if (vertices <= 0)
    {
        std::cout << "Некорректное количество вершин. Ввод графа прерван." << std::endl;
        vertices = 0;
        edges.clear();
        return;
    }

    std::cout << "Введите общее количество неориентированных ребер: ";
    std::cin >> edgesCount;

    edges.clear();

    std::cout << "Введите ребра в формате: [начальная вершина] [конечная вершина]" <<
        " [вес] " << std::endl;
    std::cout << "Используйте вершины с номерами от 1 до " << vertices << std::endl;

    for (int i = 0; i < edgesCount; ++i)
    {
        std::cout << "Ребро " << i + 1 << ": ";
        if (!(std::cin >> u >> v >> weight))
        {
            std::cout << "Ошибка ввода. Создание графа прервано." << std::endl;
            break;
        }

        u--, v--;

        if (u >= 0 && u < vertices && v >= 0 && v < vertices)
        {
            addEdge(u, v, weight);
            addEdge(v, u, weight);
        }
        else
        {
            std::cout << "Ошибка. Некорректный номер вершины. Ребро пропущено" << std::endl;
        }
    }

    std::cout << "Ввод графа завершен. Общее количество ориентированных ребер: "
                << edges.size() << std::endl;
}

void Graph::setVertices(int vert)
{
    vertices = vert;
}

int Graph::getVertices()
{
    return vertices;
}