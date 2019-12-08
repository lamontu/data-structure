/* closest_pair.cpp */

#include <iostream>
#include <cmath>

using std::sort;
using std::min;
using std::cin;
using std::cout;

const int INF = 0x7fffffff;

struct Point {
  double x, y;
  Point(double x0=0, double y0=0) : x(x0), y(y0) {  }

  bool operator<(const Point& p) const {
    if (x != p.x) {
      return x < p.x;
    } else {
      return y < p.y;
    }
  }
};

Point p[200000+5];
Point temp[200000+5];

bool cmpy(Point a, Point b) {
  return a.y < b.y;
}

double Dis(Point a, Point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double n2MinDis(Point p[], int n) {
  double min_dis = INF;
  double dis;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      dis = Dis(p[i], p[j]);
      if (dis < min_dis) {
        min_dis = dis;
      }
    }
  }
  return min_dis;
}


double ClosestPair(int left, int right) {
  double d = INF;
  if (left == right) {
    return d;
  }
  if (left + 1 == right) {
    return Dis(p[left], p[right]);
  }
  int mid = (left + right) >> 1;
  double d1 = ClosestPair(left, mid);
  double d2 = ClosestPair(mid, right);
  d = min(d1, d2);
  int k = 0;
  for (int i = left; i <= right; ++i) {
    if (fabs(p[mid].x - p[i].x) <= d) {
      temp[k++] = p[i];
    }
  }
  sort(temp, temp + k, cmpy);
  for (int i = 0; i < k; ++i) {
    for (int j = i + 1; j < k && temp[j].y - temp[i].y < d; ++j) {
      double d3 = Dis(temp[i], temp[j]);
      d = min(d, d3);
    }
  }
  return d;
}

int main() {
  cout << "Point number: ";
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    double a, b;
    cout << "Point[" << i << "]: ";
    scanf("%lf%lf", &a, &b);
    p[i] = Point(a, b);
  }
  sort(p, p + n);
  printf("%.3f\n", n2MinDis(p, n));
  printf("%.3f\n", ClosestPair(0, n - 1));
  return 0;
}
