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

struct AhoCorasick {
    static const int UNDEF = 0, MAXN = 205, CHARSET = 2;
    int end, tag[MAXN], fail[MAXN], trie[MAXN][CHARSET];

    void init() {
        tag[0] = UNDEF;
        fill(trie[0], trie[0] + CHARSET, -1);
        end = 1;
    }

    void add(int m, const char* s, int t) {
        int p = 0;
        rep(i, m) {
            int w = (*s)=='R' ? 0 : 1;
            if (trie[p][w] == -1) {
                tag[end] = UNDEF;
                fill(trie[end], trie[end] + CHARSET, -1);
                trie[p][w] = end++;
            }
            p = trie[p][w];
            s++;
        }
        tag[p] = t;
    }

    void build() {
        queue<int> bfs;
        fail[0] = 0;
        rep(i, CHARSET) {
            if (trie[0][i] != -1) {
                fail[trie[0][i]] = 0;
                bfs.push(trie[0][i]);
            } else trie[0][i] = 0;
        }
        while (!bfs.empty()) {
            int p = bfs.front();
            tag[p] |= tag[fail[p]];
            bfs.pop();
            rep(i, CHARSET) {
                if (trie[p][i] != -1) {
                    fail[trie[p][i]] = trie[fail[p]][i];
                    bfs.push(trie[p][i]);
                } else {
                    trie[p][i] = trie[fail[p]][i];
                }
            }
        }
    }
} ac;

const int L = 105, N = 205, mod = 1000000007;
int T, n, m;
char s1[L], s2[L];
int f[2][N / 2][N][4];

void update(int &a, int &b, int r) {
    a += b;
    a %= mod;
    if (r == 1) b = 0;
}

void dp() {
    memset(f, 0, sizeof f);
    f[0][0][0][0] = 1;
    int len = n + m;
    rep(i, len) {
        rep(j, n + 1) rep(k, ac.end) rep(l, 4) rep(r, 2) {
            int u = ac.trie[k][1 - r];
            update(f[1 - (i % 2)][j + r][u][l | ac.tag[u]], f[i % 2][j][k][l], r);
        }
    }
    int res = 0;
    rep(k, ac.end) {
        res += f[len % 2][n][k][3];
        res %= mod;
    }
    printf("%d\n", res);
}

int main() {
    cin >> T;
    while (T--) {
        scanf("%d %d", &n, &m);
        scanf("%s %s", s1, s2);
        ac.init();
        int l = strlen(s1);
        ac.add(l, s1, 1);
        l = strlen(s2);
        ac.add(l, s2, 2);
        ac.build();
        dp();        
    }
    return 0;
}

