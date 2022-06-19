#include <cmath>

#include "Tree.hpp"


using namespace std;

class BalanceReturn {
 public:
  bool isBalanced;
  int height;
  BalanceReturn(bool isB, int hei) : isBalanced(isB), height(hei) {}
};
template <class T>
class SearchReturn {
 public:
  bool empty;
  bool isBST;
  T min;
  T max;
  SearchReturn(bool isBST, T min, T max, bool empty = false)
      : isBST(isBST), min(min), max(max), empty(empty) {}
};
class FullReturn {
 public:
  int height;
  int nodes;
  FullReturn(int h, int n) : height(h), nodes(n) {}
};

template <class T>
bool isCompleted(BiTNode<T> *root);
template <class T>
bool isBalanced(BiTNode<T> *root);
template <class T>
BalanceReturn balanceProcess(BiTNode<T> *root);
template <class T>
bool isBST(BiTNode<T> *root);  // 是否是搜索二叉树(二叉查找树)
template <class T>
SearchReturn<T> searchProcess(BiTNode<T> *root);
template <class T>
bool isFull(BiTNode<T> *root);
template <class T>
FullReturn fullProcess(BiTNode<T> *root);

template <class T>
bool isCompleted(BiTNode<T> *root) {
  // 层序遍历下：
  // 1. 任意节点，有右无左，false
  // 2. 在1的条件下，遇到第一个左右孩子不双全的节点，之后的节点需均为叶节点
  if (root == nullptr) return true;
  queue<BiTNode<T> *> q;
  BiTNode<T> *node;
  q.push(root);
  bool isLeaf = false;
  while (!q.empty()) {
    node = q.front();
    q.pop();
    // 1.
    if (node->right != nullptr && node->left == nullptr) return false;
    // 2.
    if (isLeaf && (node->left != nullptr || node->right != nullptr))
      return false;
    if (node->left != nullptr) q.push(node->left);
    if (node->right != nullptr) q.push(node->right);
    if (node->left == nullptr || node->right == nullptr) isLeaf = true;
  }
  return true;
}
template <class T>
bool isBalanced(BiTNode<T> *root) {
  return balanceProcess(root).isBalanced;
}
template <class T>
BalanceReturn balanceProcess(BiTNode<T> *root) {
  if (root == nullptr) return BalanceReturn(true, 0);
  BalanceReturn leftData = balanceProcess(root->left);
  BalanceReturn rightData = balanceProcess(root->right);
  int height = max(leftData.height, rightData.height) + 1;
  bool isBalanced = (leftData.isBalanced && rightData.isBalanced) &&
                    (abs(leftData.height - rightData.height) <= 1);
  return BalanceReturn(isBalanced, height);
}

template <class T>
bool isBST(BiTNode<T> *root) {
  // 1. 左子树是搜索二叉树
  // 2. 右子树是搜索二叉树
  // 3. 左子树最大值小于当前节点值，右子树最小值大于当前节点值
  return searchProcess(root).isBST;
}
template <class T>
SearchReturn<T> searchProcess(BiTNode<T> *root) {
  if (root == nullptr)
    return SearchReturn<T>(true, 0, 0,
                           true);  // 由于没有空对象概念，使用empty代替
  SearchReturn<T> leftData = searchProcess(root->left);
  SearchReturn<T> rightData = searchProcess(root->right);
  bool isBST = true;
  T mi = root->value;
  T ma = root->value;
  if (!leftData.empty) {
    mi = min(mi, leftData.min);
    ma = max(ma, leftData.max);
    if (!leftData.isBST || leftData.max >= root->value) isBST = false;
  }
  if (!rightData.empty) {
    mi = min(mi, rightData.min);
    ma = max(ma, rightData.max);
    if (!rightData.isBST || rightData.min <= root->value) isBST = false;
  }
  return SearchReturn<T>(isBST, mi, ma);
}
template <class T>
bool isFull(BiTNode<T> *root) {
  if (root == nullptr) return true;
  FullReturn data = fullProcess(root);
  return data.nodes == (pow(2, data.height) - 1);   // n = 2^h - 1
}

template <class T>
FullReturn fullProcess(BiTNode<T> *root) {
  if (root == nullptr) return FullReturn(0, 0);
  FullReturn leftData = fullProcess(root->left);
  FullReturn rightData = fullProcess(root->right);
  int height = max(leftData.height, leftData.height) + 1;
  int nodes = leftData.nodes + rightData.nodes + 1;
  return FullReturn(height, nodes);
}
int main() {
  //   vector<char> data = {'a', 'b', 'c', 'd', '#', 'e', '#',
  //    'f', 'g', '#', '#', 'h', 'i'};
  vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  // vector<char> data = {'7', '4', '9', '2', '6', '8', '#', '1', '3', '5'};
  BiTree<char> bt;
  bt.root = bt.creatTree(data, 0);
  bt.printTree(bt.root);
  vector<BiTNode<char> *> td;
  // td = bt.preOrderTraverse(bt.root);
  // td = bt.endOrderTraverse(bt.root);
  // td = bt.levelOrderTraverse3(bt.root);
  td = bt.midOrderTraverse(bt.root);
  BalanceReturn rt = balanceProcess(bt.root);
  printf(
      "returnType: isBalanced: %s; isBST: %s; isCompleted: %s; isFull: %s\n "
      "height:%d\n",
      isBalanced(bt.root) ? "true" : "false", isBST(bt.root) ? "true" : "false",
      isCompleted(bt.root) ? "true" : "false",isFull(bt.root) ? "true" : "false", rt.height);
  for (auto i : td) {
    printf("%c", i->value);
  }
  return 0;
}