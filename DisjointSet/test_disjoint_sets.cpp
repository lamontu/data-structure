/* test_disjoint_sets.cpp */

#include "disjoint_sets.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  DisjointSets uf(5);
  cout << "## Number of sets: " << uf.Count() << endl;
  cout << "### Find 2, 3, 4:" << endl;
  cout << uf.Find(2) << ", "
       << uf.Find(3) << ", "
       << uf.Find(4) << ", "
       << endl;
  cout << "### Test connection:" << endl;
  uf.Connected(2, 4) ? cout << "2, 4 connected.\n"
                     : cout << "2, 4 not connected.\n";
  cout << "--------------------------------" << endl;

  cout << "## Merge 2, 3 ..." << endl;
  uf.Merge(3, 2);
  cout << "## Merge 3, 4 ..." << endl;
  uf.Merge(3, 4);
  cout << "## Number of sets: " << uf.Count() << endl;
  cout << "### Find 2, 3, 4:" << endl;
  cout << uf.Find(2) << ", "
       << uf.Find(3) << ", "
       << uf.Find(4) << ", "
       << endl;
  cout << "### Test connection:" << endl;
  uf.Connected(2, 4) ? cout << "2, 4 connected.\n"
                     : cout << "2, 4 not connected.\n";
  return 0;
}
