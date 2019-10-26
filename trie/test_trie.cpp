#include <sys/time.h>
#include <iostream>
#include <fstream>
#include "trie.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main() {
  Trie trie;
  timeval tv_start, tv_end;
  long start = 0;
  ifstream stream_in("./trie/dict_linux.txt", ifstream::in);
  if (stream_in.is_open()) {
    int count = 0;
    int lineLength = 1024;
    char *buffer = new char[lineLength];
    long insert_sp = 0;
    while (stream_in.getline(buffer, lineLength)) {
      count++;
      gettimeofday(&tv_start, nullptr);
      start = (long)tv_start.tv_sec*1000 + (long)tv_start.tv_usec/1000;
      trie.insert(buffer);
      gettimeofday(&tv_end, nullptr);
      insert_sp += (((long)tv_end.tv_sec*1000 + (long)tv_end.tv_usec/1000)
                  - start);
    }
    cout << "Create trie spend: " << insert_sp << "ms." << endl;
  }

  long time_sp = 0;
  gettimeofday(&tv_start, nullptr);
  start = (long)tv_start.tv_sec*1000 + (long)tv_start.tv_usec/1000;
  trie.buildFailurePointer();
  gettimeofday(&tv_end, nullptr);
  time_sp = (((long)tv_end.tv_sec*1000 + (long)tv_end.tv_usec/1000) - start);
  cout << "Build failure pointer spend: " << time_sp << "ms." << endl;

  const char* keyword = "zygomaticoauricularis";
  gettimeofday(&tv_start, nullptr);
  string status;
  start = (long)tv_start.tv_sec * 1000 + (long)tv_start.tv_usec / 1000;
  for (int i = 0; i < 10000; ++i) {
    status = trie.find(keyword) == true ? "true" : "false";
  }
  gettimeofday(&tv_end, nullptr);
  time_sp = ((long)tv_end.tv_sec * 1000 + (long)tv_end.tv_usec / 1000) - start;
  cout << "Find result: " << status << endl;
  cout << "Find spend x10000: " << time_sp << "ms." << endl;

  start = (long)tv_start.tv_sec * 1000 + (long)tv_start.tv_usec / 1000;
  trie.match(keyword);
  time_sp = ((long)tv_end.tv_sec * 1000 + (long)tv_end.tv_usec / 1000) - start;
  cout << "Match spend: " << time_sp << "ms." << endl;

  return 0;
}
