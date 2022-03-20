#include <vector>

using std::vector;

class Node {
  public:
  vector<Node*> vertexes;
  int key;

  Node(int k) {
    key = k;
  }

  Node* DeepClone(Node* src) {
    Node* dst = new Node(src->key);
    vector<bool> visited(vertexes.size(), false);
    clone(src, dst, visited);
    return dst;
  }

private:
  void clone(Node* src, Node* dst, vector<bool>& visited) {
    Node* node = nullptr;
    if (!visited[src->key] && !src->vertexes.empty()) {
      for (auto && cur : src->vertexes) {
        if (node == nullptr || (node != nullptr && node->key != cur->key)) {
          node = new Node(cur->key);
        }
        dst->vertexes.push_back(node);
        clone(cur, dst, visited);
        visited[cur->key] = true;
      }
    }
  }
};