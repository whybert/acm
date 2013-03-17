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

double X,Y;
int n;
double dfs(double x,double y,int n) {
    if (n == 1) return x>y?x/y:y/x;
    double MAX = 10000000;
    for (int i = 1; i < n; i++) {
        double tx = x*i/n , ty = y*i/n;
        MAX = min(max(dfs(tx,y,i), dfs(x-tx,y,n-i)),MAX);
        MAX = min(max(dfs(x,ty,i), dfs(x,y-ty,n-i)),MAX);
    }
    return MAX;
}
int main() {
    while (cin>>X>>Y>>n) {
        printf("%.6f\n",dfs(X,Y,n));
    }
    return 0;
}

