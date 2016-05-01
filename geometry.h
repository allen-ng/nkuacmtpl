#ifndef _ACM_GEOMETRY
#define _ACM_GEOMETRY

namespace acm {
	namespace geometry {
		#include <iostream>
		using namespace std;
		// change to double if necessary
		// pay special attention to precision !!
		typedef long long T; 
		const double eps = 1e-8;
		struct Point {
			void print() {
				cerr<<"("<<x<<", "<<y<<")"<<endl;
			}
			T x, y;
			Point(T _x, T _y) : x(_x), y(_y) {}

			Point operator-(const Point& b) const {
				return Point(x - b.x, y - b.y);
			}
			Point operator+(const Point& b) const {
				return Point(x + b.x, y + b.y);
			}
			double operator^(const Point& b) const {
				return x * b.y - y * b.x;
			}
			double operator*(const Point& b) const {
				return x * b.x + y * b.y;
			}
		};

		bool colinear(Point& a, Point& b, Point& c) {
			return abs((b - a)^(c - a)) == 0;
		}

		struct Line {
			T A, B, C; // Ax + By + C = 0
			// a, b should not be the same
			Line(Point& a, Point& b) {
				A = b.y - a.y;
				B = -(b.x - a.x);
				C = a ^ b;
			}
			Line(T a, T b, T c):A(a), B(b), C(c) {}
			void print() {
				cerr<<"A: "<<A<<", B: "<<B<<", C: "<<C<<endl;
			}
			
			// please assure this line is not vertical to invoke this function
			double at(T x) {
				return 1.0*(-C - double(A) *x)/B;
			}
		};

		// 叉乘
		ll cross(const Point& a, const Point& b, const Point& c) {
				return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x -  a.x);
		}

		// 凸包, !!顺时针!!, 不包含重复点
		vector<Point> convexHull(vector<Point>& p) {
			int n = p.size();
			if(n <= 1) return p;
			sort(p.begin(), p.end(), [](const Point& a, const Point& b) -> bool {
					return a.x != b.x ? a.x < b.x : a.y < b.y;
					});
			vector<Point> q = vector<Point>(n * 2);
			int cnt = 0;
			for(int i = 0; i < n; q[cnt++] = p[i++])
				for(; cnt > 1 && cross(q[cnt - 2], q[cnt - 1], p[i]) >= 0; --cnt);
			for(int i = n - 2, t = cnt; i >= 0; q[cnt++] = p[i--]) 
				for(; cnt > t && cross(q[cnt - 2], q[cnt - 1], p[i]) >= 0; --cnt);
			int sz = cnt - 1 - (q[0].x == q[1].x && q[0].y == q[1].y ? 1 : 0);
			return vector<Point>(q.begin(), q.begin() + sz);
		}
	} // geometry
} //acm

#endif
