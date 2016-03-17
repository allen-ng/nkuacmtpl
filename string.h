#ifndef _ACM_STRING
#define _ACM_STRING


namespace acm {
	namespace str {
		#include <bits/stdc++.h>
		using namespace std;
		const int maxn = 1e5;

		struct entry {
			int nr[2];
			int p; // Position
			bool operator<(const entry& b) const{ 
				bool l0 = nr[0] < b.nr[0],
						 l1 = nr[1] < b.nr[1];
				return nr[0] == b.nr[0] ? l1 : l0;
			}
		} L[maxn]; // The real suffix array

		int P[2][maxn];// Rank
		int LCP[maxn]; // height/Logest Common Prefix, from 1
		int stp; // used to access P

		
		// O(n) build lcp
		void build_lcp(int stp, string& s) {
			int i, j, k = 0;
			int n = s.size();
			// P[stp][i] is rank array
			for(i = 0; i < n; LCP[P[stp][i++]] = k) {
				for(k ? k-- : 0, j = L[P[stp][i] - 1].p; j + k < n && s[i + k] == s[j + k]; k++);
			}
		}

		// O(nlog^2n) build suffix array
		void build_suffix_array(string& s) {
			int N, i;
			int cnt;
			N = s.size();
			for(i = 0; i < N; i++) {
				P[0][i] = s[i] - 'a';
			}
			for(stp = 1, cnt = 1; cnt < N; stp ^= 1, cnt *= 2) {
				for(i = 0; i < N; i++) {
					L[i].nr[0] = P[stp ^ 1][i];
					L[i].nr[1] = i + cnt < N ? P[stp ^ 1][i + cnt] : -1;
					L[i].p = i;
				}
				// Can be altered to a 2-pass bucket
				sort(L, L + N);
				for(i = 0; i < N; i++) {
					// Calculate rank of index L[i].p, and thinking of the same rank
					P[stp][L[i].p] = i > 0 && L[i].nr[0]==L[i-1].nr[0] && L[i].nr[1] == L[i- 1].nr[1] ? P[stp][L[i-1].p] : i;
				}
			}
			build_lcp(stp, s); 
		} // build suffix array

		namespace trie {
			const int maxn = 2555;
			class Node {
				map<char, Node*> branch;
				bool isWord = false;
				char c = 0;
			} pool;
			int p = 1;
			void insert(string& s) {
				Node* root = pool;
				int sz = s.size();
				for(int i = 0; i < sz; i++) {
					Node* next = 0;
					if(root->branch.find(s[i]) == root->branch.end()) {
						next = &pool[p++];
						next->c = s[i];
						root->branch[s[i]] = next;
					}
					else
						next =root->branch[s[i]];
					root = next;
				}
				root->isWord = true;
			}
		}// namespace trie
	} // namespace str
} // namespace acm

#endif
