#ifndef _ACM_UTILS
#define _ACM_UTILS
namespace acm {
	namespace utils {
		// untested
		// a^n % mod
		// O(logn)
		typedef long long ll;
		using namespace std;

		ll qpow(ll a, ll n, ll mod) {
			ll ans = 1LL;
			while(n) {
				if(n & 1) ans = ans * a % mod;
				a = (a * a) % mod;
				n >>= 1;
			}
			return ans;
		}

		// untested
		// a * b % mod
		// O(logb)
		ll qmul(ll a, ll b, ll mod) {
			ll ans = 0;
			while(b) {
				if(b & 1) {
					ans = (ans + a) % mod;
				}
				a = (a + a) % mod;
				b >>= 1;
			}
			return ans;
		}

		// untested
		ll gcd(ll a, ll b) {
			if(a < 0) a = -a;
			if(b < 0) b = -b;
			if(a < b) swap(a, b);
			while(b) {
				ll c = b;
				b = a % b;
				a = c;
			}
			return a;
		}
		
		// untested
		ll extgcd(ll a, ll b, ll& x, ll& y)
		{
			if (b == 0) { x = 1LL; y = 0; return a; } 
			ll d = extgcd(b, a % b, x, y); 
			ll t = x; x = y; y = t - a / b * y; 
			return d; 
		}

		// untested
		// p should be a prime and gcd(a, p) = 1
		// based on Fermat Theory(费马小定理)
		inline ll reverse(ll a, ll p) {
			return qpow(a, p - 2, p);
		}

		// 线性同余方程(x === A[i] (mod M[i])), M[i] 不一定互质, 但是需要lcm不太大
		ll M[maxn], A[maxn];
		int N;

		ll lcm[maxn];
		void init() {
			ll g;
			lcm[0] = M[0];
			rep(i, 1, N) {
				g = gcd(lcm[i - 1], M[i]);
				lcm[i] = lcm[i - 1] * (M[i] / g);
			}
		}
		ll linear_mod_equation() {
			init();
			ll a = A[0];
			rep(i, 1, N) {
				ll g, k0, k, _;
				g = extgcd(lcm[i - 1], M[i],k0,_);
				if((A[i] - a) % g != 0) return -1;
				k0 = (k0 * ((A[i] - a) / g));
				while(k0 < 0) k0 += M[i];
				k0 %= M[i];
				a = ((k0 * lcm[i - 1] + a) + lcm[i]) % lcm[i];
			}
			return a == 0 ? lcm[N - 1] : a;
		}


	}
}
#endif
