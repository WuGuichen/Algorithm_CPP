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
        // return setMap.at(from) == setMap.at(to);
        for(Node* n : setMap.at(to)) {
            if(n == from) return true;
        }
        for(Node* n : setMap.at(from)) {
            if(n == to) return true;
        }
        return false;
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

unordered_set<Edge*> kruskalMST(Graph graph);
unordered_set<Edge*> primMST(Graph graph);

unordered_set<Edge*> kruskalMST(Graph graph){
    list<Node*> nodes;
    for(auto i : graph.nodes){
        nodes.emplace_back(i.second);
    }
    MySets unionSet(nodes);
    // 根据边权值从小到大排序的优先级队列
    const auto cmp = [](Edge*& e1, Edge*& e2) { return e1->weight > e2->weight; };
    priority_queue<Edge*, vector<Edge*>, decltype(cmp)> priorityQueue(cmp);
    for(Edge* edge : graph.edges) priorityQueue.emplace(edge);  // M条边，O(logM)
    unordered_set<Edge*> res;
    while(!priorityQueue.empty()){
        Edge* edge = priorityQueue.top();
        priorityQueue.pop();
        if(!unionSet.isSameSet(edge->from, edge->to)){
            res.emplace(edge);
            unionSet.unionSet(edge->from, edge->to);
        }
    }
    for (auto i : unionSet.setMap){
        printf("\nNode: %d; Set: ", i.first->value);
        for(auto j : i.second){
            printf("%d,", j->value);
        }
    }
    printf("\n");
    return res;
}

unordered_set<Edge*> primMST(Graph graph){
    // 解锁的边进入小根堆
    const auto cmp = [](Edge*& e1, Edge*& e2) { return e1->weight > e2->weight; };
    priority_queue<Edge*, vector<Edge*>, decltype(cmp)> priorityQueue(cmp);
    unordered_set<Node*> set;  // 检查Node是否添加过
    unordered_set<Edge*> res;  // 依次挑选的边
    for(auto i : graph.nodes){
        Node* node = i.second;
        if(set.find(node) == set.end()){
            set.emplace(node);    // 加入新Node
            for(Edge* edge : node->edges){  // 解锁所有Node连的边
                priorityQueue.emplace(edge);
            }
            while(!priorityQueue.empty()){
                Edge* edge = priorityQueue.top();
                priorityQueue.pop();
                Node* toNode = edge->to;   // 可能的新Node
                if(set.find(toNode) == set.end()){
                    set.emplace(toNode);
                    res.emplace(edge);
                    for(Edge* nextEdge : toNode->edges){
                        priorityQueue.emplace(nextEdge);
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    vector<vector<int>> data;
    data = {{1, 3, 4},{3, 1, 4}, {2, 3, 8},{3, 2, 8}, {3, 4, 1},{4, 3, 1}, {1, 2, 3},{2,1,3}, {1, 4, 2},{4,1,2}};
    Graph graph(data);
    // unordered_set<Edge*> res = kruskalMST(graph);
    unordered_set<Edge*> res = primMST(graph);
    printf("res: ");
    for(auto i : res){
        printf("%d, ", i->weight);
    }

    // ====== test: ======

    // list<Node*> nodes;
    // for (auto node : graph.nodes) {
    //     nodes.emplace_back(node.second);
    // }
    // MySets ms(nodes);
    // bool isSame = false;
    // ms.unionSet(graph.getNode(1), graph.getNode(3));
    // for (auto i : ms.setMap){
    //     printf("\nNode: %d; Set: ", i.first->value);
    //     for(auto j : i.second){
    //         printf("%d,", j->value);
    //     }
    // }
    // // 自定义类指针无法通过重载<就可以排好序
    // const auto cmp = [](Edge*& e1, Edge*& e2) { return e1->weight > e2->weight; };
    // priority_queue<Edge*, vector<Edge*>, decltype(cmp)> edges(cmp);
    // for (auto edge : graph.edges)
    //     edges.emplace(edge);
    // printf("\n");
    // while (!edges.empty()) {
    //     printf("%d_", edges.top()->weight);
    //     edges.pop();
    // }
    // printf("\n isSame: %s", ms.isSameSet(graph.getNode(1), graph.getNode(3))? "true":"false");
    return 0;
}