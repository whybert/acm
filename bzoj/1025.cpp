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

const int N = 1005;
int n;
long long f[N][N];
int prm[N], tot;
void getPrm() {
    tot = 1;
    for (int i=2;i<=n;i++) {
        bool is = 1;
        for (int j=2;j<=sqrt(i);j++) {
            if (i%j == 0) is = 0;
        }
        if (is) prm[tot++] = i;
    }
}
int mi(int p,int k) {
    int x = 1;
    for (int i=0;i<k;i++) x *= p;
    return x;
}
int main() {
    cin>>n;
    getPrm();
    memset(f,0,sizeof f);
    f[0][0] = 1;
    for (int i=1;i<tot;i++) {
        for (int j=0;j<=n;j++) {
            f[i][j] = f[i-1][j];
            for (int k=1;k<n;k++) {
                if (mi(prm[i],k) > j) break;
                f[i][j] += f[i-1][j-mi(prm[i],k)];
            }
        }
    }
    long long ans = 0;
    for (int i=0;i<=n;i++) {
        ans += f[tot-1][i];
    }
    cout<<ans<<endl;
    return 0;
}

