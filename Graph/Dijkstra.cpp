#include "Graph.hpp"

using namespace std;

unordered_map<Node*, int> dijkstra1(Node* head);
Node* getMinDisAndUnselectedNode(unordered_map<Node*,int>,unordered_set<Node*> touchedNodes);

unordered_map<Node*, int> dijkstra1(Node* head){
    unordered_map<Node*, int> disMap;
    disMap.emplace(head, 0);
    unordered_set<Node*> selectedNodes;  // 已经求过距离的Node
    Node* minNode = getMinDisAndUnselectedNode(disMap, selectedNodes);
    while(minNode != nullptr){   // 当无结点可选了跳出
        int dis = disMap.at(minNode);
        for(Edge* edge : minNode->edges){
            Node* toNode = edge->to;
            if(disMap.find(toNode) == disMap.end()){
                disMap.emplace(toNode, dis + edge->weight);
            }
            int minDis = min(disMap.at(toNode), dis+edge->weight);  // 原点距离加权重
            disMap[edge->to] = minDis;
        }
        selectedNodes.emplace(minNode);  // 标记以求过该Node
        minNode = getMinDisAndUnselectedNode(disMap, selectedNodes);
    }
    return disMap;
}

Node* getMinDisAndUnselectedNode(unordered_map<Node*,int> disMap,unordered_set<Node*> touchedNodes){
    Node* minNode = nullptr;
    int minDis = INT_MAX;
    for(auto m : disMap){
        Node* node = m.first;
        int dis = m.second;
        if(touchedNodes.find(node) == touchedNodes.end() && dis < minDis){
            minNode = node;
            minDis = dis;
        }
    }
    return minNode;
}

int main(){
    vector<vector<int>> data;
    data = {{1, 3, 4},{3, 1, 4}, {2, 3, 8},{3, 2, 8}, {3, 4, 1},{4, 3, 1}, {1, 2, 3},{2,1,3}, {1, 4, 2},{4,1,2}};
    Graph graph(data);
    unordered_map<Node*, int> disMap = dijkstra1(graph.getNode(3));
    for(auto i : disMap){
        printf("Node: %d, Distance: %d", i.first->value, i.second);
    }
    return 0;
}