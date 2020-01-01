#ifndef HUFFMAN_CODE_H_
#define HUFFMAN_CODE_H_

#include "minheap.h"

using std::cout;

template<typename T, typename W>
struct CodeObject {
  T data;
  W cost;
};

const int CODESIZE = 2;

template<typename T>
struct HCNode {
  T data;
  size_t length;
  unsigned char bits[CODESIZE];
};

template<typename T, typename W>
struct HTNode {
  T data;
  W cost;
  HTNode<T, W>* left;
  HTNode<T, W>* right;

  HTNode(const T& x, const W w, HTNode<T, W>* lp=nullptr,
         HTNode<T, W>* rp=nullptr) : data(x), cost(w) {
    left = lp;
    right = rp;
  }

  operator W() const {
    return cost;
  }
};

template<typename T, typename W>
class HTNSmartPtr {
 private:
  HTNode<T, W>* ptr;

 public:
  HTNSmartPtr(HTNode<T, W>* p=nullptr) {
    ptr = p;
  }
  HTNode<T, W>& operator*() {
    return *ptr;
  }
  HTNode<T, W>* operator->() {
    return ptr;
  }

  // This is necessary for conversion HTNSmartPtr<T, W> to HTNode<T, W>*.
  operator HTNode<T, W>*() {
    return ptr;
  }

  bool operator<(HTNSmartPtr<T, W> p) {
    return ptr->cost < p->cost;
  }
  bool operator>(HTNSmartPtr<T, W> p) {
    return ptr->cost > p->cost;
  }
};

template<typename T, typename W>
class HuffmanTree {
 public:
  HuffmanTree();
  ~HuffmanTree();

  void encode(CodeObject<T, W>* codeArray, size_t length);
  bool decode(unsigned char bits[CODESIZE], size_t length, T& decodedword);
  void printCode(unsigned char bits[CODESIZE], size_t length);
  void printCodeTable();
 private:
  HTNSmartPtr<T, W> m_root;
  size_t m_tableSize;
  HCNode<T>* m_codeTable;

  void createHuffmanTree(CodeObject<T, W>* codeArray);
  void createCodeTable();
  void createCodeTableRecursive(HTNSmartPtr<T, W> ht, unsigned char* table,
                                size_t pos, size_t& index);
  void setBit(unsigned char* bits, size_t pos, bool state);
  size_t getBit(unsigned char* codeword, size_t pos);

  void destroy(HTNode<T, W>* & r);
};

template<typename T, typename W>
HuffmanTree<T, W>::HuffmanTree() : m_root(nullptr) {
  m_tableSize = 0;
  m_codeTable = nullptr;
}

template<typename T, typename W>
HuffmanTree<T, W>::~HuffmanTree() {
  HTNode<T, W>* r = m_root;
  destroy(r);
  m_root = nullptr;
  delete [] m_codeTable;
  m_codeTable = nullptr;
}

// Huffman coding
template<typename T, typename W>
void HuffmanTree<T, W>::encode(CodeObject<T, W>* codeArray, size_t length) {
  m_tableSize = length;
  if (m_codeTable != nullptr) {
    delete [] m_codeTable;
  }
  m_codeTable = new HCNode<T>[m_tableSize];
  createHuffmanTree(codeArray);
  createCodeTable();
}

/* Return true if decoding successfully
 * This method can only deocode one coded word to one T element.
 */
template<typename T, typename W>
bool HuffmanTree<T, W>::decode(unsigned char codeword[CODESIZE],
                               size_t length, T& decodeword) {
  unsigned int pos = 0;
  HTNSmartPtr<T, W> p = m_root;
  for (pos = 0; pos < length; ++pos) {
    if (p != nullptr) {
      if (getBit(codeword, pos) == 0) {
        p = p->left;
      } else {
        p = p->right;
      }
    } else {
      break;
    }
  }
  if (pos == length && p != nullptr &&
      p->left == nullptr && p->right == nullptr) {
    decodeword = p->data;
    return true;
  } else {
    return false;
  }
}

