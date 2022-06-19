#include <stdio.h>
#include <string.h>

#include <iostream>

#include "Graph.hpp"

using namespace std;

Graph creatGraph(vector<vector<int>> data);

Graph creatGraph(vector<vector<int>> data) {
    Graph graph;
    for (auto row : data) {
        int from = row[0];
        int to = row[1];
        int weight = row[2];
        // 新建未出现过的Node
        if (graph.nodes.find(from) == graph.nodes.end())
            graph.nodes.emplace(from, new Node(from));
        if (graph.nodes.find(to) == graph.nodes.end())
            graph.nodes.emplace(to, new Node(to));
        // 获得已建立的Node
        Node* fromNode = graph.nodes.at(from);
        Node* toNode = graph.nodes.at(to);
        fromNode->nexts.emplace_back(toNode);
        fromNode->out++;
        toNode->in++;
        // 建立边
        Edge* newEdge = new Edge(weight, fromNode, toNode);
        fromNode->edges.emplace_back(newEdge);
        graph.edges.emplace(newEdge);
    }
    return graph;
}

int main() {
    vector<vector<int>> data(0, vector<int>(3));
    data = {{1, 2, 3},
            {2, 3, 4},
            {3, 1, 1},
            {1, 3, 2}};
    for (auto i : data)
        for (auto j : i) printf("%d,", j);
    // Graph g = creatGraph(data);
    Graph g(data);
    cout << "" << endl;
    cout << g.edges.size() << endl;
    for(auto i : g.edges){
        printf("from: %d, to: %d, weight: %d\n", i->from->value, i->to->value, i->weight);
    }
    return 0;
}