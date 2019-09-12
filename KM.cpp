/*
实际上，O(n^4)的KM算法表现不俗，使用O(n^3)并不会很大的提高KM的运行效率
需要在O(1)的时间找到任意一条边，使用邻接矩阵存储更为方便
*/
#include <cstring>
#include <cstdio>
const int maxn = 305;
const int INF = 0x3f3f3f3f;
int match[maxn],lx[maxn],ly[maxn],slack[maxn];
int G[maxn][maxn];
bool visx[maxn],visy[maxn];
int n,nx,ny,ans;

bool findpath(int x)
{
    int tempDelta;

    visx[x] = true;
    for(int y = 0 ; y < ny ; ++y){
        if(visy[y]) continue;
        tempDelta = lx[x] + ly[y] - G[x][y];
        if(tempDelta ==  0){//(x,y)在相等子图中
            visy[y] = true;
            if(match[y] == -1 || findpath(match[y])){
                match[y] = x;
                return true;
            }
        }
        else if(slack[y] > tempDelta)
            slack[y] = tempDelta;//(x,y)不在相等子图中且y不在交错树中
    }
    return false;
}
void KM()
{

    for(int x = 0 ; x < nx ; ++x){
        for(int j = 0 ; j < ny ; ++j) slack[j] = INF;//这里不要忘了，每次换新的x结点都要初始化slack
        while(true){
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));//这两个初始化必须放在这里,因此每次findpath()都要更新
            if(findpath(x)) break;
            else{
                int delta = INF;
                for(int j = 0 ; j < ny ; ++j)//因为dfs(x)失败了所以x一定在交错树中，y不在交错树中，第二类边
                    if(!visy[j] && delta > slack[j])
                        delta = slack[j];
                for(int i = 0 ; i < nx ; ++i)
                    if(visx[i]) lx[i] -= delta;
                for(int j = 0 ; j < ny ; ++j){
                    if(visy[j])
                        ly[j] += delta;
                    else
                        slack[j] -= delta;
                    //修改顶标后，要把所有的slack值都减去delta
                    //这是因为lx[i] 减小了delta
                    //slack[j] = min(lx[i] + ly[j] -w[i][j]) --j不属于交错树--也需要减少delta，第二类边
                }
            }
        }
    }
}
void solve()
{

   memset(match,-1,sizeof(match));
   memset(ly,0,sizeof(ly));
   for(int i = 0 ; i < nx ; ++i){
        lx[i] = -INF;
        for(int j = 0 ; j < ny ; ++j)
            if(lx[i] < G[i][j])
                lx[i] = G[i][j];
   }
   KM();
}
int main()
{
    while(scanf("%d",&n) != EOF){
        nx = ny = n;
        for(int i = 0 ; i < nx ; ++i)
            for(int j = 0 ; j < ny ; ++j)
                scanf("%d",&G[i][j]);
        solve();
        int ans = 0;
        for(int i = 0 ; i < ny ; ++i)
            if(match[i] != -1)
                ans += G[match[i]][i];
        printf("%d\n",ans);
    }
    return 0;
}
/*
简介: KM算法，用于求二分图匹配的最佳匹配。何为最佳匹配？就是带权二分图的权值最大的完备匹配称为最佳匹配。 那么何为完备匹配？X部中的每一个顶点都与Y部中的一个顶点匹配，或者Y部中的每一个顶点也与X部中的一个顶点匹配，则该匹配为完备匹配。
*/