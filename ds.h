namespace acm {
	namespace ds {
		namespace rmq {
			const int maxn = 2e5;
			int a[maxn];
			int rmq[maxn][18];
			int id[maxn][18];
			int n;
			void RMQ_init()
			{
				for(int i=1; i<=n; i++) {
					rmq[i][0]=a[i];
					id[i][0] = i;
				}
				for(int j=1; (1<<j)<=n; j++)
					for(int i=1;i+(1<<j)-1<=n;i++) {
						int b = i + (1<<(j - 1));
						if(rmq[i][j - 1] > rmq[b][j - 1]) {
							rmq[i][j] = rmq[i][j - 1];
							id[i][j] = id[i][j - 1];
						} else {
							rmq[i][j] = rmq[b][j - 1];
							id[i][j] = id[b][j - 1];
						}
						rmq[i][j]=max(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
					}
			}
			// id 为返回的下标
			pii RMQ(int L,int R)
			{
				int k=0;
				while((1<<(k+1))<=R-L+1) k++;
				int b = R - (1<<k) + 1;
				return rmq[L][k] > rmq[b][k] ?
					mp(rmq[L][k], id[L][k]) :
					mp(rmq[b][k], id[b][k]);
			}
		} // rmq
		namespace hldecomp { // 树链剖分(带O(2n)空间的线段树)
			//{{{
			struct Edge {
				int to;
				int val;
				Edge(int a, int b) : to(a), val(b) {}
			};
			#define to(e) (e.to)
			class ST { // Segment Tree
				public:
					const static int oo = 0x7fffffff;
					inline int lc(int x) { return x<<1; }
					inline int rc(int x) { return (x<<1)|1; }

					vector<int> st;
					int* a, n;

					// black magic
					inline int id(int l, int r) {
						return l + r | (l != r);
					}

					void init(int* _a, int _n) {
						n = _n;
						a = _a;
						st.assign((n + 1) * 2, 0);
						build(1, n);
					}
					int build(int l, int r) {
						int rt = id(l, r);
						if(l == r) { st[rt] = a[l]; return st[rt]; }
						int m = (l + r) >> 1;
						return st[rt] = max(build(l, m), build(m + 1, r));
					}

					void update(int p, int v) { update(p, v, 1, n); }
					int update(int p, int v, int l, int r) {
						int rt = id(l, r);
						if(l == r) {st[rt] = v; return st[rt]; }
						int m = (l + r) >> 1;
						if(p <= m) update(p, v, l, m);
						else update(p, v, m + 1, r);
						return st[rt] = max(st[id(l, m)], st[id(m + 1, r)]);
					}

					int query(int l, int r) { return query(l, r, 1, n); }
					int query(int ql, int qr, int l, int r) {
						int rt = id(l, r);
						if(ql <= l && r <= qr) return st[rt];
						int m = (l + r) >> 1;
						int ans = -oo;
						if(ql <= m) ans = max(query(ql, qr, l, m), ans);
						if(qr >= m + 1) ans = max(query(ql, qr, m + 1, r), ans);
						return ans;
					}
			};
			//}}}


			// {{{
			class HLD { // HL Decomposition
				public:
					const static int oo = 0x7fffffff;
					vector<Edge>* E;
					int totC;
					vector<int> cHead, cPos, // pos starting from 1
						cInd, cSz;
					vector<int> sSz; // subtree size
					vector<int> par; // parent
					vector<int> depth;
					/* Customized data structures */
					vector<int> a;
					vector<int> val;
					vector<ST> sts;
					/* -------------------------- */

					HLD() : totC(0), E(0) {}
					void init(vector<Edge>* tree, int n, int root) {
						cHead.assign(n + 1, -1);
						cPos.assign(n + 1, 0);
						cInd.assign(n + 1, 0);
						sSz.assign(n + 1, 0);
						cSz.assign(n + 1, 0);
						depth.assign(n + 1, 0);
						par.assign(n + 1, 0); //7 initialization

						/* Customized data structures */
						a.assign(n + 1, 0);
						val.assign(n + 1, 0);
						/* -------------------------- */

						E = tree;
						totC = 0;
						val[0] = -oo;
						dfs(root); // cal subsz
						hld(root);
						totC++;
					}

					void dfs(int cur, int fa = -1, int dep = 0) {
						sSz[cur]++;
						par[cur] = fa;
						depth[cur] = dep;
						for(int i = 0; i < E[cur].size(); i++) {
							Edge e = E[cur][i];
							if(to(e) == fa) continue;
							val[to(e)] = e.val;
							dfs(to(e), cur, dep + 1);
							sSz[cur] += sSz[to(e)];
						}
					}

					void hld(int cur, int fa = -1) {
						if(cHead[totC] == -1) cHead[totC] = cur;
						cInd[cur] = totC;
						cPos[cur] = cSz[totC];
						// varies
						a[cSz[totC] + 1] = val[cur];
						cSz[totC]++;

						int ind = -1, mai = -1;
						int cnt = 0;
						for(int i = 0; i < E[cur].size(); i++) {
							Edge nxt = E[cur][i];
							int t = to(nxt);
							if(t == fa) continue;
							cnt++;
							if(sSz[t] > mai) {
								mai = sSz[t];
								ind = t;
							}
						}
						if(cnt == 0) {
							sts.pb(ST());
							sts.back().init(&a[0], cSz[totC] + 1);	
						}

						if(ind > 0) hld(ind, cur);

						for(int i = 0; i < E[cur].size(); i++) {
							Edge nxt = E[cur][i];
							int t = to(nxt);
							if(t == fa || t == ind) continue;

							totC++;
							hld(t, cur);
						}
					}

					int LCA(int u, int v) {
						int uc = cInd[u], vc = cInd[v];
						while(uc != vc) {
							if(depth[cHead[uc]] > depth[cHead[vc]]) {
								u = par[cHead[uc]];
								uc = cInd[u]; 
							} else if(depth[cHead[uc]] < depth[cHead[vc]]) {
								v = par[cHead[vc]];
								vc = cInd[v];
							} else { // same depth
								u = par[cHead[uc]];
								v = par[cHead[vc]];
								uc = cInd[u];
								vc = cInd[v];
							}
						}
						if(depth[u] > depth[v]) return v;
						else return u;
					}

					int queryUp(int u, int v) { // v is ancestor of u
						int uch = cInd[u], vch = cInd[v], ans = -1;
						// [v, u]
						while(1) {
							if(uch == vch) {
								if(cPos[v] + 1 > cPos[u]) return ans;
								// Pay attention, here, cPos[v] + 1 means querying on edges!
								int cur = sts[vch].query(cPos[v] + 1, cPos[u]);
								ans = max(ans, cur);
								return ans;
							}
							int cur = sts[uch].query(1, cPos[u]);
							ans = max(ans, cur);

							// jump up
							u = par[cHead[uch]];
							uch = cInd[u];
						}
					}

					int query(int u, int v) {
						int lca = LCA(u, v);
						return max(queryUp(u, lca), queryUp(v, lca));
					}

					void update(int p, int v) {
						sts[cInd[p]].update(cPos[p], v);
					}

			};
			//}}}


			const int maxn = 10100;

			void addedge(vector<Edge>* E, int u, int v, int c) {
				E[u].pb(Edge(v, c));
				E[v].pb(Edge(u, c));
			}

		}; // hldecomp
	} // ds
};
