// binary tree

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* lchild;
  TreeNode* rchild;

  TreeNode(int _val) : val(_val), lchild(nullptr), rchild(nullptr) {  }

  ~TreeNode() {
    if (lchild != nullptr) {
      delete lchild;
    }
    if (rchild != nullptr) {
      delete rchild;
    }
  }

  void preorder() {
    cout << val << ", ";
    if (lchild != nullptr) {
      lchild->preorder();
    }
    if (rchild != nullptr) {
      rchild->preorder();
    }
  }

  void inorder() {
    if (lchild != nullptr) {
      lchild->inorder();
    }
    cout << val << ", ";
    if (rchild != nullptr) {
      rchild->inorder();
    }
  }

  void postorder() {
    if (lchild != nullptr) {
      lchild->postorder();
    }
    if (rchild != nullptr) {
      rchild->postorder();
    }
    cout << val << ", ";
  }
};

class BinaryTree {
 private:
  TreeNode* root;

/*
  static char ss[10];

  void serializeTraversal(TreeNode* root, string& res) {
    if (root == nullptr) {
      res += "#,";
    } else {
      sprintf(ss, "%d", root->val);
      res += string(ss);
      res.push_back(',');
      serializeTraversal(root->lchild, res);
      serializeTraversal(root->rchild, res);
    }
  }

  void deserializeTraversal(vector<string>& data, TreeNode* root, int& iter) {
    ++iter;
    if (data[iter - 1] == "#") {
      root = nullptr;
    } else {
      int val;
      sscanf(data[iter -1 ].c_str(), "%d", &val);
      root = new TreeNode(val);
      deserializeTraversal(data, root->lchild, iter);
      deserializeTraversal(data, root->rchild, iter);
    }
  } 
*/

 public:
  BinaryTree() {
    root = nullptr;
  }

  ~BinaryTree() {
    if (root != nullptr) {
      delete root;
    }
  }

  void build_demo() {
    root = new TreeNode(1);
    root->lchild = new TreeNode(2);
    root->rchild = new TreeNode(3);
    root->lchild->lchild = new TreeNode(4);
    root->lchild->rchild = new TreeNode(5);
    root->rchild->rchild = new TreeNode(6);
  }

  void preorder() {
    root->preorder();
  }

  void inorder() {
    root->inorder();
  }

  void postorder() {
    root->postorder();
  }

/*
  string serialize(TreeNode* root) {
    string res = "{";
    // preorder traverse
    serializeTraversal(root, res);
    res[res.length() - 1] = '}';
    return res;
  }

  TreeNode* deserialize(string s) {
    vector<string> data;
    int i, j, len;
    len = (int)s.length();
    i = 1;
    while (true) {
      j = i + 1;
      while (s[j] != ',' && s[j] != '}') {
        ++j;
      }
      data.push_back(s.substr(i, j - i));
      i = j + 1;
      if (i >= len) {
        break;
      }
    }

    int iter = 0;
    TreeNode* root = nullptr;
    // preorder traverse
    deserializeTraversal(data, root, iter);
    return root;
  }
*/
};


int main(int argc, char* argv[]) {
  BinaryTree binarytree;
  binarytree.build_demo();
  binarytree.preorder();
  cout << endl;
  binarytree.inorder();
  cout << endl;
  binarytree.postorder();
  cout << endl;
  return 0;
}
