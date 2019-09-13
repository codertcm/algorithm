
#include <bits/stdc++.h>
using namespace std;

typedef long long int LL;
const int N = 1010;
const int INF = 0x3f3f3f3f;

int n;
int a[N];
int sum[N];
int dp[N][N];

int minCost(){
    sum[0] = 0;
    for(int i=1;i<=n;i++){
        sum[i] = sum[i-1] + a[i];
    }
    for(int i=0;i<=n;i++){
        dp[i][i] = 0;
    }
    for(int w=2;w<=n;w++){
        for(int i=1;i<=n-w+1;i++){
            int j = i+w-1;
            int sumij = sum[j] - sum[i-1];
            dp[i][j] = INF;
            for(int k=i;k<j;k++){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + sumij );
            }
        }
    }
    return dp[1][n];
}

int main(int argc, char **argv)
{

	cin >> n;
	for(int i=1;i<=n;i++)
        cin >> a[i];
    cout << minCost() << endl;

	return 0;
}

