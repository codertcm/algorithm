#include <iostream>  
#include <cstring>  
  
using namespace std;  
  
const int INT_MAX2 = 0x7F7F7F7F;//并不是整数的最大值 只是将就的做法  
const int N = 1000;  
  
int v[N+1];  
int sum[N+1];  //sum[i] 代表从第0堆到i堆的石子数量和
int dp[N+1][N+1]; //dp[i][j] 代表第i堆石子到第j堆石子合并的最优值 
int p[N+1][N+1];  //p[i][j] 代表dp[i][j] 合适的k值
  
//合适的k值 使得 合并的顺序得到最优解 

int main()  
{  
    int n;  
  
    // 变量初始化：置为最大值  
    memset(dp, INT_MAX2, sizeof(dp));  
  
    // 输入数据  
    cin >> n;  
    sum[0] = 0;  
    for(int i=1; i<=n; i++) {  
        cin >> v[i];  
  
        sum[i] = sum[i-1] + v[i];  
        dp[i][i] = 0; //自己和自己合并 0 因为自己不能和自己合并
        p[i][i] = i;  //合适的k 为 i
    }  
  
    // DP计算   这里有点类似 滑动窗口的感觉
    for(int len=2; len<=n; len++)  // i 和j之间的区间大小 len
        for(int i=1; i+len-1<=n; i++) {  
            int j = i + len - 1;  
            //平行四边形等式优化
            //根据平行四边形规则有以下不等式：p[i][j-1]<=p[i][j]<=p[i+1][j]
            //原本遍历寻找k值 是从i开始到j 现在只需要缩小到从p[i][j-1] 到 p[i+1][j]
            for(int k=p[i][j-1]; k<=p[i+1][j]; k++) {  
                int val = dp[i][k] + dp[k+1][j] + sum[j] - sum[i-1];//计算合并的花费  
                if(dp[i][j]>val) {  //保存最小值
                    dp[i][j] = val;  
                    p[i][j] = k;  //记录取得最小值时候的k值
                }  
            }  
        }  
  
    // 输出结果  
    cout << dp[1][n] << endl;  
  
    return 0;  
}  