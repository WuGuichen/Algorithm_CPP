#ifndef TREE_HPP
#define TREE_HPP
#include <stdio.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
struct BiTNode {
    T value;
    BiTNode *left;
    BiTNode *right;
    BiTNode *parent;
    BiTNode(T value) :
        value(value), left(nullptr), right(nullptr), parent(nullptr){};
};

template <class T>
class BiTree {
private:
public:
    BiTNode<T> *root;
    vector<BiTNode<T> *> preOrderTraverse(BiTNode<T> *root);
    vector<BiTNode<T> *> midOrderTraverse(BiTNode<T> *root);
    vector<BiTNode<T> *> endOrderTraverse(BiTNode<T> *root);
    vector<BiTNode<T> *> levelOrderTraverse1(BiTNode<T> *root); // 普通层序遍历
    vector<BiTNode<T> *> levelOrderTraverse2(BiTNode<T> *root);
    vector<BiTNode<T> *> levelOrderTraverse3(BiTNode<T> *root);
    bool isBalanced(BiTNode<T> *root);
    // vector<BiTNode *> midOrderTraverse(BiTNode<T> *root);
    BiTree() :
        root(nullptr){};
    bool empty();
    void traverse(int key, void (*visit)(T));
    void printTree(BiTNode<T> *root);
    BiTNode<T> *creatTree(vector<T> data, int start, BiTNode<T> *pNode = nullptr); // 默认值只需要在声明时写出即可
};

template <class T>
inline bool BiTree<T>::empty() {
    return this->root == nullptr ? true : false;
}

template <class T>
void BiTree<T>::traverse(int key, void (*visit)(T)) {
    if (key == 1) {
        BiTree<T>::PreOrderTraverse(this->root, visit);
    } else if (key == 2) {
        MidOrderTraverse(this->root, visit);
    } else if (key == 3) {
        EndOrderTraverse(this->root, visit);
    } else if (key == 4) {
        LevelOrderTraverse(visit);
    } else if (key == 5) {
        PreOrderTraverseStack(visit);
    }
}
template <class T>
BiTNode<T> *BiTree<T>::creatTree(vector<T> data, int start, BiTNode<T> *pNode) {
    if (data.empty() || data[start] == '#') return NULL;
    BiTNode<T> *root = new BiTNode<T>(data[start]);
    int lNode = 2 * start + 1;
    int rNode = lNode + 1;
    // 检测是否越界
    if (lNode < data.size()) root->left = creatTree(data, lNode, root);
    if (rNode < data.size()) root->right = creatTree(data, rNode, root);
    root->parent = pNode;
    return root;
}

// template <class T>
// BiTNode<T> *BiTree<T>::creatTree(vector<T> data, int start, BiTNode<T>*
// pNode) {
//   if (data.empty() || data[start] == '#') return NULL;
//   BiTNode<T> *root = new BiTNode<T>(data[start]);
//   int lNode = 2 * start + 1;
//   int rNode = lNode + 1;
//   // 检测是否越界
//   if (lNode < data.size()) root->left = creatTree(data, lNode, root);
//   if (rNode < data.size()) root->right = creatTree(data, rNode, root);
//   root->parent = pNode;
//   return root;
// }
template <class T>
vector<BiTNode<T> *> BiTree<T>::preOrderTraverse(BiTNode<T> *root) {
    if (root == nullptr) return vector<BiTNode<T> *>();
    vector<BiTNode<T> *> res;
    stack<BiTNode<T> *> stk;
    stk.push(root);
    while (!stk.empty()) {
        BiTNode<T> *node = stk.top();
        stk.pop();
        res.push_back(node);
        if (node->right != nullptr) stk.push(node->right);
        if (node->left != nullptr) stk.push(node->left);
    }
    return res;
}
template <class T>
vector<BiTNode<T> *> BiTree<T>::midOrderTraverse(BiTNode<T> *root) {
    vector<BiTNode<T> *> res;
    stack<BiTNode<T> *> stk;
    BiTNode<T> *node = root;
    while (!stk.empty() || node != nullptr) {
        while (node != nullptr) {
            stk.push(node);
            node = node->left;
        }
        node = stk.top();
        stk.pop();
        res.push_back(node);
        node = node->right;
    }
    return res;
}

