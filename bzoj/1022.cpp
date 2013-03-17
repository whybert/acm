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

int n;
int main() {
    cin>>n;
    while (~scanf("%d",&n)) {
        int s = 0,t,k = 0;
        rep(i,n) {
            scanf("%d",&t);
            s ^= t;
            if (t!=1) k = 1;
        }
        if (!k) {
            if (n%2) puts("Brother"); else puts("John");
        }
        else if (s) puts("John"); else puts("Brother");
    }
    return 0;
}


