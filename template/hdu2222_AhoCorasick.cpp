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
int T, n;
struct AhoCorasick {
    static const int UNDEF = 0;
    static const int MAXN = 300005;
    static const int CHARSET = 26;

    int end;
    int tag[MAXN];
    int fail[MAXN];
    int trie[MAXN][CHARSET];
    
    void init() {
        tag[0] = UNDEF;
        fill(trie[0], trie[0] + CHARSET, -1);
        end = 1;
    }

    void add(int m, const char* s, int t) {
        int p = 0;
        rep(i, m) {
            int w = *s - 'a';
            if (trie[p][w] == -1) {
                tag[end] = UNDEF;
                fill(trie[end], trie[end] + CHARSET, -1);
                trie[p][w] = end++;
            }
            p = trie[p][w];
            s++;
        }
        tag[p] += t;
    }

    void build() {
        queue<int> bfs;
        fail[0] = 0;
        rep(i, CHARSET) {
            if (trie[0][i] != -1) {
                fail[trie[0][i]] = 0;
                bfs.push(trie[0][i]);
            } else {
                trie[0][i] = 0;
            }
        }
        while (!bfs.empty()) {
            int p = bfs.front();
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

    int work(int m, char* s) {
        int p = 0, res = 0;
        rep(i, m) {
            int w = *s - 'a';
            p = trie[p][w];
            int u = p;
            while (u && tag[u] != -1) {
                res += tag[u];
                tag[u] = -1;
                u = fail[u];
            }
            s++;
        }
        return res;
    }

} ac;
const int L = 55, N = 1000005;;
char tmp[L], S[N];
int main() {
    cin >> T;
    while (T--) {
        ac.init();
        scanf("%d", &n);
        rep(i, n) {
            scanf("%s", tmp);
            int l = strlen(tmp);
            ac.add(l, tmp, 1);
        }
        ac.build();
        scanf("%s", S);
        int l = strlen(S);
        printf("%d\n", ac.work(l, S));
    }
    return 0;
}

