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

int n;
double g,a[100005],f[100005];
int main() {
    while (~scanf("%d %lf",&n,&g)) {
        for (int i=1;i<=n;i++) {
            scanf("%lf",a+i);
            f[i] = 0;
        }
        for (int i=1;i<=n;i++) {
            for (int j=1;j<=n;j++) {
                if (i!=j && i<=g*j) {
                    f[j] += a[i]*a[j]/(j-i);
                }
            }
            debug2(i,f[i]);
        }
    }
    return 0;
}
