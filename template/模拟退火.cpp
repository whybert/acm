/*
codeforces 2C
author: qinz


*/
#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<map>
#include<math.h>
#include<algorithm>
#define MAX 3
using namespace std;
int X[MAX],Y[MAX],R[MAX];
double dx[4]= {0,1,0,-1},dy[4]= {1,0,-1,0};
const double eps=1e-7;
double dis(double x1,double y1,double x2,double y2) {
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double calc(double x,double y) {
    double dif,d[3];
    int i,j;
    for(i=0; i<3; i++)
        d[i]=dis(x,y,X[i],Y[i])/R[i];
    for(dif=i=0; i<3; i++)
        for(j=i+1; j<3; j++)
            dif+=(d[i]-d[j])*(d[i]-d[j]);
    return dif;
}
int main() {
    int i,best;
    double x,y,dis,now,t;
    for(x=y=i=0; i<3; i++) {
        scanf("%d%d%d",&X[i],&Y[i],&R[i]);
        x+=X[i];
        y+=Y[i];
    }
    x/=3;
    y/=3;
    dis=1;
    while(dis>eps) {
        now=calc(x,y);
        //printf("%.3f %.3f %.3f\n",x,y,now);
        for(best=-1,i=0; i<4; i++) {
            t=calc(x+dis*dx[i],y+dis*dy[i]);
            if(now>t) {
                now=t;
                best=i;
            }
        }
        if(best==-1)
            dis=0.7*dis;
        else {
            x+=dis*dx[best];
            y+=dis*dy[best];
        }
    }
    if(calc(x,y)<1e-5)
        printf("%.5f %.5f\n",x,y);
    return 0;
}
