//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
const int iinf = 0x7fffffff;
const ll linf = ~(1LL<<63);
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<ll, int> mli;
typedef map<ll, ll> mll;
template<typename T>
inline T gcd(T a, T b) { 
	if(a < b) return gcd(b, a); 
	if(b == 0) return a; 
	return gcd(b, a%b);
}
template<typename C> // container
inline void sort(C& v) {
	sort(v.begin(), v.end());
}
inline void println(int u) { printf("%d\n", u); }
inline void printsp(int u) { printf("%d ", u); }

// -------------------- Spliters ------------------------
#include "./geometry.h"
const int maxn = 200003;
//不检查ll是猪!!!

using namespace acm::geometry;
struct ConvexPolygonGame {
	int maxy[maxn], miny[maxn];

	inline int to_ind(int x) { return x + 100000; }
	inline int to_cor(int x) { return x - 100000; }

	string winner(vector<int> X, vector<int> Y) {
		memset(maxy, 0, sizeof maxy);
		memset(miny, 0, sizeof miny);
		int sz = X.size();
		int l=1e6, r = -1e6;
		int tot = 0;
		for(int i = 0; i < sz; i++) {
			Point a(X[i], Y[i]);
			Point b(X[(i + 1) % sz], Y[(i + 1) % sz]);
			l = min(min(to_ind(a.x), to_ind(b.x)), l);
			r = max(max(to_ind(a.x), to_ind(b.x)), r);
			if(a.x > b.x) { // top side,
				maxy[to_ind(a.x)] = a.y - 1;
				maxy[to_ind(b.x)] = b.y - 1;
				Line li(a, b);
				for(int x = a.x - 1; x >= b.x + 1; x--) {
					double y = li.at(x);
					maxy[to_ind(x)] = (int)floor(y);
				}
			} else if(a.x < b.x) { // bottom side
				miny[to_ind(a.x)] = a.y + 1;
				miny[to_ind(b.x)] = b.y + 1;
				Line li(a, b);
				for(int x = a.x + 1; x <= b.x - 1; x++) {

					double y = li.at(x);
					miny[to_ind(x)] = (int) ceil(y);
					
					if(x == -99990) {
						a.print();
						b.print();
						li.print();
						cerr<<y<<endl;
					}
					
				}
			} else { // a.x == b.x
				maxy[to_ind(a.x)] = max(a.y, b.y) - 1;
				miny[to_ind(a.x)] = min(a.y, b.y) + 1;
			}
		}
		vector<Point> pt;
		for(int x = l; x <= r; x++) {
			if(maxy[x] - miny[x] >= 0) {
				cout<<to_cor(x)<<": "; cout<<maxy[x]<<", "<<miny[x]<<endl;
				tot += maxy[x] - miny[x] + 1;
				if(tot > 200001) return "Masha";
				for(int y = miny[x]; y <= maxy[x]; y++) {
					pt.push_back(Point(to_cor(x), y));
				}
			}
		}
		if(pt.size() <= 2) return "Petya";
		Point a = pt[0], b = pt[1];
		int psz = pt.size();

		for(int i = 2; i < psz; i++) {
			if(!colinear(a, b, pt[i])) {
				return "Masha";
			}
		}
		return "Petya";
	}
};

int main()
{
	//ios::sync_with_stdio(0);
	ConvexPolygonGame sol;
	cout<<sol.winner(
			{-100000, 100000, -99933}, {-100000, 70000, -99943}
		)<<endl;


	return 0;
}
//--USE C++11


