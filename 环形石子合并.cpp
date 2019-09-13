#include <iostream>
#include <string.h>
#include <stdio.h>
 
using namespace std;
const int INF = 1 << 30;
const int N = 205;
 
int mins[N][N];
int maxs[N][N];
int sum[N],a[N];
int minval,maxval;
int n;
 
int getsum(int i,int j)
{
    if(i+j >= n) return getsum(i,n-i-1) + getsum(0,(i+j)%n);
    else return sum[i+j] - (i>0 ? sum[i-1]:0);
}
 
void Work(int a[],int n)
{
    for(int i=0;i<n;i++)
        mins[i][0] = maxs[i][0] = 0;
    for(int j=1;j<n;j++)
    {
        for(int i=0;i<n;i++)
        {
            mins[i][j] = INF;
            maxs[i][j] = 0;
            for(int k=0;k<j;k++)
            {
                mins[i][j] = min(mins[i][j],mins[i][k] + mins[(i+k+1)%n][j-k-1] + getsum(i,j));
                maxs[i][j] = max(maxs[i][j],maxs[i][k] + maxs[(i+k+1)%n][j-k-1] + getsum(i,j));
            }
        }
    }
    minval = mins[0][n-1];
    maxval = maxs[0][n-1];
    for(int i=0;i<n;i++)
    {
        minval = min(minval,mins[i][n-1]);
        maxval = max(maxval,maxs[i][n-1]);
    }
}
 
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        sum[0] = a[0];
        for(int i=1;i<n;i++)
            sum[i] = sum[i-1] + a[i];
        Work(a,n);
        printf("%d %d\n",minval,maxval);
    }
    return 0;
}