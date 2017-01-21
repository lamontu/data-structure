/* disjoint_sets.h */

#ifndef __DISJOINT_SETS_H__
#define __DISJOINT_SETS_H__

#include <algorithm>

using namespace std;

class DisjointSets {
 private:
  int count_;  // The total number of sets
  int* identity_;  // The identity of an element
  int* size_;  // The number of an element's siblings

 public:
  DisjointSets(int count) {
    count_ = count;
    identity_ = new int[count];
    size_ = new int[count];
    for (int i = 0; i < count_; ++i) {
      identity_[i] = i;
      size_[i] = 1;
    }
  }

  ~DisjointSets() {
    delete [] identity_;
    identity_ = nullptr;
    delete [] size_;
    size_ = nullptr;
  }

  int Find(int elem) {
    if (elem != identity_[elem]) {
      identity_[elem] = Find(identity_[elem]);
    }
    return identity_[elem];
  }

  void Merge(int x, int y) {
    if (x > y) swap(x, y);

    int i = Find(x);
    int j = Find(y);
    if (i == j) return;
    if (size_[i] < size_[j]) {
      identity_[i] = j;
      size_[j] += size_[i];
    } else {
      identity_[j] = i;
      size_[i] += size_[j];
    }
    count_--;
  }

  bool Connected(int x, int y) {
    return Find(x) == Find(y);
  }

  int Count() const {
    return count_;
  }
};

#endif  // __DISJOINT_SETS_H__
