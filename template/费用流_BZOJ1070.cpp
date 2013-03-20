#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <numeric>
#include <string>

#define rep(i,n) for(int i=0;i<n;i++)
#define re(i,j,n) for(int i=j;i<n;i++)
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;

const int maxn=1000, maxm = 100000;

struct costflow {
	int head[maxn],link[maxm],next[maxm],c[maxm],w[maxm],pre[maxn],d[maxn],h[maxn],s,t,n,tot;
	bool v[maxn],modify;
	bool spfa() {
		memset(d,0x6f,sizeof(d));
		memset(v,false,sizeof(v));
		int f=1,p=2;
		h[1]=s;d[s]=0;v[s]=true;
		while (p!=f){
			int i=head[h[f]];
			for (int i=head[h[f]];i;i=next[i])
				if (d[h[f]]+w[i]<d[link[i]]&&c[i]>0){
					d[link[i]]=d[h[f]]+w[i];
					pre[link[i]]=i;
					if (!v[link[i]]){
						v[link[i]]=true;
						h[p]=link[i];
						if (++p>=maxn) p=1;
					}
				}
			v[h[f]]=false;
			if (++f>=maxn) f=1;
		}
		if (d[t]<0x3f3f3f) return true;
		else return false;
	}
	int mincost(){
		int ans=0;
		modify=true;
		while (!modify||spfa()){
			int i=t;
			modify=false;
			while (i!=s){
				ans+=w[pre[i]];
				if (--c[pre[i]]==0) modify=true;
				if (++c[pre[i]^1]==1) modify=true;
				i=link[pre[i]^1];
			}
		}
		return ans;
	}
	void add(int a,int b,int cc,int ww){
		next[++tot]=head[a];
		head[a]=tot;
		link[tot]=b;
		w[tot]=ww;
		c[tot]=cc;
		next[++tot]=head[b];
		head[b]=tot;
		link[tot]=a;
		w[tot]=-ww;
		c[tot]=0;
		if (tot>=maxm) while(1);
	}
	void init(){
		memset(head,0,sizeof(head));
		tot=1;
	}
} g;

int n, m;

int main() {
    while (cin>>m>>n) {
        g.init();
        g.s = 1;
        int t = 2;
        rep(i,m) {
            rep(j,n) {
                g.add(1,t,1,0);
                t++;
            }
        }
        int c, p = t;
        rep(i,n) {
            rep(j,m) {
                scanf("%d", &c);
                rep(k,n) {
                    g.add(2 + j * n + k, t, 1, c * (k + 1));
                }
            }
            t++;
        }
        re(i,p,t)
            g.add(i, t, 1, 0);
        g.t = t;
        g.n = t;
        int mincost = g.mincost();
        double ans = mincost / (double)(n);
        printf("%.2f\n",ans);
    }
    return 0;
}

