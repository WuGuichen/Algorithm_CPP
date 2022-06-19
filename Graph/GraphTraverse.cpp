#include "Graph.hpp"

using namespace std;

void bfs(Node* node);
void dfs(Node* node);

void bfs(Node* node){
    if(node == nullptr) return;
    queue<Node*> q;
    unordered_set<Node*> set;  // 去重
    q.emplace(node);
    set.emplace(node);
    while(!q.empty()){
        Node* cur = q.front();
        q.pop();
        printf("%d,",cur->value);
        for(Node* next : cur->nexts){
            if(set.find(next) == set.end()){
                set.emplace(next);
                q.emplace(next);
            }
        }
    }
    printf("\n");
}

void dfs(Node* node){
    if(node == nullptr) return;
    stack<Node*> stk;
    unordered_set<Node*> set;
    stk.emplace(node);
    set.emplace(node);
    printf("%d,", node->value);
    while(!stk.empty()){
        Node* cur = stk.top();
        stk.pop();
        for(Node* next : cur->nexts){
            if(set.find(next) == set.end()){
                stk.emplace(cur);
                stk.emplace(next);
                set.emplace(next);
                printf("%d,", next->value);
                break;
            }
        }
    }
    printf("\n");
}

int main(){
    vector<vector<int>> data(0, vector<int>(3));
    data = {{3, 7, 1},
            {3, 1, 2},
            {3, 6, 2},
            {6, 9, 1},
            {1, 9, 2},
            {9, 7, 1},
            {7, 3, 3}};
    Graph graph(data);
    Node* n = graph.getNode(3);
    bfs(n);
    dfs(n);
    return 0;
}