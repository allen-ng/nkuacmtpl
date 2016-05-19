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
	} // ds
};
