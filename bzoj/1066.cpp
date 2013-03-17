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

const int N = 2000, inf = 1 << 30;

struct netflow{
	int head[N],next[N * 10],link[N * 10],h[N],vh[N+3],n,s,t,tot;
	int c[N * 10];
	int dfs(int p,int f){
		if (p==t) return f;
		int rest=f;int minh=n;
		for (int i=head[p];i;i=next[i])
			if (c[i]){
				if (h[p]==h[link[i]]+1){
					int d=dfs(link[i],c[i]>rest?rest:c[i]);
					c[i]-=d;c[i^1]+=d;rest-=d;
					if (h[s]>=n) return f-rest;
				}
				if (h[link[i]]<minh) minh=h[link[i]];
				if (rest==0) break;
			}
		if (rest==f){
			if (--vh[h[p]]==0) h[s]=n;
			vh[h[p]=minh+1]++;
		}
		return f-rest;
	}
	int maxflow(){
		int ans=0;
		memset(h,0,sizeof(h));
		memset(vh,0,sizeof(vh));
		while (h[s]<n) ans+=dfs(s,inf);
		return ans;
	}
	void add(int a,int b,int cc){
		next[++tot]=head[a];
		head[a]=tot;
		link[tot]=b;
		c[tot]=cc;
		next[++tot]=head[b];
		head[b]=tot;
		link[tot]=a;
		c[tot]=0;
	}
	void init(){
		tot=1;
		memset(head,0,sizeof(head));
	}
} g;

char a[30][30], b[30][30];
map< pair<int,int> , int> M;
int main() {
    int r,c,d,cnt,sum;
    while (cin>>r>>c>>d) {
        rep(i,r) scanf("%s",a[i]);
        rep(i,r) scanf("%s",b[i]);
        sum = 0;
        rep(i,r)rep(j,c) if (b[i][j]=='L') sum++;
        cnt = 3;
        g.init();
        rep(i,r) rep(j,c) {
            if (a[i][j]!='0') {
                M[make_pair(i,j)] = cnt;
                if (b[i][j]=='L')
                    g.add(1,cnt,1);
                g.add(cnt, cnt + 1, a[i][j] - '0');
                cnt+=2;
            }
        }
        rep(i,r)rep(j,c)rep(k,r)rep(l,c) {
            if (a[i][j]!='0' && a[k][l]!='0' && abs(i-k)+abs(j-l)<=d) {
                if (i==k && j==l) continue;
                g.add(M[make_pair(i,j)]+1,M[make_pair(k,l)],10);
            }
        }
        rep(i,r)rep(j,c) {
            if (a[i][j]!='0' && (i<d || j<d || r-i<=d || c-j<=d)) {
                g.add(M[make_pair(i,j)]+1,2,10);
            }
        }
        g.s = 1;
        g.t = 2;
        g.n = cnt;
        cout<<sum - g.maxflow()<<endl;
    }
    return 0;
}
