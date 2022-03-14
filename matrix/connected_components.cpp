#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

struct Point {
    int r;
    int c;
    Point(int r_, int c_) : r(r_), c(c_) {}
    Point(const Point& p) : r(p.r), c(p.c) {}
};

class Solution {
public:
    int m;
    int n;
    bool isValid(int i, int j, vector<vector<int>>& matrix, vector<vector<bool>>& mask) {
        return i >= 0 && i < m && j >= 0 && j < n && !mask[i][j] && matrix[i][j] == 1;
    }

    void add(int i, int j, vector<vector<int>>& matrix, queue<Point>& q, vector<vector<bool>>& mask) {
        if (isValid(i, j, matrix, mask)) {
            q.push(Point(i, j));
            mask[i][j] = true;
        }
    }

    vector<vector<Point>> bwlabel(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        vector<vector<Point>> res;
        vector<Point> tmp;
        vector<vector<bool>> mask(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mask[i][j] || matrix[i][j] == 0)
                    continue;
                tmp.clear();
                queue<Point> q;
                q.push(Point(i, j));
                mask[i][j] = true;
                while (!q.empty()) {
                    Point t = q.front();
                    q.pop();
                    tmp.push_back(t);
                    add(t.r - 1, t.c, matrix, q, mask);
                    add(t.r + 1, t.c, matrix, q, mask);
                    add(t.r, t.c - 1, matrix, q, mask);
                    add(t.r, t.c + 1, matrix, q, mask);
                }
                res.push_back(tmp);
            }
        }
        return res;
    }

    std::pair<Point, Point> boundingbox(vector<Point> points) {
        auto rExtremes = std::minmax_element(points.begin(), points.end(),
        [](const Point& lhs, const Point& rhs) {
            return lhs.r < rhs.r;
        });
        auto cExtremes = std::minmax_element(points.begin(), points.end(),
        [](const Point& lhs, const Point& rhs) {
            return lhs.c < rhs.c;
        });
        return make_pair(Point(rExtremes.first->r, cExtremes.first->c),
         Point(rExtremes.second->r, cExtremes.second->c));
    }
    
};

int main() {
    vector<vector<int>> m = {
        {1,1,0,0,0},
        {1,0,1,0,0},
        {0,1,1,0,0},
        {0,0,0,1,0},
        {0,0,0,0,1},
        {0,0,0,0,0}
    };
    
    Solution sln;
    auto res = sln.bwlabel(m);
    std::cout << "count = " << res.size() << std::endl;
    for (auto& conn : res) {
        auto box = sln.boundingbox(conn);
        std::cout << "bounding box = (" << box.first.r << "," << box.first.c << "), ("
         << box.second.r << "," << box.second.c <<")" << std:: endl;
        std::cout << "black points: ";
        for (auto& p : conn) {
            std::cout << "(" << p.r << "," << p.c << "), ";
        }
        std::cout << std::endl << std::endl;
    }

}