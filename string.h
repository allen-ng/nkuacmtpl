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

		namespace ac_automaton {
#include <bits/stdc++.h>
			using namespace std;

			const int maxn = 10000;
			struct AC {
				map<int, AC*> next;
				int c;
				int cnt = 0;
				AC* fail = NULL, *fa = NULL;
			} nodes[maxn];
			int p = 1;
			AC* root;

			void init_ac() {
				root = nodes;
				root->c = 0;
				root->fail = NULL;
				root->fa = NULL;
			}

			void insert(string& s) {
				AC* curr = root;
				for(auto c : s) {
					if(curr->next.find(c) == curr->next.end()) {
						curr->next.insert(make_pair(c, &(nodes[p++])));
						curr->next[c]->c = c;
						curr->next[c]->fa = curr;
					}
					curr = curr->next[c];
				}
				curr->cnt++;
			}

			void build_ac() {
				static queue<AC*> q;
				for(auto pr : root->next) {
					q.push(pr.second);
				}
				AC* curr;
				while(!q.empty()) {
					AC* rt = q.front();
					q.pop();
					for(auto pr : rt->next) {
						q.push(pr.second);
					}
					curr = rt->fa == NULL ? NULL : rt->fa->fail;
					while(curr != NULL) {
						if(curr->next.find(rt->c) == curr->next.end()) {
							curr = curr->fail;
						} else {
							rt->fail = curr->next[rt->c];
							break;
						}
					}
					if(curr == NULL) {
						rt -> fail = root;
					}
				}
			}

			void query(string& s) {
				AC* curr = root;
				for(auto c : s) {
					while(curr != root && curr->next.find(c) == curr->next.end()) {
						curr = curr->fail;
					}
					if(curr == root && curr->next.find(c) == curr->next.end()) continue;
					curr = curr->next[c];
					if(curr->cnt != 0) {
						cout<<"YES"<<endl;
						return;
					}
				}
				cout<<"NO"<<endl;
			}
		} // namespace ac_automaton
		namespace sam {

			const int maxn = 100100;

			// define maxn beforehand
			int rt[maxn<<1]; // right
			int dd[maxn<<1]; // degree
			// remember change node type !
			struct node {
				// 如果被卡next可以考虑换成数组
				// 0代表无边, 后面克隆节点用Memcpy
				map<char, int> next;
				int link, len;
				int vis = -1;
			} st[maxn<<1];



			int sz = 1, last = 0;
			void init() {
				st[0].link = -1;
				st[0].len = 0;
				sz = 1; last = 0;
			}

			void debug() {
				for(int i = 0; i < sz; i++) {
					cerr<<"[ST "<<i<<"]: "<<endl;
					for(auto pr : st[i].next) {
						cerr<<"  ("<<pr.first<<", "<<pr.second<<")"<<endl;
					}
					cerr<<"  link: "<<st[i].link<<endl;
					cerr<<"  len : "<<st[i].len<<endl;
				}
			}
			void sa_extend(char c) {
				int cur = sz++;
				rt[cur] = 1;
				st[cur].len = st[last].len + 1;

				int p;
				for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link) 
					st[p].next[c] = cur;
				if (p == -1)
					st[cur].link = 0;
				else {
					int q = st[p].next[c];
					if (st[p].len + 1 == st[q].len) {
						st[cur].link = q;
					}
					else {
						int clone = sz++;
						st[clone].len = st[p].len + 1;
						st[clone].next = st[q].next;
						st[clone].link = st[q].link;
						for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
							st[p].next[c] = clone;
						}
						st[q].link = st[cur].link = clone;

					}
				}
				last = cur;
			}

			void build_right() {
				queue<int> q;
				for (int i = 1; i < sam::sz; i++) dd[sam::st[i].link]++;
				for (int j = 1; j < sam::sz; j++) if (dd[j] == 0) q.push(j);
				while (!q.empty()) {
					int x = q.front(); q.pop();
					int fa = sam::st[x].link;
					if (fa != -1) {
						rt[fa] += rt[x];
						dd[fa]--;
						if (dd[fa] == 0) {
							q.push(fa);
						}
					}
				}
			}
		} // namespace sam

		namespace manacher { //求最长回文子串
			const int maxn = 10010;
			int P[maxn];
			char s[maxn];
			char str[maxn<<1]; //需要提前准备数据, 参考下面的preparing data
			int manacher(int j) {
				// preparing data
				/*
					 int j = 1;
					 for(int i = 0; i < len; i++) {
					 str[j] = s[i];
					 str[j + 1] = '#';
					 j += 2;
					 }
					 */
				str[0] = '#';
				int mx = -1;
				int id, ans = -1;
				for(int i = 0; i < j; i++) {
					if(mx > i) 
						P[i] = min(P[2 * id - i], mx - i);
					else
						P[i] = 1;
					while(i - P[i] >= 0 && i + P[i] < j && str[i + P[i]] == str[i - P[i]]) 
						P[i]++;
					if(P[i] + i > mx) {
						mx = P[i] + i;
						id = i;
					}
					ans = max(P[i] - 1, ans);
				}
				return ans;

			}
		} // namespace manacher

	} // namespace str
} // namespace acm

#endif
