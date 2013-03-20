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

#define lson l , m , rt << 1
#define rson m + 1, r , rt << 1 | 1

using namespace std;
const int N =  1 << 20;

int n, add[N], a[N];
long long sum;
int cnt;
double avg;

void pushDown(int rt) {
    add[rt << 1] += add[rt];
    add[rt << 1 | 1] += add[rt];
    add[rt] = 0;
}
void update(int l, int r, int rt, int p, int x) {
    if (p >= r) {
        add[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    update(lson, p, x);
    if (p > m)  update(rson, p, x);
}

int query(int l, int r, int rt, int p) {
    if (l == p && r == p) {
        int t = add[rt];
        add[rt] = 0;
        return t;
    }
    pushDown(rt);
    int m = (l + r) >> 1;
    if (p <= m) return query(lson, p);
    else return query(rson, p);
}

int main() {
    while (cin >> n) {
        cnt = 1;
        memset(add, 0, sizeof add);
        memset(a, 0, sizeof a);
        sum = 0;
        rep(i,n) {
            int t, p, x;
            scanf("%d",&t);
            if (t == 1) {
                scanf("%d %d", &p, &x);
                update(1, n, 1, p, x);
                sum += p * x;
            }
            if (t == 2) {
                scanf("%d", &x);
                cnt++;
                a[cnt] = x;
                sum += x;
            }
            if (t == 3) {
                sum -= a[cnt] + query(1, n, 1, cnt);
                cnt--;
            }
            avg = sum /(double)cnt;
            printf("%.7f\n",avg);
        }

    }
    return 0;
}