// Print the coded word
template<typename T, typename W>
inline void HuffmanTree<T, W>::printCode(unsigned char codeword[CODESIZE],
                                         size_t length) {
  for (unsigned int j = 0; j < length; ++j) {
    cout << getBit(codeword, j);
  }
}

// Print the coded table
template<typename T, typename W>
void HuffmanTree<T, W>::printCodeTable() {
  cout << "Object\tCode\tSize" << endl;
  for (size_t i = 0; i < m_tableSize; ++i) {
    cout << m_codeTable[i].data << "\t";
    printCode(m_codeTable[i].bits, m_codeTable[i].length);
    cout << "\t" << m_codeTable[i].length << endl;
  }
  cout << endl;
}

// Create the Huffman tree
template<typename T, typename W>
void HuffmanTree<T, W>::createHuffmanTree(CodeObject<T, W>* codeArray) {
  MinHeap<HTNSmartPtr<T, W> > heap(m_tableSize);
  HTNSmartPtr<T, W> tree = nullptr,
                    subtreeL = nullptr,
                    subtreeR = nullptr;
  for (size_t i = 0; i < m_tableSize; ++i) {
    tree = new HTNode<T, W>(codeArray[i].data, codeArray[i].cost,
                            nullptr, nullptr);
    heap.insert(tree);
  }
  while (heap.size() > 1) {
    heap.deleteMin(subtreeL);
    heap.deleteMin(subtreeR);
    tree = new HTNode<T, W>(T(), subtreeL->cost + subtreeR->cost,
                            subtreeL, subtreeR);
    heap.insert(tree);
  }
  heap.deleteMin(m_root);
}

// Create the coded character table
template<typename T, typename W>
void HuffmanTree<T, W>::createCodeTable() {
  for (size_t i = 0; i < m_tableSize; ++i) {
    m_codeTable[i].data = T();
    m_codeTable[i].length = 0;
  }
  unsigned char table[CODESIZE];
  size_t index = 0;
  createCodeTableRecursive(m_root, table, 0, index);
}

// Create the code character table
template<typename T, typename W>
void HuffmanTree<T, W>::createCodeTableRecursive(HTNSmartPtr<T, W> ht,
                          unsigned char* table, size_t pos, size_t& index) {
  if (ht->left) {
    setBit(table, pos, 0);
    createCodeTableRecursive(ht->left, table, pos + 1, index);
  }
  if (ht->right) {
    setBit(table, pos, 1);
    createCodeTableRecursive(ht->right, table, pos + 1, index);
  }
  if (nullptr == ht->left && nullptr == ht->right) {
    m_codeTable[index].data = ht->data;
    for (int i = 0; i < CODESIZE; ++i) {
      m_codeTable[index].bits[i] = table[i];
    }
    m_codeTable[index].length = pos;
    index++;
  }
}

/* Set the bit at position pos in the array bits to value state
 * Array bits has two char elements.
 * Each char element contains 8 bits.
 */
template<typename T, typename W>
void HuffmanTree<T, W>::setBit(unsigned char* bits, size_t pos, bool state) {
  unsigned char mask = 0x80;
  for (unsigned int i = 0; i < (pos % 8); ++i) {
    mask = mask >> 1;
  }
  if (1 == state) {
    bits[pos / 8] = bits[pos / 8] | mask;
  } else if (0 == state) {
    bits[pos / 8] = bits[pos / 8] & (~mask);
  } else {
    cerr << endl << "The bit to be set should be '1' or '0'!" << endl;
  }
  return;
}

// Get the state of the bit at position pos int the array bits
template<typename T, typename W>
size_t HuffmanTree<T, W>::getBit(unsigned char* bits, size_t pos) {
  unsigned char mask = 0x80;
  for (unsigned int i = 0; i < (pos % 8); ++i) {
    mask = mask >> 1;
  }
  return ((mask & bits[pos / 8]) == mask) ? 1 : 0;
}

template<typename T, typename W>
void HuffmanTree<T, W>::destroy(HTNode<T, W>* & r) {
  if (r != nullptr) {
    destroy(r->left);
    destroy(r->right);
    delete r;
    r = nullptr;
  }
}

#endif  // HUFFMAN_CODE_H_
