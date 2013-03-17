#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
using namespace std;
const int inf=~0U>>1,maxn=1000;
int n;
vector<int> Prime;
typedef vector<int>::iterator it;
int D[maxn],S=0,noLimit=0;
bool isPrime(int x) {
    if(x==2) return true;
    if(x/2==0) return false;
    for(int i=3; i*i<=x; i+=2)
        if(x%i==0) return false;
    return true;
}
void getPrime() {
    for(int i=2; i<=n; i++)
        if(isPrime(i)) Prime.pb(i);
}
void init() {
    cin>>n;
    rep(i,n) {
        cin>>D[i];
        if(D[i]>0)
            S+=D[i]-1;
        else
            noLimit++;
    }
}
struct BigInt {
    int H[400];
    BigInt() {
        memset(H,0,sizeof(H));
    }
    void mul(int x) {
        rep(i,Prime.size())
        while(x%Prime[i]==0) x/=Prime[i],H[i]++;
    }
    void div(int x) {
        rep(i,Prime.size())
        while(x%Prime[i]==0) x/=Prime[i],H[i]--;
    }
};
ostream& operator<<(ostream&out,const BigInt&x) {
    static int Hp[100000],last;
    memset(Hp,0,sizeof(Hp));
    Hp[last=0]=1;
    rep(i,Prime.size()) {
        rep(j,x.H[i]) {
            int o=Prime[i],d=0;
            rep(k,last+1) {
                d+=Hp[k]*o;
                Hp[k]=d%10;
                d/=10;
            }
            while(d) Hp[++last]=d%10,d/=10;
        }
    }
    for(int i=last; i>=0; --i)out<<Hp[i];
    return out;
}
void work() {
    if(S>n-2) {
        cout<<0<<endl;
        return;
    }
    if(noLimit==0&&S<n-2) {
        cout<<0<<endl;
        return;
    }
    getPrime();
    BigInt ans;
    for(int i=1; i<=n-2; i++)
        ans.mul(i);
    rep(i,n) {
        if(D[i]>0)
            for(int j=1; j<=D[i]-1; j++)
                ans.div(j);
    }
    for(int i=1; i<=n-2-S; i++)
        ans.div(i);
    rep(i,n-2-S) ans.mul(noLimit);
    cout<<ans<<endl;
}
int main() {
    //freopen("in","r",stdin);
    init();
    work();
}

