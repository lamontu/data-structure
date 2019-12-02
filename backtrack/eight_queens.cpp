
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
private:
    vector<vector<string> > result;
public:
    int helper_call_count = 0;
    
    vector<vector<string> > solveNQueens(int n) {
        vector<string>cur(n, string(n,'.'));
        helper1(cur, 0);

        // vector<int> states(n, -1);
        // helper2(states, 0);

        return result;
    }

    void helper1(vector<string> &cur, int row) {
        helper_call_count++;
        if (row == cur.size()) {
            result.push_back(cur);
            return;
        }
        for (int col = 0; col < cur.size(); ++col) {
            if (isValid(cur, row, col)) {
                cur[row][col] = 'Q';
                helper1(cur, row+1);
                cur[row][col] = '.';
            }
        }
    }

    void helper2(vector<int> &states, int row) {
        helper_call_count++;

        //放置第row行的皇后
        int n = states.size();
        if (row == n) {
            vector<string>temp_res(n, string(n,'.'));
            for (int i = 0; i < n; i++) {
                temp_res[i][states[i]] = 'Q';
            }
            result.push_back(temp_res);
            return;
        }
        for (int col = 0; col < n; ++col) {
            if (isValid2(states, row, col)) {
                states[row] = col;
                helper2(states, row+1);
                states[row] = -1;
            }
        }
    }
     
    // 判断在cur[row][col]位置放一个皇后，是否是合法的状态，
    // 已经保证了每行一个皇后，只需要判断列是否合法以及对角线是否合法，
    // 只需要判断对角线上半部分，因为后面的行还没有开始放置。
    bool isValid(vector<string> &cur, int row, int col) {
        // 列
        for(int i = 0; i < row; ++i)
            if(cur[i][col] == 'Q') return false;
        // 左上对角线
        for(int i = row-1, j=col-1; i >= 0 && j >= 0; --i,--j)
            if(cur[i][j] == 'Q') return false;
        // 右上对角线
        for(int i = row-1, j=col+1; i >= 0 && j < cur.size(); --i,++j)
            if(cur[i][j] == 'Q') return false;
        
        return true;
    }

    bool isValid2(vector<int> &states, int row, int col) {
        for(int i = 0; i < row; ++i)
            if(states[i] == col || abs(row - i) == abs(col - states[i]))
                return false;

        return true;
    }

};

int main() {
    Solution sln = Solution();
    vector<vector<string> >  res = sln.solveNQueens(8);
    cout << "helper call count: " << sln.helper_call_count << endl;
    cout << "result count: " << res.size() << endl;
    return 0;
}