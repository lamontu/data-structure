#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

class SkipList {
 public:
  SkipList();
  ~SkipList();

  SkipList(const SkipList& other) = delete;
  SkipList& operator=(const SkipList& rhs) = delete;

  void Print() const;
  string* Find(int key) const;

  void Insert(int key, const string& new_value);
  void Erase(int key);

 private:
  const double Probability;
  const size_t MaxLevel;

  struct Node {
    vector<Node*> forward;
    string value;
    int key;
    char padding[4];
    Node(int k, const string& v, size_t level)
      : forward(level, nullptr), value(v), key(k), padding("") {  }
  };
  Node* head;
  Node* NIL;

  size_t random_level() const;
  static size_t node_level(const Node* v);
  static Node* make_node(int key, string val, size_t level);
  Node* lower_bound(int key) const;
  vector<Node*> predecessors(int key) const;
};

SkipList::SkipList() : Probability(0.5), MaxLevel(16) {
  int head_key = numeric_limits<int>::min();
  head = new Node(head_key, "head", MaxLevel);
  int nil_key = numeric_limits<int>::max();
  NIL = new Node(nil_key, "NIL", MaxLevel);

  fill(head->forward.begin(), head->forward.end(), NIL);
}

SkipList::~SkipList() {
  auto node = head;
  while (node->forward[0]) {
    auto tmp = node;
    node = node->forward[0];
    delete tmp;
  }
  delete NIL;
}

string* SkipList::Find(int key) const {
  string* res{};
  if (auto x = lower_bound(key)) {
    if (x->key == key && x != NIL) {
      res = &(x->value);
    }
  }
  return res;
}

void SkipList::Print() const {
  Node* list = head->forward[0];
  int line_length = 0;
  cout << "{";
  while (list != NIL) {
    cout << "value: " << list->value << ", key: " << list->key
         << ", level: " << node_level(list);
    list = list->forward[0];
    if (list != NIL) cout << " : ";
    if (++line_length % 2 == 0) cout << "\n";
  }
  cout << "}\n";
}

void SkipList::Insert(int key, const string& new_value) {
  auto preds = predecessors(key);

  auto next = preds[0]->forward[0];
  if (next->key == key && next != NIL) {
    next->value = new_value;
    return;
  }

  const size_t new_level = random_level();
  auto new_node_ptr = make_node(key, new_value, new_level);

  for (size_t i = 0; i < new_level; ++i) {
    new_node_ptr->forward[i] = preds[i]->forward[i];
    preds[i]->forward[i] = new_node_ptr;
  }
}

void SkipList::Erase(int key) {
  auto preds = predecessors(key);

  auto node = preds[0]->forward[0];
  if (node->key != key || node == NIL) {
    return;
  }

  for (size_t i = 0; i < node_level(node); ++i) {
    preds[i]->forward[i] = node->forward[i];
  }
  delete node;
}

size_t SkipList::node_level(const Node* v) {
  return v->forward.size();
}

SkipList::Node* SkipList::make_node(int key, string val, size_t level) {
  return new Node(key, val, level);
}

size_t SkipList::random_level() const {
  size_t v = 1;
  // This is important for the time complexity
  while (static_cast<double>(rand()) / RAND_MAX < Probability && v < MaxLevel) {
    v++;
  }
  return v;
}

SkipList::Node* SkipList::lower_bound(int key) const {
  Node* x = head;
  for (size_t i = node_level(head); i-- > 0;) {
    while (x->forward[i]->key < key) {
      x = x->forward[i];
    }
  }
  return x->forward[0];
}

// The size of returned vector is the MaxLevel
vector<SkipList::Node*> SkipList::predecessors(int key) const {
  vector<Node*> result(node_level(head), nullptr);
  Node* x = head;

  for (size_t i = node_level(head); i-- > 0;) {
    while (x->forward[i]->key < key) {
      x = x->forward[i];
    }
    result[i] = x;
  }

  return result;
}

int main() {
  SkipList s;

  for (int i = 0; i < 50; ++i) {
    stringstream ss;
    ss << i;
    s.Insert(i, ss.str());
  }

  s.Print();

  auto f = s.Find(10);
  if (f) {
    cout << "Node found!\nvalue: " << *f << endl;
  } else {
    cout << "Node NOT found!" << endl;
  }

  s.Insert(40, "Test");
  s.Print();

  s.Erase(40);
  s.Print();

  return 0;
}
