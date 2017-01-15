/* huffmancode.h */

#ifndef __HUFFMAN_CODE_H__
#define __HUFFMAN_CODE_H__

#include <iostream>
#include "minheap.h"

using namespace std;

template<typename T, typename W>
struct CodeObject {
  T data;
  W cost;
};

const int CODESIZE = 2;

template<typename T>
struct HCNode {
  T data;
  unsigned char bits[CODESIZE];
  unsigned int length;
};

template<typename T, typename W>
struct HTNode {
  T data;
  W cost;
  HTNode<T, W>* left;
  HTNode<T, W>* right;

  HTNode(const T& x, const W w, HTNode<T, W>* lp=nullptr,
         HTNode<T, W>* rp=nullptr) {
    data = x;
    cost = w;
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

  void code(CodeObject<T, W>* codeArray, int length);
  bool decode(unsigned char bits[CODESIZE], unsigned int length,
              T& decodedword);
  void printCode(unsigned char bits[CODESIZE], unsigned int length);
  void printCodeTable();
 private:
  HTNSmartPtr<T, W> root;
  int arraySize;
  HCNode<T>* codeTable;

  void createHuffmanTree(CodeObject<T, W>* codeArray);
  void createCodeTable();
  void createCodeTableRecursive(HTNSmartPtr<T, W> ht, unsigned char* code,
                                int pos, int& index);
  void setBit(unsigned char* bits, unsigned int pos, unsigned int state);
  unsigned int getBit(unsigned char* codeword, unsigned int pos);

  void destroy(HTNode<T, W>* & r);
};

template<typename T, typename W>
HuffmanTree<T, W>::HuffmanTree() : root(nullptr) {
  arraySize = 0;
  codeTable = nullptr;
}

template<typename T, typename W>
HuffmanTree<T, W>::~HuffmanTree() {
  HTNode<T, W>* r = root;
  destroy(r);
  root = nullptr;
  delete [] codeTable;
  codeTable = nullptr;
}

// Huffman coding
template<typename T, typename W>
void HuffmanTree<T, W>::code(CodeObject<T, W>* codeArray, int length) {
  arraySize = length;
  if (codeTable != nullptr) {
    delete [] codeTable;
  }
  codeTable = new HCNode<T>[arraySize];
  createHuffmanTree(codeArray);
  createCodeTable();
}

/* Return true if decoding successfully
 * This method can only deocode one coded word to one T element.
 */
template<typename T, typename W>
bool HuffmanTree<T, W>::decode(unsigned char codeword[CODESIZE],
                               unsigned int length, T& decodeword) {
  unsigned int pos = 0;
  HTNSmartPtr<T, W> p = root;
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
                                         unsigned int length) {
  for (unsigned int j = 0; j < length; ++j) {
    cout << getBit(codeword, j);
  }
}

// Print the coded table
template<typename T, typename W>
void HuffmanTree<T, W>::printCodeTable() {
  cout << "Object\tCode\tSize" << endl;
  for (int i = 0; i < arraySize; ++i) {
    cout << codeTable[i].data << "\t";
    printCode(codeTable[i].bits, codeTable[i].length);
    cout << "\t" << codeTable[i].length << endl;
  }
  cout << endl;
}

// Create the Huffman tree
template<typename T, typename W>
void HuffmanTree<T, W>::createHuffmanTree(CodeObject<T, W>* codeArray) {
  MinHeap<HTNSmartPtr<T, W>> heap(arraySize);
  HTNSmartPtr<T, W> tree = nullptr,
                    subtreeL = nullptr,
                    subtreeR = nullptr;
  for (int i = 0; i < arraySize; ++i) {
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
  heap.deleteMin(root);
}

// Create the coded character table
template<typename T, typename W>
void HuffmanTree<T, W>::createCodeTable() {
  for (int i = 0; i < arraySize; ++i) {
    codeTable[i].data = T();
    codeTable[i].length = 0;
  }
  unsigned char code[CODESIZE];
  int index = 0;
  createCodeTableRecursive(root, code, 0, index);
}

// Create the code character table
template<typename T, typename W>
void HuffmanTree<T, W>::createCodeTableRecursive(HTNSmartPtr<T, W> ht,
                          unsigned char* code, int pos, int& index) {
  if (ht->left) {
    setBit(code, pos, 0);
    createCodeTableRecursive(ht->left, code, pos + 1, index);
  }
  if (ht->right) {
    setBit(code, pos, 1);
    createCodeTableRecursive(ht->right, code, pos + 1, index);
  }
  if (nullptr == ht->left && nullptr == ht->right) {
    codeTable[index].data = ht->data;
    for (int i = 0; i < CODESIZE; ++i) {
      codeTable[index].bits[i] = code[i];
    }
    codeTable[index].length = pos;
    index++;
  }
}

/* Set the bit at position pos in the array bits to value state
 * Array bits has two char elements.
 * Each char element contains 8 bits.
 */
template<typename T, typename W>
void HuffmanTree<T, W>::setBit(unsigned char* bits, unsigned int pos,
                               unsigned int state) {
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
unsigned int HuffmanTree<T, W>::getBit(unsigned char* bits, unsigned int pos) {
  unsigned char mask = 0x80;
  for (unsigned int i = 0; i < (pos % 8); ++i) {
    mask = mask >> 1;
  }
  return ( ((mask & bits[(int)(pos / 8)]) == mask) ? 1 : 0 );
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

#endif  // __HUFFMAN_CODE_H__
