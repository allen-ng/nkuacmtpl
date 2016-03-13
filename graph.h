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
			memset(head, -1, sizeof(head));
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

	} // graph
}// acm

#endif
