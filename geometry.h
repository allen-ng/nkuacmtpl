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
	} // geometry
} //acm

#endif
