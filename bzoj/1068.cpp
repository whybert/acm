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

const int N = 100, inf = 0x3f3f3f3f;
char str[N];
int f[N][N], n,re[N][N];

bool ck(int l,int r) {
    if ((r - l) % 2 == 0) return false;
    int k = l, p = (r - l + 1)/2 + l;
    while (str[k] == str[p]) {
        if (p == r) return true;
        k++, p++;
    }
    return false;
}

int main() {
    while (~scanf("%s",str + 1)) {
        memset(f,0x3f,sizeof f);
        f[0][0] = 0;
        n = strlen(str + 1) + 1;
        rep(i,n)rep(j,n) if (j>i) re[i][j] = ck(i,j);
        int ans = inf;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (f[i][j] < inf) {
                    for (int k = i + 1; k < n; k++) {
                        if (ck(j,k)) {
                            int p = (k - j + 1)/2 + j - i;
                            if (p > 0) {
                                f[k][j] = min(f[k][j], f[i][j] + p);
                            }
                        }
                    }
                    for (int k = i + 1; k < n; k++) {
                        for (int l = k + 1; l < n; l++) {
                            if (re[k][l]) {
                                f[l][k] = min(f[l][k], f[i][j] + (k != 1) + k - i + (l - k + 1) / 2);
                            }
                        }
                    }
                    ans = min(ans, f[i][j] + n - 1 - i);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

