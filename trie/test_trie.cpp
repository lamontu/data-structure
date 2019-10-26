#include <sys/time.h>
#include <iostream>
#include <fstream>
#include "trie.h"

using namespace std;

int main(int argc, char* argv[]) {
  cout << "========================================" << endl;

  Trie trie;
  long time_sp = 0;
  ifstream stream_in("./trie/dict_linux.txt", std::ifstream::in);
  if (stream_in.is_open()) {
    int count = 0;
    int lineLength = 1024;
    char *buffer = new char[lineLength];
    while (stream_in.getline(buffer, lineLength)) {
      count++;
      timeval tv_start, tv_end;
      gettimeofday(&tv_start, nullptr);
      long start = (long)tv_start.tv_sec*1000 + (long)tv_start.tv_usec/1000;
      trie.insert(buffer);
      gettimeofday(&tv_end, nullptr);
      time_sp += (((long)tv_end.tv_sec*1000 + (long)tv_end.tv_usec/1000)
                  - start);
    }
  }
  cout << time_sp << " ms. \n";

  const char* keyword = "zygomaticoauricularis";
  timeval find_tv_start, find_tv_end;
  gettimeofday(&find_tv_start, nullptr);
  string status;
  long find_start = (long)find_tv_start.tv_sec * 1000 +
                    (long)find_tv_start.tv_usec / 1000;
  for (int i = 0; i < 10000; ++i) {
    status = trie.find(keyword) == true ? "true" : "false";
  }
  gettimeofday(&find_tv_end, nullptr);
  long find_end = ((long)find_tv_end.tv_sec * 1000 +
                   (long)find_tv_end.tv_usec / 1000) - find_start;
  cout << "Search result: " << status << endl;
  cout << find_end << " ms. \n";
  cout << "========================================" << endl;
  return 0;
}
