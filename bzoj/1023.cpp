#include<iostream>
#include<cstdio>
using namespace std;
const int u=50010,w=200010;
int ver[w],next[w],head[u],dfn[u],low[u],fa[u],f[u],q[u*2],a[u*2];
int n,m,tot,num,ans,i,j,k,x,y;
void add(int x,int y) {
    ver[++tot]=y;
    next[tot]=head[x];
    head[x]=tot;
}
void dp(int x,int y) {
    int m,i,l,r,p;
    for(m=0; y!=x; y=fa[y]) a[++m]=f[y];
    for(a[++m]=f[x],i=1; i<m; i++) a[m+i]=a[i];
    l=r=q[1]=1;
    p=m/2;
    for(i=2; i<=m+p; i++) {
        while(l<=r&&i-q[l]>p) l++;
        ans=max(ans,a[q[l]]+a[i]+i-q[l]);
        while(l<=r&&a[q[r]]+i-q[r]<=a[i]) r--;
        q[++r]=i;
    }
    for(i=1; i<m; i++) f[x]=max(f[x],a[i]+min(i,m-i));
}
void tarjan(int x) {
    dfn[x]=low[x]=++num;
    for(int i=head[x]; i; i=next[i])
        if(fa[x]!=ver[i])
            if(!dfn[ver[i]]) {
                fa[ver[i]]=x;
                tarjan(ver[i]);
                low[x]=min(low[x],low[ver[i]]);
                if(dfn[x]<low[ver[i]]) {
                    ans=max(ans,f[x]+f[ver[i]]+1);
                    f[x]=max(f[x],f[ver[i]]+1);
                }
            } else low[x]=min(low[x],dfn[ver[i]]);
    for(int i=head[x]; i; i=next[i])
        if(fa[ver[i]]!=x&&dfn[x]<dfn[ver[i]]) dp(x,ver[i]);
}
int main() {
    cin>>n>>m;
    for(i=1; i<=m; i++) {
        scanf("%d%d",&k,&x);
        for(j=1; j<k; j++) {
            scanf("%d",&y);
            add(x,y);
            add(y,x);
            x=y;
        }
    }
    tarjan(1);
    cout<<ans<<endl;
    return 0;
}
