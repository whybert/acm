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

int n;
int f[20][12][2];
int cal(char a[20]) {
    int len = strlen(a);
    memset(f,0,sizeof f);
    rep(i,a[0]-'0') f[0][i][0] = 1;
    f[0][0][0] = 0;
    f[0][11][0] = 1;
    f[0][a[0]-'0'][1] = 1;
    int ans = 0;
    for (int i=0;i<len-1;i++) {
        int u = a[i] - '0', v = a[i+1] - '0';
        for (int j=0;j<v;j++) if (u-j>1 || j-u>1) f[i+1][j][0] += f[i][u][1];
        if (u-v>1 || v-u>1) f[i+1][v][1] += f[i][u][1];
        f[i+1][11][0] += f[i][11][0];
        rep(j,10)rep(k,12) {
            if (j==0 && k>9) continue;
            if (j-k>1 || k-j>1) {
                f[i+1][j][0] += f[i][k][0];
            }
        }
    }
    rep(i,12)rep(j,2) ans += f[len-1][i][j];
    return ans;
}
int test(char a[20]) {
    rep(i,strlen(a)-1) {
        if (abs(a[i] - a[i+1]) < 2) {
            return 0;
        }
    }
    return 1;
}
int main() {
    char a[20], b[20];
    while (~scanf("%s %s",&a,&b)) {
        printf("%d\n",cal(b) - cal(a) + test(a));
    }
    return 0;
}

