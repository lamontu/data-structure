#include "huffmancode.h"

using std::string;

const size_t CHARNUM = 128;

template<typename T, typename W>
void createCodeInfo(string& str, CodeObject<T, W>* & codeArr, size_t& length);

template<typename T, typename W>
void printCodeInfo(CodeObject<T, W>* & codeArr, size_t length);

int main() {
  size_t length = 0;
  CodeObject<char, int>* codeArr = nullptr;
  string str = "AAAABBCD";
  createCodeInfo(str, codeArr, length);
  printCodeInfo(codeArr, length);

  HuffmanTree<char, int> ht;
  ht.encode(codeArr, length);
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
void createCodeInfo(string& str, CodeObject<T, W>* & codeArr, size_t& length) {
  char charFreq[CHARNUM];
  int index[CHARNUM];
  for (size_t i = 0; i < CHARNUM; ++i) {
    charFreq[i] = 0;
    index[i] = -1;
  }
  length = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    charFreq[int(str[i])] += 1;
  }
  for (size_t i = 0; i < CHARNUM; ++i) {
    if (charFreq[i]) {
      index[length++] = i;
    }
  }
  codeArr = new CodeObject<T, W>[length];
  for (size_t i = 0; i < length; ++i) {
    codeArr[i].data = index[i];
    codeArr[i].cost = charFreq[index[i]];
  }
}

// Print the characters and there frequency
template<typename T, typename W>
void printCodeInfo(CodeObject<T, W>* & codeArr, size_t length) {
  cout << "Object\tCode" << endl;
  for (size_t i = 0; i < length; ++i) {
    cout << codeArr[i].data << "\t" << codeArr[i].cost << endl;
  }
  cout << endl;
}
