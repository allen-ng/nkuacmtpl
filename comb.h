#ifndef _ACM_COMBINATORICS
#define _ACM_COMBINATORICS
namespace acm {
	namespace comb {
		#include <bits/stdc++.h>
		#include "./utils.h"
		using namespace std;
		typedef long long ll;

		// untested
		ll lucas(ll n, ll m, ll mod) {
			return n / m * lucas(n % mod, m % mod) % mod;
		}
	}
}
#endif
