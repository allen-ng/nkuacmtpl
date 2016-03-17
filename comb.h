#ifndef _ACM_COMBINATORICS
#define _ACM_COMBINATORICS
namespace acm {
	namespace comb {
		#include <bits/stdc++.h>
		#include "./utils.h"
		using namespace std;
		typedef long long ll;

		// untested
		// naive C(n, m) % mod
		ll C(ll n, ll m, ll mod) {
		}
		// untested
		ll lucas(ll n, ll m, ll mod) {
			return lucas(n / p, m / p, mod) * C(n % mod, m % mod, mod) % mod;
		}
	}
}
#endif
