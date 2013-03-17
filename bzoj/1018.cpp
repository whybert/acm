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
    #define debug1(x) cout << #x" = " << x << endl;
    #define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
    #define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
    #define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

    #define lson l , m , rt << 1
    #define rson m + 1 , r , rt << 1 | 1

    using namespace std;

    const int N = 100005;
    int st[N << 2],C;
    int lc[N << 2][2],rc[N << 2][2];

    int T[64][64];
    void init() {
        rep(i1,2)rep(i2,2)rep(j1,2)rep(j2,2)rep(k1,2)rep(k2,2) {
            int t1 = i1 + i2 * 2 + j1 * 4 + j2 * 8 + k1 * 16 + k2 * 32;
            rep(m1,2)rep(m2,2)rep(n1,2)rep(n2,2)rep(p1,2)rep(p2,2){
                int t2 = m1 + m2 * 2 + n1 * 4 + n2 * 8 + p1 * 16 + p2 * 32;
                    T[t1][t2] = (i1 * m1 * k1 + i2 * n1 * k2 > 0)
                        + (i1 * m2 * k1 + i2 * n2 * k2 > 0) * 2
                        + (j1 * m1 * k1 + j2 * n1 * k2> 0) * 4
                        + (j1 * m2 * k1 + j2 * n2 * k2 > 0) * 8
                        + p1 * 16 + p2 *32;
            }
        }
    }

    void PushUp(int rt) {
        st[rt] = T[st[rt << 1]][st[rt << 1 | 1]];
    }

    void PushUp2(int rt, int len) {
        rep(i,2) {
            if (rc[rt << 1][i] == (len + 1)/2) rc[rt][i] = rc[rt << 1][i] + rc[rt << 1 | 1][i];
            else rc[rt][i] = rc[rt << 1][i];
            if (lc[rt << 1 | 1][i] == len/2) lc[rt][i] = lc[rt << 1][i] + lc[rt << 1 | 1][i];
            else lc[rt][i] = lc[rt << 1 | 1][i];
        }
    }

    void build(int l,int r,int rt) {
        if (l == r) {
            st[rt] = 9;
            lc[rt][0] = lc[rt][1] = 0;
            rc[rt][0] = rc[rt][1] = 0;
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUp(rt);
    }

    void update(int w,int c,int l,int r,int rt) {
        if (w == l && w == r) {
            if (c > 0) st[rt] |= c; else st[rt] &= (1 << 20) - 1 + c;
            return ;
        }
        int m = (l + r) >> 1;
        if (w <= m) update(w , c , lson);
        else update(w , c , rson);
        PushUp(rt);
    }

    void update2(int w,int d,int o,int u,int l,int r,int rt) {
        if (w == l && w == r) {
            if (d > 0) {
                rc[rt][u] = o;
            } else lc[rt][u] = o;
            return ;
        }
        int m = (l + r) >> 1;
        if (w <= m) update2(w , d , o , u , lson);
        else update2(w , d , o , u , rson);
        PushUp2(rt , r - l + 1);
    }

    int query(int L,int R,int l,int r,int rt) {
        if (L <= l && r <= R) {
            return st[rt];
        }
        int m = (l + r) >> 1;
        if (m >= R) return query(L , R , lson);
        if (m < L) return query(L , R , rson);
        return T[query(L , R , lson)][query(L , R , rson)];
    }

    int query2(int L,int R,int d,int u,int l,int r,int rt) {
        if (R < l || L > r) return 0;
        if (L <= l && r <= R) {
            if (d > 0) return rc[rt][u]; else return lc[rt][u];
        }
        int m = (l + r) >> 1;
        if (d > 0) {
            if (L > m) return query2(L , R , d , u , rson);
            int t1 = query2(L , R , d , u , lson);
            if (R > m && t1 == m - L + 1) {
                return t1 + query2(L , R , d , u , rson);
            }else return t1;
        } else {
            if (R <= m) return query2(L , R , d , u , lson);
            int t1 = query2(L , R , d , u , rson);
            if (L <= m && t1 == R - m) {
                return t1 + query2(L , R , d , u , lson);
            }else return t1;
        }
    }

    void gao(int x1,int y1,int x2,int y2) {
        int l1 = y1 - query2(1,y1,0,x1-1,1,C,1), r1 = y2 + query2(y2,C,1,x2-1,1,C,1);
        int t = query(l1,r1,1,C,1);
        int p = x1>1?4:1;
        t &= p * x2;
        if (t) puts("Y");else puts("N");
    }

    int main() {
        init();
        while (cin>>C) {
            char s[10];
            build(1,C,1);
            while (~scanf("%s",s)) {
                int x1,x2,y1,y2;
                if (s[0] == 'E') break;
                if (s[0] == 'O') {
                    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                    if (y1 > y2) swap(x1,x2),swap(y1,y2);
                    if (x1 == x2) {
                        update(y1,8<<x1,1,C,1);
                        update2(y1,1,1,x1-1,1,C,1);
                        update2(y2,0,1,x1-1,1,C,1);
                    }
                    else
                        update(y1,6,1,C,1);
                }
                if (s[0] == 'C') {
                    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                    if (y1 > y2) swap(x1,x2),swap(y1,y2);
                    if (x1 == x2) {
                        update(y1,-(8<<x1),1,C,1);
                        update2(y1,1,0,x1-1,1,C,1);
                        update2(y2,0,0,x1-1,1,C,1);
                    }
                    else
                        update(y1,-6,1,C,1);
                }
                if (s[0] == 'A') {

                    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                    if (y1 > y2) swap(x1,x2),swap(y1,y2);
                    int t = query(y1,y2,1,C,1);
                    int p = x1>1?4:1;
                    t &= p * x2;
                    if (t) puts("Y");else {
                        gao(x1,y1,x2,y2);
                    }
                }
            }
        }
        return 0;
    }
    /*
    10
    O 1 1 1 2
    O 1 2 1 3
    O 2 2 1 2
    O 2 2 2 3
    O 2 3 2 4
    O 2 4 2 5
    O 2 5 2 6
    O 2 7 2 8
    O 2 6 1 6
    O 1 5 1 6
    O 1 6 1 7
    C 2 3 2 4
    A 1 2 1 3

    */
