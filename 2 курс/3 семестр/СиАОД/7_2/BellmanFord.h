#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

const double INF = std::numeric_limits<double>::infinity();

struct Edge
{
    int source;
    int destination;
    double weight;

    Edge(int source, int destination, double weight)
        : source(source), destination(destination), weight(weight) {}
};

class Graph
{
public:
    Graph(int v = 0) : vertices(v) {}

    void addEdge(int u, int v, double w);
    bool BellmanFord(int startNode);
    void printDistances(int startNode, const std::vector<double>& dist);

    void loadTestData();
    void inputGraph();

    void setVertices(int vert);
    int getVertices();
private:
    int vertices;
    std::vector<Edge> edges;
};

#endif //BELLMANFORD_H
