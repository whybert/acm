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
const int N = 50005;
typedef long long LL;
map<int,int> M;
int a[N], f[N][20];
int n,Q;
void init() {
    memset(f,0xef,sizeof f);
    re(i,1,n+1) f[i][0] = a[i];
    re(j,1,20)re(i,1,n+1) {
        if (i + (1 << (j - 1)) > n) break;
        f[i][j] = max(f[i][j-1], f[i + (1 << (j-1))][j-1]);
    }
}
int query(int u,int v) {
    u = a[u], v = a[v];
    int MAX = a[u];
    for (int i = 18; i >= 0; i--) {
        if (u + (1 << i) <= v) {
            MAX = max(MAX,f[u][i]);
            u += 1 << i;
        }
    }
    MAX = max(MAX, f[u][0]);
    return MAX;
}
void go1(int u,int v) {
    if (u==v) {
        puts("true");
        return;
    }
    int p = M[u], q = M[v];
    if (query(p + 1,q-1) >= a[q]) {
        puts("false");
    } else {
        if (a[p] < a[q]) {
            puts("false");
        } else {
            if (q-(LL)p==v-(LL)u) {
                puts("true");
            } else puts("maybe");
        }
    }
}
void go2(int u,int v) {
    pair<int,int> t = *(M.lower_bound(v));
    int p = M[u], q;
    if (t.first > v) {
        q = t.second - 1;
    } else q = t.second;
    if (t.second == 0) q = n;
    if (p==q) puts("maybe");
    else
        if (query(p+1,q)>=a[p]) {
            puts("false");
        }else puts("maybe");
}
void go3(int u,int v) {
    pair<int,int> t = *(M.lower_bound(u));
    int p, q = M[v];
    if (t.first < u) {
        p = t.second + 1;
    } else p = t.second;
    if (p == q) puts("maybe");
    else
        if (query(p,q-1)>=a[q]) {
            puts("false");
        }else puts("maybe");
}
void go4(int u,int v) {
    puts("maybe");
}
int main() {

    while (cin>>n) {
        M.clear();
        rep(i,n) {
            int y;
            scanf("%d %d",&y,a + i + 1);
            M[y] = i + 1;
        }
        init();
        scanf("%d",&Q);
        rep(i,Q) {
            int u,v;
            scanf("%d %d",&u,&v);
            if (M.find(u)->second && M.find(v)->second) go1(u,v);
            else
            if (M.find(u)->second && !M.find(v)->second) go2(u,v);
            else
            if (!M.find(u)->second && M.find(v)->second) go3(u,v);
            else
            if (!M.find(u)->second && !M.find(v)->second) go4(u,v);
        }
    }
    return 0;
}

