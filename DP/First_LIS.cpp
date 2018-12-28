//#include <cstdio>
//#include <cstring>
//#include <algorithm>
//#include <ctime>
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
vi a,tmp,pos;
bool com(int a, int b){
    return a>b;
}
void print(int k){
    for(int i=0,j=a.size();i<j;++i){
        if(pos[i]==k){
            printf("%d ",a[i]);
            --k;
        }
    }
    printf("\n");
}
int main()
{
    //freopen("..\\file\\input.txt","r",stdin);
    //freopen("..\\file\\output.txt","w",stdout);
    /*clock_t start_c,end_c;
    start_c=clock();*/
    int n;
    while(~scanf("%d",&n) && n){
        a.clear(); tmp.clear(); pos.clear();
        for(int i=0;i!=n;++i){
            int in;
            scanf("%d",&in);
            a.push_back(in);
            pos.push_back(0);
        }
        tmp.push_back(a.back());
        int maxn=1; pos[n-1]=1;
        for(int i=n-2;i>=0;--i){
            if(a[i]<tmp.back()){
                tmp.push_back(a[i]);
                pos[i]=++maxn;
            }
            else{
                int k=lower_bound(tmp.begin(),tmp.end(),a[i],com)-tmp.begin();
                tmp[k]=a[i];
                pos[i]=k+1;
            }
        }
        printf("len = %d\nLIS : ",maxn);
        print(maxn);
    }
    /*end_c=clock();
    printf("Use %.0lf ms\n", (((double)(end_c-start_c))/CLOCKS_PER_SEC)*1000);*/
    return 0;
}

