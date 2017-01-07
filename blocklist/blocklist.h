/* blocklist.h */

#ifndef __BLOCK_LIST_H__
#define __BLOCK_LIST_H__

#include <iostream>

using namespace std;

const int MAXN = 300;

template<typename T>
class Block {
 public:
  static int maxn;
  T data[MAXN];
  int len;
  bool rev;  // Unused
  Block<T> *next, *prev;
  Block(Block<T>* to, Block<T>* p) : next(to), prev(p) {
    len = 0;
    rev = false;
  }
  /* Split a block at pos
   * [0, len) -> [0, pos), [pos, len)
   * 1 <= pos < len
   */
  void split(int pos) {
    if (pos >= len || pos <= 0) return;
    if (this->rev) {
      reverse(this->data, this->data + this->len);
      this->rev = 0;
    }
    Block<T>* newBlock = new Block<T>(this->next, this);
    if (this->next != nullptr) this->next->prev = newBlock;
    this->next = newBlock;
    newBlock->len = len - pos;

    // strcpy((char*)newblock->data, (char*)&data[pos]);
    newBlock->setData(data + pos, len - pos);
    this->len = pos;
  }

  /* Merge two blocks
   * len1 + len2 <= MAXN
   */
  bool merge() {
    Block<T>* nextBlock = this->next;
    if (nullptr == nextBlock) return false;
    if (nextBlock->len + this->len > maxn) return false;
    if (this->rev) {
      reverse(this->data, this->data + this->len);
      this->rev = 0;
    }
    if (nextBlock->rev) {
      reverse(nextBlock->data, nextBlock->data + nextBlock->len);
      nextBlock->rev = 0;
    }
    this->next = nextBlock->next;
    if(nextBlock->next != nullptr) nextBlock->next->prev = this;
    // strcpy((char*)&this->data[len], (char*)nextBlock->data)
    int i;
    for (i = 0; i < nextBlock->len; ++i) {
      data[this->len++] = nextBlock->data[i];
    }
    delete nextBlock;
    nextBlock = nullptr;
    return true;
  }

  T select(int k) {
    if (k < len && k >= 0) {
      return data[k];
    }
    return 0;  // Not sure
  }

  // remove the next block
  void remove() {
    Block<T>* nextBlock = this->next;
    if (nullptr == nextBlock) return;
    this->next = nextBlock->next;
    if (nextBlock->next != nullptr) nextBlock->next->prev = this;
    delete nextBlock;
    nextBlock = nullptr;
  }

  void setData(T array[], int len) {
    this->len = len;
    int i;
    for (i = 0; i < len; ++i) {
      this->data[i] = array[i];
    }
  }
};

template<typename T>
int Block<T>::maxn = MAXN;

template<typename T>
class BlockList {
 public:
  Block<T>* head;
  Block<T>* cur;
  int offset;

  BlockList() {
    head = new Block<T>(nullptr, nullptr);  // Dummy node
    cur = head;
    offset = -1;  // Equivalent to index
  }

  void moveKth(int pos);
  void Next();
  void Prev();
  void get(int n);
  void insert(T array[], int n);
  void erase(int n);
};

// Move offset forward for pos steps
template<typename T>
void BlockList<T>::moveKth(int pos) {
  Block<T> *father = head, *temp = head->next;
  int accumulation = 0;
  while (temp != nullptr) {
    if (accumulation + temp->len >= pos) break;
    father = temp;
    accumulation += temp->len;
    temp = temp->next;
  }
  if (nullptr == temp) {
    cur = father;
    this->offset = cur->len - 1;
  } else {
    cur = temp;
    this->offset = pos - accumulation - 1;
  }
  if (cur != nullptr) {
    while (cur->merge()) ;
  }
}

template<typename T>
void BlockList<T>::Prev() {
  if (this->offset == -1) {
    if (head->next != nullptr) {
      cur = head->next;
    }
  } else if (this->offset == 0) {
    if (cur != head->next) {
      cur = cur->prev;
      this->offset = cur->len - 1;
    } else {
      this->offset--;  //  offset = -1
    }
  } else {
    this->offset--;
  }
  if (cur != nullptr) {
    while (cur->merge()) ;
  }
}

template<typename T>
void BlockList<T>::Next() {
  if (this->offset == -1) {
    if (head->next != nullptr) {
      cur = head->next;
      this->offset = 0;
    }
  } else if (this->offset == cur->len - 1) {
    if (cur->next != nullptr) {
      cur = cur->next;
      this->offset = 0;
    }
  } else {
    this->offset++;
  }
  if (cur != nullptr) {
    while (cur->merge()) ;
  }
}

template<typename T>
void BlockList<T>::get(int n) {
  if (this->offset == -1) {
    if (nullptr == head->next) return;
    cur = head->next;
  }
  Block<T>* temp = cur;
  int i, pos;
  for (i = 0, pos = this->offset + 1; i < n; ++i, ++pos) {
    if (pos == temp->len) {
      temp = temp->next;
      if (nullptr == temp) break;
      pos = 0;
    }
    if (temp != nullptr) {
      cout << temp->select(pos);
    }
  }
  cout << endl;
}

template<typename T>
void BlockList<T>::insert(T array[], int n) {
  if (n <= 0) return;
  Block<T> *father, *next;
  if (this->offset == -1) {
    next = head->next;
    father = head;
  } else {  // split
    cur->split(this->offset + 1);
    next = cur->next;
    father = cur;
  }
  int len, accumulation = 0;
  do {
    Block<T>* newBlock = new Block<T>(nullptr, father);
    if (n > Block<T>::maxn) {
      len = Block<T>::maxn;
    } else {
      len = n;
    }
    newBlock->setData(array + accumulation, len);
    father->next = newBlock;
    father = newBlock;
    n -= len;
    accumulation += Block<T>::maxn;
  } while (n > 0);
  father->next = next;
  if (next != nullptr) next->prev = father;
  if (this->offset == -1) cur = head->next;
  if (cur != nullptr) {
    while (cur->merge()) ;
  }
}

template<typename T>
void BlockList<T>::erase(int n) {
  if (this->offset == -1) {
    if (nullptr == head->next) return;
    cur = head;
  } else {
    cur->split(this->offset + 1);
  }
  int accumulation = 0;
  Block<T>* temp = cur->next;
  while (temp != nullptr) {
    if (temp->len + accumulation <= n) {
      accumulation += temp->len;
      temp = temp->next;
      cur->remove();
    } else {
      if (n > accumulation) {
        temp->split(n - accumulation);
        cur->remove();
      }
      break;
    }
  }
  if (this->offset == -1) cur = head->next;
  if (cur != nullptr) {
    while (cur->merge()) ;
  }
}

#endif // __BLOCK_LSIT_H__
