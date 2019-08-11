# 最长下降子序列

```c++

#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;
int ar[N], dp[N];

int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
        int i;
        for(i=1;i<=n;i++){
            scanf("%d",&ar[i]);
        }
        int p = 1;
        dp[0] = ar[n];
        for(i=n-1; i>=1; i--){
            int k = lower_bound(dp, dp+p, ar[i]) - dp;
            if(ar[i] > dp[p-1])
                dp[p++] = ar[i];
            else
                dp[k] = ar[i];
        }
        printf("%d\n",p);
    }
    return 0;
}

```
