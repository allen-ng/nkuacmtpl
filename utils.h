#ifndef _ACM_UTILS
#define _ACM_UTILS
namespace acm {
	namespace utils {
		// untested
		ll qpow(ll a, ll n, ll mod) {
			ll ans = 1LL;
			while(n) {
				if(n & 1) {
					ans = ans * a % mod;
				}
				a = (a * a) % mod;
			}
			return ans;
		}

		// untested
		ll qmul(ll a, ll b, ll mod) {
			ll ans = 0;
			while(b) {
				if(b & 1) {
					ans = (ans + a) % mod;
				}
				a = (a + a) % mod;
			}
			return ans;
		}
	}
}
#endif
