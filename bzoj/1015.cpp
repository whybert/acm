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
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;
const int M = 200005;
int n,m,Q,a[2*M],cnt,fa[2*M];
pair<int,int> E[M];
vector<int> V[2*M],ans;
bool vis[2*M];
int find(int k) {
    if (fa[k] == k) return k;
    int p = fa[k];
    while (p!=fa[p]) p = fa[p];
    int t;
    while (k != fa[k]) {
        t = k;
        k = fa[k];
        fa[t] = p;
    }
    return p;
}
int main() {
    while (cin>>n>>m) {
        rep(i,n) {
            V[i].clear();
        }
        rep(i,m) {
            scanf("%d %d",&E[i].first,&E[i].second);
            V[E[i].first].push_back(E[i].second);
            V[E[i].second].push_back(E[i].first);
        }
        cin>>Q;
        memset(vis,0,sizeof vis);
        rep(i,Q) {
            scanf("%d",a+i);
            vis[a[i]] = 1;
        }
        rep(i,n) fa[i] = i;
        cnt = n;
        rep(i,n) {
            if (!vis[i]) {
                int t1 = find(i);
                rep(j,V[i].size()) {
                    if (!vis[V[i][j]]) {
                        int t2 = find(V[i][j]);
                        if (t1 != t2) fa[t2] = t1, cnt--;
                    }
                }
            }
        }
        ans.clear();
        ans.push_back(cnt);
        for (int i=Q-1;i>=0;i--) {
            int t1 = find(a[i]);
            rep(j,V[a[i]].size()) {
                if (!vis[V[a[i]][j]]) {
                    int t2 = find(V[a[i]][j]);
                    if (t2 != t1) fa[t2] = t1, cnt--;
                }
            }
            ans.push_back(cnt);
            vis[a[i]] = 0;
        }
        for (int i=Q;i>=0;i--) {
            printf("%d\n",ans[i] - Q + i);
        }
    }
    return 0;
}

