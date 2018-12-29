//#include <cstdio>
//#include <cstring>
//#include <algorithm>
//#include <ctime>
#include <bits/stdc++.h>
using namespace std;
int dp[1001][1001];
int main()
{
    //freopen("..\\file\\input.txt","r",stdin);
    //freopen("..\\file\\output.txt","w",stdout);
    /*clock_t start_c,end_c;
    start_c=clock();*/
    int m,n,M;
    while(~scanf("%d",&n) && n){
        scanf("%d%d",&m,&M);
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=m;++i)
            for(int j=0;j<=n;++j)
                dp[i][j]=j>=i?(dp[i][j-i]+dp[i-1][j])%M:dp[j][j];
        printf("%d\n",dp[m][n]);
    }
    /*end_c=clock();
    printf("Use %.0lf ms\n", (((double)(end_c-start_c))/CLOCKS_PER_SEC)*1000);*/
    return 0;
}