template <class T>
vector<BiTNode<T> *> BiTree<T>::endOrderTraverse(BiTNode<T> *root) {
    if (root == nullptr) return vector<BiTNode<T> *>();
    vector<BiTNode<T> *> res;
    stack<BiTNode<T> *> stk;
    stk.push(root);
    while (!stk.empty()) {
        BiTNode<T> *node = stk.top();
        stk.pop();
        res.push_back(node);
        if (node->left != nullptr) stk.push(node->left);
        if (node->right != nullptr) stk.push(node->right);
    }
    reverse(res.begin(), res.end());
    return res;
}
// 简单层序遍历
template <class T>
vector<BiTNode<T> *> BiTree<T>::levelOrderTraverse1(BiTNode<T> *root) {
    if (root == nullptr) return vector<BiTNode<T> *>();
    vector<BiTNode<T> *> res;
    queue<BiTNode<T> *> q;
    q.push(root);
    BiTNode<T> *node;
    while (!q.empty()) {
        node = q.front();
        q.pop();
        res.push_back(node);
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
    return res;
}
// 用map辅助进行每层节点统计
template <class T>
vector<BiTNode<T> *> BiTree<T>::levelOrderTraverse2(BiTNode<T> *root) {
    if (root == nullptr) return vector<BiTNode<T> *>();
    vector<BiTNode<T> *> res;
    queue<BiTNode<T> *> q;
    q.push(root);
    BiTNode<T> *node;
    // 对每层宽度的统计
    unordered_map<BiTNode<T> *, int> levelMap;
    levelMap.emplace(root, 1);
    int curLevel = 1;
    int curLevelNodes = 0;
    int width = INT_MIN;
    while (!q.empty()) {
        node = q.front();
        q.pop();
        res.push_back(node);
        int level = levelMap[node]; // 当前节点所在层
        if (level == curLevel) {
            curLevelNodes++;
        } else { // 遇到下一层的节点了
            width = max(curLevelNodes, width);
            // printf("level:%d, width:%d\n", curLevel,curLevelNodes);
            curLevelNodes = 1;
            curLevel++;
        }

        if (node->left != nullptr) {
            levelMap.emplace(node->left, level + 1);
            q.push(node->left);
        }
        if (node->right != nullptr) {
            levelMap.emplace(node->right, level + 1);
            q.push(node->right);
        }
    }
    width = max(curLevelNodes, width); // 最后一层宽度判断
    // printf("level:%d, width:%d\n", curLevel,curLevelNodes);
    // printf("width:%d\n", width);
    return res;
}
// 用queue辅助进行每层节点统计
template <class T>
vector<BiTNode<T> *> BiTree<T>::levelOrderTraverse3(BiTNode<T> *root) {
    if (root == nullptr) return vector<BiTNode<T> *>();
    vector<BiTNode<T> *> res;
    queue<BiTNode<T> *> q;
    q.push(root);
    BiTNode<T> *node;
    // 对每层宽度的统计
    BiTNode<T> *curEnd = root;
    BiTNode<T> *nextEnd = nullptr;
    int curLevel = 1;
    int curLevelNodes = 1;
    int width = 0;
    while (!q.empty()) {
        node = q.front();
        q.pop();
        res.push_back(node);
        if (node->left != nullptr) {
            nextEnd = node->left;
            q.push(node->left);
        }
        if (node->right != nullptr) {
            nextEnd = node->right;
            q.push(node->right);
        }
        if (node != curEnd) {
            curLevelNodes++;
        } else { // 到了本层最后一个节点
            width = max(curLevelNodes, width);
            curLevelNodes = 1;
            curLevel++;
            curEnd = nextEnd;
            // printf("endNode:%c, level%d\n", curEnd->value, curLevel);
        }
    }
    width = max(curLevelNodes, width); // 最后一层宽度判断
    printf("width:%d\n", width);
    return res;
}

template <class T>
void BiTree<T>::printTree(BiTNode<T> *root) {
    if (!root) return;
    auto tmp = root;
    vector<BiTNode<T> *> inArray =
        BiTree<T>::midOrderTraverse(tmp); // 中序遍历节点数组
    string tmpStr;                        // 每行打印string的长度
    int loc = 0;
    unordered_map<BiTNode<T> *, int>
        first_locs; // 存储节点对应在本行string中的首位置
    for (auto &i : inArray) {
        loc = tmpStr.size();
        tmpStr += to_string(i->value) + " ";
        first_locs[i] = loc;
    }
    for (auto &i : tmpStr) i = ' '; //把模板全部置为空格方便后续使用
    // 层序遍历
    queue<BiTNode<T> *> q;
    q.emplace(root);
    while (!q.empty()) {
        int curLevelSize = q.size();
        int curLoc = 0;
        string tmpStr1 = tmpStr; // 节点所在行
        string tmpStr2 = tmpStr; // 下一行
        for (int i = 1; i <= curLevelSize; i++) {
            auto node = q.front();
            q.pop();
            curLoc = first_locs[node];
            string numStr(1, node->value);
            // cout << numStr << endl;
            if (node->left) {
                q.emplace(node->left);
                int firstLoc = first_locs[node->left] + 1;
                tmpStr2[firstLoc++] = '/';
                while (firstLoc < curLoc) tmpStr1[firstLoc++] = '_';
            }
            // 中间,对应位置打印节点值
            for (int j = 0; j < numStr.length(); j++, curLoc++) {
                tmpStr1[curLoc] = numStr[j];
            }
            //右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
            if (node->right) {
                q.emplace(node->right);
                int lastLoc = first_locs[node->right] - 1;
                tmpStr2[lastLoc] = '\\';
                while (curLoc < lastLoc) tmpStr1[curLoc++] = '_';
            }
        }
        cout << tmpStr1 << endl;
        cout << tmpStr2 << endl;
    }
}
template <class T>
bool BiTree<T>::isBalanced(BiTNode<T> *root) {
    // 三个条件：
    // 1. 左子树是平衡二叉树。
    // 2. 右子树是平衡二叉树。
    // 3. 左右子树高度差不超过1。
}

#endif

// int main() {
//   // vector<char> data = {'a', 'b', 'c', 'd', '#', 'e', '#',
//   //  'f', 'g', '#', '#', 'h', 'i'};
//   vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '#',
//   'j'}; BiTree<char> bt; bt.root = bt.creatTree(data, 0);
//   vector<BiTNode<char> *> r = bt.midOrderTraverse(bt.root);
//   vector<BiTNode<char> *> td;
//   bt.printTree(bt.root);
//   // td = bt.preOrderTraverse(bt.root);
//   // td = bt.endOrderTraverse(bt.root);
//   td = bt.levelOrderTraverse3(bt.root);
//   printf("isCBT: %s\n", bt.isCBT(bt.root) ? "true" : "false");

//   for (auto i : td) {
//     printf("%c", i->value);
//   }
//   return 0;
// }