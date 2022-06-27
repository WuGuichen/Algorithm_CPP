#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TrieNode {
public:
    int pass; // 该Node被经过多少次
    int end;  // 是多少个字符串的结尾Node
    // 根据使用环境决定找到下一级Node的方法
    TrieNode *nexts[26] = {nullptr}; // 固定字符种类数建议使用此方法(此处值限制为26个小写字母)
    TrieNode() :
        pass(0), end(0){};
    // ~TrieNode(){
    // }
};

class Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word);
    int search(string word);
};

void Trie::insert(string word) {
    if (word.empty()) return;
    vector<char> chs;
    chs.assign(word.begin(), word.end());
    TrieNode *node = root;
    node->pass++;
    int index = 0;
    for (int i = 0; i < chs.size(); i++) {
        index = chs[i] - 'a';                // 对应字母的index
        if (node->nexts[index] == nullptr) { // 如果下一节点中没有就新建
            node->nexts[index] = new TrieNode();
        }
        node = node->nexts[index]; // node移动到下一级的Node上
        node->pass++;
    }
    // 最后一个字母判断完走到最后一个Node
    node->end++;
}

int Trie::search(string word){
    if(word.empty()) return 0;
    vector<char> chs;
    chs.assign(word.begin(), word.end());
    TrieNode* node = root;
    int index = 0;
    for(int i = 0; i< chs.size(); i++){
        index = chs[i] - 'a';
        if(node->nexts[index] == nullptr)
            return 0;
        node = node->nexts[index];
    }
    return node->end;
}

int main() {
    TrieNode *n = new TrieNode();
    Trie t;
    t.insert("hello");
    t.insert("hell");
    t.insert("hell");
    int res = t.search("hell");
    cout << res << endl;
    // string w = "hello";
    // int l = w.size();
    // cout << l << endl;
    // const char *c = new char(l);
    // c = w.c_str();
    // for(int i = 0; i < l; i++)
    //     cout << *(c+i) << ',';
    return 0;
}