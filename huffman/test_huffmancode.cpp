/* test_huffmancode.cpp */

#include "huffmancode.h"
#include <iostream>

using namespace std;

const int CHARNUM = 128;

template<typename T, typename W>
void createCodeInfo(string& str, CodeObject<T, W>* & codeArr, int& length);

template<typename T, typename W>
void printCodeInfo(CodeObject<T, W>* & codeArr, int length);

int main(int argc, char* argv[]) {
  int length = 0;
  CodeObject<char, int>* codeArr = nullptr;
  string str = "AAAABBCD";
  createCodeInfo(str, codeArr, length);
  printCodeInfo(codeArr, length);

  HuffmanTree<char, int> ht;
  ht.code(codeArr, length);
  ht.printCodeTable();

  char decodeResult;
  unsigned char codeword[CODESIZE];
  cout << "Coding\t" << "Decodedword" << endl;
  codeword[0] = 0xC0;
  if (ht.decode(codeword, 3, decodeResult)) {
    ht.printCode(codeword, 3);
    cout << "\t" << decodeResult << endl;
  } else {
    cerr << "\t" << "Invalid codeword!" << endl;
  }
  if (ht.decode(codeword, 4, decodeResult)) {
    ht.printCode(codeword, 4);
    cout << "\t" << decodeResult << endl;
  } else {
    ht.printCode(codeword, 4);
    cerr << "\t" << "Invalid codeword!" << endl;
  }

  codeword[0] = 0x40;
  if (ht.decode(codeword, 3, decodeResult)) {
    ht.printCode(codeword, 3);
    cout << "\t" << decodeResult << endl;
  } else {
    ht.printCode(codeword, 3);
    cerr << "\t" << "Invalid codeword!" << endl;
  }

  return 0;
}

// Generate the array for counting character frequency
template<typename T, typename W>
void createCodeInfo(string& str, CodeObject<T, W>* & codeArr, int& length) {
  char charFreq[CHARNUM];
  int index[CHARNUM];
  for (int i = 0; i < CHARNUM; ++i) {
    charFreq[i] = 0;
    index[i] = -1;
  }
  length = 0;
  for (unsigned int i = 0; i < str.size(); ++i) {
    charFreq[int(str[i])] += 1;
  }
  for (int i = 0; i < CHARNUM; ++i) {
    if (charFreq[i]) {
      index[length++] = i;
    }
  }
  codeArr = new CodeObject<T, W>[length];
  for (int i = 0; i < length; ++i) {
    codeArr[i].data = index[i];
    codeArr[i].cost = charFreq[index[i]];
  }
}

// Print the characters and there frequency
template<typename T, typename W>
void printCodeInfo(CodeObject<T, W>* & codeArr, int length) {
  cout << "Object\tCode" << endl;
  for (int i = 0; i < length; ++i) {
    cout << codeArr[i].data << "\t" << codeArr[i].cost << endl;
  }
  cout << endl;
}
