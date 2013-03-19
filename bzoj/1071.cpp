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

const int N = 5005;
int n,a,b,c;
int h[N], s[N], f[N], id1[N], id2[N];
bool vis[N];

bool cmp1(int i, int j) {
    return (h[i] > h[j]);
}
bool cmp2(int i,int j) {
    return (f[i] > f[j]);
}
int main() {
    while (~scanf("%d %d %d %d", &n, &a, &b, &c)) {
        rep(i, n) {
            scanf("%d %d", h + i, s + i);
            f[i] = a * h[i] + b * s[i] - c;
            id1[i] = i;
            id2[i] = i;
        }
        sort(id1, id1 + n, cmp1);
        sort(id2, id2 + n, cmp2);
        int ans = 0;
        rep(i, n) {
            int val = a * h[i] + b * s[i], p1 = n, p2;
            int cnt = 0;
            memset(vis, 0, sizeof vis);
            rep(j, n) {
                if (f[id2[j]] <= val) {
                    if (p1 == n) p1 = j;
                    if (s[id2[j]] >= s[i] && h[id2[j]] >= h[i]) {
                        vis[id2[j]] = 1;
                        cnt++;
                    }
                }
            }
            if (cnt > ans) ans = cnt;
            rep(j, n) {
                if (h[id1[j]] == h[i]) {
                    p2 = j;
                    break;
                }
            }
            re(j, p2, n) {
                if (s[id1[j]] >= s[i]) {
                    val = a * h[id1[j]] + b * s[i];
                    if (f[id1[j]] > val) continue;
                    if (!vis[id1[j]]) {
                        vis[id1[j]] = 1;
                        cnt++;
                    }
                    while (p1 < n) {
                        if (f[id2[p1]] > val)  {
                            if (vis[id2[p1]]) cnt--;
                            p1++;
                        }
                        else break;
                    }
                    if (p1 == n) break;
                    if (cnt > ans) ans = cnt;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

