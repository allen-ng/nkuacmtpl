#ifndef _ACM_GRAPH
#define _ACM_GRAPH

namespace acm {
	namespace graph {
		#include <bits/stdc++.h>
		using namespace std;

		const int N = 510;
		const int M = 1000010;
		const int INF = 0x7f7f7f7f;

		struct Edge {
			int v, cap, cost, next;
			Edge() {}
			Edge(int a, int b, int c, int d)
				:v(a), cap(b), cost(c), next(d) {}
		}e[M];
		int head[N], sz;
		int dis[N], pre[N], cur[N];
		bool inq[N];
		queue<int> q;

		void graphinit() {
			rep(i, 0, N) head[i] = -1;
			sz = 0;
		}
		void addedge(int u, int v, int cp, int ct) {
			//printf("%d %d %d %d\n", u, v, cp, ct);
			e[sz] = Edge(v, cp, ct, head[u]);
			head[u] = sz++;
			e[sz] = Edge(u, 0, -ct, head[v]);
			head[v] = sz++;
		}
		pair<int, int> mcmf(int s, int t) {
			int mc = 0, mf = 0;
			while (true) {
				memset(pre, -1, sizeof(pre));
				memset(inq, 0, sizeof(inq));
				memset(dis, 0x7f, sizeof(dis));
				dis[s] = 0;
				q.push(s);
				while (!q.empty()) {
					int u = q.front(); q.pop();
					inq[u] = false;
					for (int i = head[u]; i != -1; i = e[i].next) {
						int v = e[i].v;
						if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
							dis[v] = dis[u] + e[i].cost;
							pre[v] = u; cur[v] = i;
							if (!inq[v]) { inq[v] = true; q.push(v); }
						}
					}
				}
				if (pre[t] == -1) break;
				int aug = INF;
				for (int i = t; i != s; i = pre[i])
					aug = min(aug, e[cur[i]].cap);
				mf += aug;
				mc += dis[t] * aug;
				for (int i = t; i != s; i = pre[i]) {
					e[cur[i]].cap -= aug;
					e[cur[i] ^ 1].cap += aug;
				}
			}
			return make_pair(mf, mc);
		}
		struct MaximumFlow {
#define each(it,o) for(auto it = (o).begin(); it != (o).end(); ++ it)
			static const int INF = 0x3f3f3f3f;
			typedef int Index;
			typedef int Flow;
			static const Flow InfCapacity = INF;
			struct Edge {
				Index to;
				Flow capacity;
				Index rev;
			};
			vector<vector<Edge> > g;
			void init(Index n) { g.assign(n, vector<Edge>()); }
			void add(Index i, Index j, Flow capacity) {
				Edge e, f; e.to = j, f.to = i; e.capacity = capacity, f.capacity = 0;
				g[i].push_back(e); g[j].push_back(f);
				g[i].back().rev = (Index)g[j].size() - 1; g[j].back().rev = (Index)g[i].size() - 1;
			}
			void addB(Index i, Index j, Flow capacity) {
				Edge e, f; e.to = j, f.to = i; e.capacity = capacity, f.capacity = capacity;
				g[i].push_back(e); g[j].push_back(f);
				g[i].back().rev = (Index)g[j].size() - 1; g[j].back().rev = (Index)g[i].size() - 1;
			}
			//gを破壊する
			Flow maximumFlow(int s, int t) {
				int n = g.size();
				vector<Index> level(n);
				Flow total = 0; bool update;
				do {
					update = false;
					fill(level.begin(), level.end(), -1); level[s] = 0;
					queue<Index> q; q.push(s);
					for(Index d = n; !q.empty() && level[q.front()] < d; ) {
						int u = q.front(); q.pop();
						if(u == t) d = level[u];
						each(e, g[u]) if(e->capacity > 0 && level[e->to] == -1)
							q.push(e->to), level[e->to] = level[u] + 1;
					}
					vector<Index> iter(n);
					for(Index i = 0; i < n; i ++) iter[i] = (int)g[i].size() - 1;
					while(1) {
						Flow f = augment(level, iter, s, t, InfCapacity);
						if(f == 0) break;
						total += f; update = true;
					}
				} while(update);
				return total;
			}
			Flow augment(vector<Index> &level, vector<Index> &iter, Index u, Index t, Flow f) {
				if(u == t || f == 0) return f;
				Index lv = level[u];
				if(lv == -1) return 0;
				level[u] = -1;
				for(; iter[u] >= 0; -- iter[u]) {
					Edge &e = g[u][iter[u]];
					if(level[e.to] <= lv) continue;
					Flow l = augment(level, iter, e.to, t, min(f, e.capacity));
					if(l == 0) continue;
					e.capacity -= l; g[e.to][e.rev].capacity += l;
					level[u] = lv;
					return l;
				}
				return 0;
			}
		};

	} // graph
}// acm

#endif
