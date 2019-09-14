//我们使用SPFA来维护每个点的距离标号，然后用zkw在dfs的思想进行多路増广，
//这样时间效率还是可以快很多（而且这样似乎可以跑负权图，然而zkw原版的不可以） 
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

struct node
{
    int x,y,c,cc,next;
}a[2100000];//数组模拟链表存储边 
int len=1,last[210000],maxn=1e9;
int vis[210000];int dis[210000];
//解释一下各数组的含义：vis两个用处：spfa里的访问标记，増广时候的访问标记，dis是每个点的距离标号
int n,m,s,t,ans=0,x,y,c,cc,k;
//s是起点，t是终点，ans是费用答案
inline int add(int x,int y,int c,int cc)
{
    len++;
    a[len].x=x;a[len].y=y;a[len].c=c;a[len].cc=cc;
    a[len].next=last[x];last[x]=len;

    len++;
    a[len].x=y;a[len].y=x;a[len].c=0;a[len].cc=-cc;
    a[len].next=last[y];last[y]=len;

}//建边

inline bool spfa(int s,int t)//反向跑最短路，求出距离标号 
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;i++)dis[i]=maxn;
    vis[t]=1;dis[t]=0;
    //首先SPFA我们维护距离标号的时候要倒着跑，这样可以维护出到终点的最短路径
    deque<int>p;p.push_back(t);
    //使用了SPFA的SLF优化
    while(!p.empty())
    {
        int now=p.front();p.pop_front();
        for(int k=last[now];k;k=a[k].next)
        {
            if(a[k^1].c>0)
            //首先c[k^1]是为什么呢，因为我们要保证正流，但是SPFA是倒着跑的，所以说我们要求c[k]的对应反向边是正的，这样保证走的方向是正确的
            {
                int y=a[k].y;
                if(dis[y]>dis[now]-a[k].cc)
                {
                    dis[y]=dis[now]-a[k].cc;
                    //因为已经是倒着的了，我们也可以很清楚明白地知道建边的时候反向边的边权是负的，所以减一下就对了（负负得正）
                    if(vis[y]==0)
                    {
                        vis[y]=1;
                        if(!p.empty() && dis[y]<dis[now])p.push_front(y);
                        else p.push_back(y);
                        //SLF优化
                    }
                }
            }
        } 
        vis[now]=0;//队头元素退队，设置为未访问 
    }
    if(dis[s]==maxn)return(false);
    else return(true);
    //判断起点终点是否连通
} 

int dfs(int x,int low)//这里就是进行増广了
{
    if(x==t){vis[t]=1;return low;} 
    int used=0,aa;vis[x]=1;//这边是不是和dinic很像啊
    for(int k=last[x];k; k=a[k].next)
    {
        int y=a[k].y;
        if(vis[y]==0 && a[k].c>0 && dis[x]-a[k].cc==dis[y])
        //这个条件就表示这条边可以进行増广
        {
            aa=dfs(y,min(a[k].c,low-used));
            if(aa>0)ans+=aa*a[k].cc,a[k].c-=aa,a[k^1].c+=aa,used+=aa;
            //累加答案，加流等操作都在这了
            if(used==low)break;
        }
    } 
    return used; 
}

inline int costflow()
{
    int flow=0;
    while(spfa(s,t))//判断起点终点是否连通，不连通说明满流，做完了退出
    {
        vis[t]=1;
        while(vis[t])
        {
            memset(vis,0,sizeof(vis));
            flow+=dfs(s,maxn); 
            //一直増广直到走不到为止（这样也可以省时间哦）
        }
    }
    return(flow);;//这里返回的是最大流，费用的答案在ans里
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&y,&c,&cc);
        add(x,y,c,cc);
    }
    printf("%d ",costflow());
    printf("%d",ans);
    return 0;
} 