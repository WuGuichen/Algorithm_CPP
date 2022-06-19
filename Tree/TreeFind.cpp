#include "Tree.hpp"

using namespace std;

// 直接的方法
template <class T>
BiTNode<T>* getLCA(BiTNode<T>* root, BiTNode<T>* n1, BiTNode<T>* n2);
template <class T>
void getFatherProcess(
    BiTNode<T>* root,
    unordered_map<BiTNode<T>*, BiTNode<T>*>& fatherMap);  // map不加引用无法修改

// 巧方法
// case1: n1是n2的祖先或n2是n1的祖先
// case2: n1和n2不互为祖先
template <class T>
BiTNode<T>* lowestAncestor(BiTNode<T>* root, BiTNode<T>* n1, BiTNode<T>* n2);

// 找后继节点
template <class T>
BiTNode<T>* getSuccessorNode(BiTNode<T>* node);

template <class T>
BiTNode<T>* getLCA(BiTNode<T>* root, BiTNode<T>* n1, BiTNode<T>* n2) {
  unordered_map<BiTNode<T>*, BiTNode<T>*> fatherMap;  // 用来让节点上窜
  fatherMap.emplace(root, root);
  getFatherProcess(root, fatherMap);  // 递归获取所有节点的父节点
  unordered_set<BiTNode<T>*> set1;    // 记录节点到根节点的节点链
  set1.emplace(n1);
  BiTNode<T>* curNode = n1;
  while (curNode != fatherMap.at(curNode)) {
    set1.emplace(curNode);
    curNode = fatherMap.at(curNode);
  }
  set1.emplace(root);
  // 接着让n2上窜直至遇到n1节点链中的节点即为公共祖先（略）
  return n1;  // 略
}

template <class T>
void getFatherProcess(BiTNode<T>* root,
                      unordered_map<BiTNode<T>*, BiTNode<T>*>& fatherMap) {
  if (root == nullptr) return;
  fatherMap.emplace(root->left, root);
  fatherMap.emplace(root->right, root);
  // printf("Size:%d\n", fatherMap.size());
  getFatherProcess(root->left, fatherMap);
  getFatherProcess(root->right, fatherMap);
}

// 代码很难理解，直接背下现成的
template <class T>
BiTNode<T>* lowestAncestor(BiTNode<T>* root, BiTNode<T>* n1, BiTNode<T>* n2) {
  if (root == nullptr || root == n1 || root == n2)
    return root;  // base case:当前节点等于空、n1、n2时返回当前节点
  BiTNode<T>* left = lowestAncestor(root->left, n1, n2);
  BiTNode<T>* right = lowestAncestor(root->right, n1, n2);
  if (left != nullptr && right != nullptr)
    return root;  // 左右两树都有返回值则返回当前节点
  return left != nullptr ? left : right;  // 返回有返回值的那边
}

template <class T>
BiTNode<T>* getSuccessorNode(BiTNode<T>* node) {
  if (node == nullptr) return node;
  // 有右孩子，找右子树最左的节点
  if (node->right != nullptr) {     
    node = node->right;
    while (node->left != nullptr) node = node->left;
    return node;
  }else{  // 无右子树，则一直往上查父节点(需要有查父节点的功能)
    BiTNode<T>* pNode = node->parent;
    while(pNode != nullptr && pNode->left != node){  // 在当前节点无父节点或当前节点为左孩子时结束循环
      node = pNode;
      pNode = pNode->parent;
    }
    return pNode;
  }
}

int main() {
  //   vector<char> data = {'a', 'b', 'c', 'd', '#', 'e', '#',
  //    'f', 'g', '#', '#', 'h', 'i'};
  vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  // vector<char> data = {'7', '4', '9', '2', '6', '8', '#', '1', '3', '5'};
  BiTree<char> bt;
  bt.root = bt.creatTree(data, 0, nullptr);
  bt.printTree(bt.root);
  vector<BiTNode<char>*> td;
  td = bt.midOrderTraverse(bt.root);

  BiTNode<char>* n1 = td[2];
  BiTNode<char>* n2 = td[5];
  // BiTNode<char>* lca = getLCA(bt.root, n1, n2);  // 该方法略过
  BiTNode<char>* lca = lowestAncestor(bt.root, n1, n2);
  printf("lca of %c and %c is %c", n1->value, n2->value, lca->value);

  // 检查父节点设置
  // for (auto i : td) {
  //   printf("%c parent: %c\n", i->value, i->parent != nullptr ? i->parent->value : '#');
  // }
  // 测试中序遍历后继节点查找
  // BiTNode<char>* ss = getSuccessorNode(bt.root);
  // BiTNode<char>* sss = getSuccessorNode(ss);
  // cout << sss->value << endl;
  return 0;
}