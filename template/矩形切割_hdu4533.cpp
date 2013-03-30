/*
 矩形切割 hdu4533

 ORZ岛娘！！！！


*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)
#define re(i,j,n) for(int i=j;i<n;i++)
#define down(i,n) for(int i=n;i>=0;i--)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
#define LL long long
#define INF (0x3f3f3f3f)
#define pb push_back
struct rec {
    int w, x, z, t;
    rec(int x): x(x), t(0), w(0), z(0) {}
    rec(int w, int x, int z, int t) : w(w), x(x), z(z), t(t) {}
    bool operator < (const rec & r) const {
        return x < r.x;
    }
};
vector<rec> event;

void Ins(int x,int y, int z) {
    event.pb(rec(x,min(y,z),0,1));      // t == 1 当扫描到min(y,z)时开启一段条行区域
    event.pb(rec(x,max(y,z),min(y,z),2));       // t == 2 当扫描到max(y,z)时关闭该段条行区域
}
void Ins(int x1, int y1, int x2, int y2) {
    Ins(1, x1, y1), Ins(1, x2, y2);
    Ins(-1, x2, y1), Ins(-1, x1, y2);
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        event.clear();
        rep(i, n) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2,&y2);
            Ins(x1, y1, x2, y2);
        }
        int q;
        cin >> q;
        rep(i, q) {
            int t;
            scanf("%d", &t);
            event.pb(rec(t));
        }
        sort(event.begin(), event.end());
        int sz = event.size();
        LL S = 0, A = 0, B = 0;
        rep(i,sz) {
            int w = event[i].w , x = event[i].x, z = event[i].z, t = event[i].t;
            if (event[i].t == 1) {
                B -= event[i].w;        // 辅助值，暂时替代A的作用
                A += (LL) event[i].w * event[i].x;
            } else if (event[i].t == 2) {
                S += (LL) event[i].w * event[i].x * event[i].z;
                A -= (LL) event[i].w * event[i].z;
            } else {
                LL ans = S + (LL) B * event[i].x * event[i].x + A * event[i].x;
                cout<< ans << endl;
            }
        }
    }
	return 0;
}




