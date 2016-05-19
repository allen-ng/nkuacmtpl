#ifndef _ACM_UTILS
#define _ACM_UTILS
namespace acm {
	namespace utils {
				typedef long long ll;
		using namespace std;

		ll add(ll a, ll b, ll mod) {
			ll res = a + b;
			while(res < 0) res += mod;
			while(res >= mod) res -= mod;
			return res;
		}
		// untested
		// a * b % mod
		// O(logb)
		ll qmul(ll a, ll b, ll mod) {
			a %= mod;
			b %= mod;
			ll ans = 0;
			while(b) {
				if(b & 1) {
					ans = (ans + a)%mod;
				}
				a = (a+ a)%mod;
				b >>= 1;
			}
			return ans;
		}
		// untested
		// a^n % mod
		// O(logn)
		ll qpow(ll a, ll n, ll mod) {
			a %= mod;
			n %= mod;
			ll ans = 1LL;
			while(n) {
				if(n & 1) ans = (ans* a% mod);
				a = (a* a% mod);
				n >>= 1;
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
		// ******************************************
		// Miller Rabin 素性检测和 pollard rho分解整数
		// ******************************************
		bool randomized = false;
		// n - 1 = x * 2 ^ t,  a^(n - 1) = a^(x*2^t) = 1 mod (n)
		bool is_composite(ll a, ll n, ll x, ll t) {
			ll ret = qpow(a, x, n);
			ll last = ret;
			for(int i = 1; i <= t; i++) {
				ret = qmul(ret, ret, n);
				// 合数有非平凡根(二次同余的解)
				if(ret == 1 && last != 1 && last != n - 1) return true;
				last = ret;
			}
			if(ret != 1) return true;
			return false;
		}

		// S 测试次数
		bool mlrb(ll n, int S = 20) {
			if(!randomized) { srand(time(NULL)); randomized = true; }
			if(n < 2) return false;
			if(n == 2) return true;
			if((n&1) == 0) return false; // even
			ll x = n - 1, t = 0;
			while((x&1) == 0) { x >>= 1; t++; }

			for(int i = 0; i < S; i++) {
				ll a = rand() % (n - 1) + 1;
				if(is_composite(a, n, x, t)) return false;
			}
			return true;
		}

		// ***********
		// pollard_rho
		// ***********
		// 分解后无序, 如有必要需要排序!!!!
		ll factor[100];
		int tot;
		ll pollard_rho(ll n) {
			if(!randomized) { srand(time(0)); randomized = true; }
			ll i = 1, k = 2;
			ll x0 = rand() % n;
			ll y = x0;
			ll c = (rand() % (n - 1)) + 1;
			while(1) {
				i++;
				x0 = qmul(x0, x0, n);
				ll d = gcd(y - x0, n);
				if(d != 1 && d != n) return d;
				if(y == x0) return n;
				if(i == k) {
					y = x0;
					k += k;
				}
			}
		}

		void find_factor(ll n) {
			if(mlrb(n)) {
				factor[tot++] = n;
				return;
			}
			ll p = n;
			while(p >= n) p = pollard_rho(p);
			find_factor(p);
			find_factor(n / p);
		}

		bool vis[maxn + 10];
		int prime[maxn + 10];
		int mu[maxn + 10], cnt = 0;
		void sieve() {
			memset(vis, 0, sizeof vis);
			mu[1] = 1;
			rep(i, 2, maxn) {
				if(!vis[i]) {
					prime[cnt++] = i;
					mu[i] = -1;
				}
				rep(j, 0, cnt) {
					if(ll(i) * prime[j] > maxn) break;
					vis[i * prime[j]] = true;
					if(i % prime[j] == 0) {
						mu[i * prime[j]] = 0;
						break;
					} else { // i is prime
					mu[i * prime[j]] = -mu[i];
					}
				}
			}
		}

	}
}
#endif
