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

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;
int n, m, K;
string str;
int T[25][25];
void init() {
    string tmp;
    memset(T,0,sizeof T);
    T[0][1] = 1;
    T[0][0] = 9;
    for (int i = 0; i < m; i++) {
        tmp += str[i];
        for (int j = 0; j < 10; j++) {
            string temp = tmp + (char)('0' + j);
            int t = -1;
            for (int k = m - 1; k >= 0; k--) {
                if (k > i + 1) continue;
                for (int l = i + 1; l >= i + 1 - k; l--) {
                    if (temp[l] != str[k - i - 1 + l]) break;
                    if (l == i + 1 - k) t = k;
                }
                if (t != -1) break;
            }
            if (t != m - 1) T[i + 1][t + 1]++;
        }
    }

}
void mul(int M1[25][25],int M2[25][25]) {
    int tmp[25][25];
    memset(tmp,0,sizeof tmp);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                tmp[i][k] += M1[i][j] * M2[j][k];
                tmp[i][k] %= K;
            }
        }
    }
    memcpy(M1,tmp,sizeof tmp);
}
void pow(int n) {
    int P[25][25];
    memset(P,0,sizeof P);
    for (int i = 0; i < m; i++) P[i][i] = 1;
    while (n) {
        if (n&1) {
            mul(P,T);
        }
        mul(T,T);
        n >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans += P[0][i];
        ans %= K;
    }
    cout<<ans<<endl;
}
int main() {
    scanf("%d %d %d",&n,&m,&K);
    cin>>str;
    init();
    pow(n);
    return 0;
}

