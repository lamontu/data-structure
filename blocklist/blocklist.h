#ifndef BLOCK_LIST_H_
#define BLOCK_LIST_H_

#include <iostream>

using std::reverse;
using std::cout;
using std::endl;

const size_t MAXN = 300;

template<typename T>
class Block {
 public:
  static size_t m_capacity;
  Block<T> *next, *prev;
  size_t m_length;
  T m_data[MAXN];
  bool rev;  // Unused
  Block(Block<T>* to, Block<T>* from) : next(to), prev(from), m_length(0), rev(false) { }

  /* Split a block at pos
   * [0, m_length) -> [0, pos), [pos, m_length)
   * 1 <= pos < m_length
   */
  void split(int pos) {
    if (pos >= m_length || pos <= 0) return;
    if (this->rev) {
      reverse(this->m_data, this->m_data + this->m_length);
      this->rev = 0;
    }
    Block<T>* newBlock = new Block<T>(this->next, this);
    if (this->next != nullptr) this->next->prev = newBlock;
    this->next = newBlock;
    newBlock->m_length = m_length - pos;

    // strcpy((char*)newblock->data, (char*)&data[pos]);
    newBlock->setData(m_data + pos, m_length - pos);
    this->m_length = pos;
  }

  /* Merge two blocks
   * len1 + len2 <= MAXN
   */
  bool merge() {
    Block<T>* nextBlock = this->next;
    if (nullptr == nextBlock) return false;
    if (nextBlock->m_length + this->m_length > m_capacity) return false;
    if (this->rev) {
      reverse(this->m_data, this->m_data + this->m_length);
      this->rev = 0;
    }
    if (nextBlock->rev) {
      reverse(nextBlock->m_data, nextBlock->m_data + nextBlock->m_length);
      nextBlock->rev = 0;
    }
    this->next = nextBlock->next;
    if(nextBlock->next != nullptr) nextBlock->next->prev = this;
    // strcpy((char*)&this->data[len], (char*)nextBlock->data)
    for (size_t i = 0; i < nextBlock->m_length; ++i) {
      m_data[this->m_length++] = nextBlock->m_data[i];
    }
    delete nextBlock;
    nextBlock = nullptr;
    return true;
  }

  T select(size_t k) {
    if (k < m_length) {
      return m_data[k];
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

  void setData(T array[], size_t length) {
    this->m_length = length;
    int i;
    for (i = 0; i < length; ++i) {
      this->m_data[i] = array[i];
    }
  }
};

template<typename T>
size_t Block<T>::m_capacity = MAXN;

template<typename T>
class BlockList {
 public:
  Block<T>* head;
  Block<T>* current;
  int offset;

  BlockList() {
    head = new Block<T>(nullptr, nullptr);  // Dummy node
    current = head;
    offset = -1;  // Equivalent to index
  }

  ~BlockList() {
    Block<T>* ptr = head;
    while (head != nullptr) {
      head = head->next;
      delete ptr;
      ptr = head;
    }
    head = current = nullptr;
    offset = -1;
  }

  BlockList(const BlockList& other) = delete;
  BlockList& operator=(const BlockList& rhs) = delete;

  void moveKth(size_t pos);
  void Next();
  void Prev();
  void get(size_t n);
  void insert(T array[], size_t n);
  void erase(size_t n);
};

// Move offset forward for pos steps
template<typename T>
void BlockList<T>::moveKth(size_t pos) {
  Block<T> *father = head, *temp = head->next;
  int accumulation = 0;
  while (temp != nullptr) {
    if (accumulation + temp->m_length >= pos) break;
    father = temp;
    accumulation += temp->m_length;
    temp = temp->next;
  }
  if (nullptr == temp) {
    current = father;
    this->offset = current->m_length - 1;
  } else {
    current = temp;
    this->offset = pos - accumulation - 1;
  }
  if (current != nullptr) {
    while (current->merge()) ;
  }
}

template<typename T>
void BlockList<T>::Prev() {
  if (this->offset == -1) {
    if (head->next != nullptr) {
      current = head->next;
    }
  } else if (this->offset == 0) {
    if (current != head->next) {
      current = current->prev;
      this->offset = current->m_length - 1;
    } else {
      this->offset--;  //  offset = -1
    }
  } else {
    this->offset--;
  }
  if (current != nullptr) {
    while (current->merge()) ;
  }
}

template<typename T>
void BlockList<T>::Next() {
  if (this->offset == -1) {
    if (head->next != nullptr) {
      current = head->next;
      this->offset = 0;
    }
  } else if (this->offset == current->m_length - 1) {
    if (current->next != nullptr) {
      current = current->next;
      this->offset = 0;
    }
  } else {
    this->offset++;
  }
  if (current != nullptr) {
    while (current->merge()) ;
  }
}

template<typename T>
void BlockList<T>::get(size_t n) {
  if (this->offset == -1) {
    if (nullptr == head->next) return;
    current = head->next;
  }
  Block<T>* temp = current;
  size_t i, pos;
  for (i = 0, pos = this->offset + 1; i < n; ++i, ++pos) {
    if (pos == temp->m_length) {
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
void BlockList<T>::insert(T array[], size_t n) {
  if (n == 0) return;
  Block<T> *father, *next;
  if (this->offset == -1) {
    next = head->next;
    father = head;
  } else {  // split
    current->split(this->offset + 1);
    next = current->next;
    father = current;
  }
  size_t len, accumulation = 0;
  do {
    Block<T>* newBlock = new Block<T>(nullptr, father);
    if (n > Block<T>::m_capacity) {
      len = Block<T>::m_capacity;
    } else {
      len = n;
    }
    newBlock->setData(array + accumulation, len);
    father->next = newBlock;
    father = newBlock;
    n -= len;
    accumulation += Block<T>::m_capacity;
  } while (n > 0);
  father->next = next;
  if (next != nullptr) next->prev = father;
  if (this->offset == -1) current = head->next;
  if (current != nullptr) {
    while (current->merge()) ;
  }
}

template<typename T>
void BlockList<T>::erase(size_t n) {
  if (this->offset == -1) {
    if (nullptr == head->next) return;
    current = head;
  } else {
    current->split(this->offset + 1);
  }
  size_t accumulation = 0;
  Block<T>* temp = current->next;
  while (temp != nullptr) {
    if (temp->m_length + accumulation <= n) {
      accumulation += temp->m_length;
      temp = temp->next;
      current->remove();
    } else {
      if (n > accumulation) {
        temp->split(n - accumulation);
        current->remove();
      }
      break;
    }
  }
  if (this->offset == -1) current = head->next;
  if (current != nullptr) {
    while (current->merge()) ;
  }
}

#endif  // BLOCK_LIST_H_
