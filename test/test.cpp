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
#include "./string.h"
const int maxn = 100;
//不检查ll是猪!!!


int main()
{
	//ios::sync_with_stdio(0);

	string a = "missisippi";
	acm::str::build_suffix_array(a);
	for(int i = 0; i < a.size(); i++) {
		cout<<acm::str::L[i].p<<": ";
			cout<<acm::str::LCP[i];
		cout<<" "<<a.substr(acm::str::L[i].p)<<endl;
	}

	return 0;
}
//--USE C++11


