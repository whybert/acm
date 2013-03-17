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
#include <stack>

#define rep(i,n) for(int i=0;i<n;i++)
#define re(i,j,n) for(int i=j;i<n;i++)
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;

int n,f[5];
char S[6][3];
stack<int> T[3];
long long ans[100];
int cal(int k) {
    int cnt = 0, used = -1;
    rep(i,3) while (!T[i].empty()) T[i].pop();
    rep(i,k) T[0].push(k-i);
    while (1) {
        rep(i,6) {
            int u = S[i][0] - 'A', v = S[i][1] - 'A';
            if (T[u].empty() || used == T[u].top()) continue;
            if (!T[v].empty() && T[u].top() > T[v].top()) continue;
            cnt++;
            used = T[u].top();
            T[v].push(used);
            T[u].pop();
            if (T[v].size() == k) return cnt;
            break;
        }
    }
}
int main() {
    while (cin>>n) {
        rep(i,6) {
            scanf("%s",S[i]);
        }
        re(k,2,5) {
            f[k-2] = cal(k);
        //    debug2(k,f[k-2]);
        }
        int u = (f[1] - f[0])/(f[0] - 1) ,v = f[0] - u;
        ans[1] = 1;
        ans[2] = f[0];
        re(i,3,n + 1) {
            ans[i] = u * ans[i-1] + v;
        }
        cout<<ans[n]<<endl;
    }
    return 0;
}

