/* trie.h */

#ifndef __TRIE_H__
#define __TRIE_H__

struct TrieNode {
  static const int letter_count = 26;

  int count;
  bool Completed;
  char letter;
  TrieNode* branches[letter_count];

  TrieNode() : letter(0), count(1), Completed(false) {
    for (int i = 0; i < letter_count; ++i) {
      branches[i] = nullptr;
    }
  }
};

class Trie {
 private:
  TrieNode* m_root;

 public:
  Trie(TrieNode* init=nullptr) : m_root(init) {  }
  ~Trie() {
    destroy(m_root);
  }

  TrieNode* create() {
    TrieNode* pnode = new TrieNode();
    return pnode;
  }

  void insert(const char* str) {
    if (!m_root || !str) {
      m_root = create();
    }
    TrieNode* pnode = m_root;
    while (*str != 0) {
      char index = *str - 'a';
      if (!pnode->branches[index]) {
        pnode->branches[index] = create();
      } else {
        pnode->branches[index]->count++;
      }
      pnode = pnode->branches[index];
      pnode->letter = *str;
      str++;
    }
    pnode->Completed = true;
  }

  void destroy(TrieNode* pnode) {
    if (!pnode) return;
    for (int i = 0; i < TrieNode::letter_count; ++i) {
      if (pnode->branches[i] != nullptr) {
        destroy(pnode->branches[i]);
      }
    }
    delete pnode;
    pnode = nullptr;
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
};

#endif  // __TRIE_H__
