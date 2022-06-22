#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdio.h>

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Node;
class Edge;
class Graph;

class Node {
public:
    int value;
    int in;             // 入度
    int out;            // 出度
    list<Node *> nexts; // 发散出的直接相邻的点
    list<Edge *> edges; //
    Node(int val) :
        value(val), nexts(), edges() {
        in = 0;
        out = 0;
    };
    bool operator==(const Node &node) const {
        return &node == this;
    }
    bool operator < (const Node &node) const{
        return value < node.value;
    }
};

class Edge {
public:
    int weight;
    Node *from;
    Node *to;
    Edge(int w, Node *f = nullptr, Node *t = nullptr) :
        weight(w), from(f), to(t){};
    bool operator==(const Edge &edge) const {
        // return from == edge.from && to == edge.to;
        return &edge == this;
    }
    bool operator < (const Edge &edge)const{
        return weight < edge.weight;
    }
    // bool operator > (const Edge &edge)const{
    //     return this->weight > edge.weight;
    // }
    // char *getHash() const {
    //     char f = from == nullptr ? '#' : from->value;
    //     char t = to == nullptr ? '#' : to->value;
    //     char r[] = {f, t, '\0'};
    //     char *res = r;
    //     return res;
    // }
};
// class hash_Edge {
// public:
//     size_t operator()(const Edge &edge) const {
//         hash<char *> hs;
//         cout << edge.getHash() << endl;
//         return hs(edge.getHash()); // hash值由Edge连接的两个Node值拼接成的字符组决定
//     }
// };
// class equal_to_Edge {
// public:
//     bool operator()(const Edge &edge1, const Edge &edge2) const {
//         return edge1 == edge2;
//     }
// };

class Graph {
public:
    unordered_map<int, Node *> nodes;
    unordered_set<Edge *> edges;
    Graph(){};
    // 一种构造方法
    Graph(vector<vector<int>> data) {
        for (auto row : data) {
            int from = row[0];
            int to = row[1];
            int weight = row[2];
            // 新建未出现过的Node
            if (nodes.find(from) == nodes.end())
                nodes.emplace(from, new Node(from));
            if (nodes.find(to) == nodes.end())
                nodes.emplace(to, new Node(to));
            // 获得已建立的Node
            Node *fromNode = nodes.at(from);
            Node *toNode = nodes.at(to);
            fromNode->nexts.emplace_back(toNode);
            fromNode->out++;
            toNode->in++;
            // 建立边
            Edge *newEdge = new Edge(weight, fromNode, toNode);
            fromNode->edges.emplace_back(newEdge);
            edges.emplace(newEdge);
        }
    }
    Node* getNode(int value){
        return nodes.at(value);
    }
};

#endif

// Graph creatGraph(int[][])

// int main() {
//     Node *n1 = new Node('a');
//     Node *n2 = new Node('b');
//     Edge *e1 = new Edge(0, n1);
//     Edge *e2 = new Edge(0, n1, n2);
//     Edge *e3 = new Edge(0, n2, n1);
//     cout << e1->getHash() << endl;
//     cout << e2->getHash() << endl;
//     unordered_map<Edge *, int> se;
//     unordered_set<Edge*> set;
//     se.emplace(e1, 5);
//     se.emplace(e1, 6);
//     se.emplace(e2, 2);
//     set.emplace(e1);
//     set.emplace(e1);
//     set.emplace(e2);
//     printf("len: %d, has: %s\n", set.size(), set.find(e3) == set.end() ? "false": "true");
//     cout << se.size() << endl;
//     cout << se.at(e2) << endl;
//     printf("%s", e2 == e2 ? "true" : "false");
//     return 0;
// }