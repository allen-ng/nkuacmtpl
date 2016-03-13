#ifndef _ACM_GEOMETRY
#define _ACM_GEOMETRY

namespace acm {
	namespace geometry {
		template<typename T, int N>
			struct Pt2d{
				T x, y;
				Pt2d(T _x, T _y) {
				}
				Pt2d operator+(Pt2d& b) {
					return Pt2d(x + b.x, y + b.y);
				}

				Pt2d operator-(Pt2d& b) {
					return Pt2d(x - b.x, y - b.y);
				}

				Pt2d operator*(Pt2d& b) {
					return Pt2d(x * b.x, y * b.y);
				}

				// Cross Product
				Pt2d operator^(Pt2d& b) {
					//return Pt2d(x * b.x, y * b.y);
				}

			};
	} // geometry
} //acm

#endif
