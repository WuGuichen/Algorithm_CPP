#include "Graph.hpp"

using namespace std;

class MySets {
   public:
    unordered_map<Node*, list<Node*>> setMap;
    // 初始化每一个结点的集合中只有自身
    MySets(list<Node*> nodes) {
        for (Node* cur : nodes) {
            list<Node*> set;
            set.emplace_back(cur);
            setMap.emplace(cur, set);
        }
    }
    inline bool isSameSet(Node* from, Node* to) {
        return setMap.at(from) == setMap.at(to);
    }
    // 将两个结点的集合合并成一样的
    void unionSet(Node* from, Node* to) {
        list<Node*>* fromSet = &setMap.at(from);  // 因为要改，所以用引用
        list<Node*> toSet = setMap.at(to);
        for (Node* toNode : toSet) {
            fromSet->emplace_back(toNode);
            setMap[toNode] = *fromSet;  // 覆盖原来的值
        }
    }
};

int main() {
    vector<vector<int>> data;
    data = {{1, 3, 4}, {3, 1, 4}, {2, 3, 8}, {3, 2, 8}, {3, 4, 1}, {4, 3, 1}, {1, 2, 3}, {2, 1, 3}};
    Graph graph(data);
    list<Node*> nodes;
    for (auto node : graph.nodes) {
        nodes.emplace_back(node.second);
    }
    MySets ms(nodes);
    bool isSame = false;
    ms.unionSet(graph.getNode(1), graph.getNode(3));
    for (auto i : ms.setMap){
        printf("Node: %d; Set: ", i.first->value);
        for(auto j : i.second){
            printf("%d,", j->value);
        }
        printf("\n");
    }
    // // 自定义类指针无法通过重载<就可以排好序
    // auto cmp = [](Edge*& e1, Edge*& e2) { return e1->weight < e2->weight; };
    // priority_queue<Edge*, vector<Edge*>, decltype(cmp)> edges(cmp);
    // for (auto edge : graph.edges)
    //     edges.emplace(edge);
    // while (!edges.empty()) {
    //     printf("%d_", edges.top()->weight);
    //     edges.pop();
    // }
    return 0;
}