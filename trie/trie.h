#ifndef TRIE_TRIE_H_
#define TRIE_TRIE_H_
#include <queue>
#include <iostream>

using std::cout;
using std::endl;

static const int letter_count = 26;

struct TrieNode {
  TrieNode* branches[letter_count];
  TrieNode* failure;
  int count;  // not used
  int level;  // pattern length when Completed is true
  bool Completed;
  char letter;

  explicit TrieNode(char character = 0, int length = 0) : failure(nullptr),
            count(1), level(length), Completed(false), letter(character) {
    for (int i = 0; i < letter_count; ++i) {
      branches[i] = nullptr;
    }
  }
};

class Trie {
 private:
  TrieNode* m_root;

 public:
  explicit Trie(TrieNode* init = nullptr) : m_root(init) {  }
  ~Trie() {
    destroy(m_root);
    m_root = nullptr;
  }

  TrieNode* create(char letter = 0, int level = 0) {
    TrieNode* pnode = new TrieNode(letter, level);
    return pnode;
  }

  void insert(const char* str) {
    if (!m_root || !str) {
      m_root = create();
    }
    TrieNode* pnode = m_root;
    while (str != nullptr && *str != 0) {
      char index = *str - 'a';
      if (index < 0) break;
      if (!pnode->branches[index]) {
        pnode->branches[index] = create(index, pnode->level + 1);
      } else {
        pnode->branches[index]->count++;
      }
      pnode = pnode->branches[index];
      str++;
    }
    pnode->Completed = true;
  }

  void destroy(TrieNode* pnode) {
    if (!pnode) return;
    for (int i = 0; i < letter_count; ++i) {
      if (pnode->branches[i] != nullptr) {
        destroy(pnode->branches[i]);
      }
    }
    delete pnode;
  }

  bool find(const char* str) {
    if (!m_root || !str) return false;
    TrieNode* pnode = m_root;
    do {
      pnode = pnode->branches[*str - 'a'];
      if (!pnode) return false;
      str++;
    } while (*str != 0);
    return pnode->Completed;
  }

  // Aho-Corasick algorithm: Construct trie with failure pointer
  void buildFailurePointer() {
    std::queue<TrieNode*> nodeQueue;
    m_root->failure = nullptr;
    nodeQueue.push(m_root);
    while (!nodeQueue.empty()) {
      TrieNode* current_node = nodeQueue.front();
      nodeQueue.pop();
      for (int i = 0; i < letter_count; ++i) {
        TrieNode* current_child = current_node->branches[i];
        if (current_child == nullptr) {
          continue;
        }
        if (current_node == m_root) {
          current_child->failure = m_root;
        } else {
          TrieNode* fail_node = current_node->failure;
          while (fail_node != nullptr) {
            TrieNode* fail_child = fail_node->branches[i];
            if (fail_child != nullptr) {
              current_child->failure = fail_child;
              break;
            }
            fail_node = fail_node->failure;
          }
          if (fail_node == nullptr) {
            current_child->failure = m_root;
          }
        }
        nodeQueue.push(current_child);
      }
    }
  }

  // Aho-Corasick algorithm: match target using trie with failure pointer
  void match(const char* target) {
    int length = strlen(target);
    TrieNode* pnode = m_root;
    int count = 0;
    for (int i = 0; i < length; ++i) {
      char index =  target[i] - 'a';
      if (index < 0) return;
      while (pnode->branches[index] == nullptr && pnode != m_root) {
        pnode = pnode->failure;
      }
      pnode = pnode->branches[index];
      if (pnode == nullptr) {
        continue;
      }
      TrieNode* tmp = pnode;
      while (tmp != m_root) {
        if (tmp->Completed) {
          count++;
          int size = tmp->level;
          int pos = i - size + 1;
          cout << "Matched at postion: " <<  pos << ", size: " << size << endl;
        }
        tmp = tmp->failure;
      }
    }
    cout << "Target: " << target << " matched count: " << count << endl;
  }
};

#endif  // TRIE_TRIE_H_
