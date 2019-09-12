const int N=110;
struct data
{
    int to,next;
} tu[N*N];
int head[N],low[N],dfn[N];///dfn[]记录某个点被访问到的次数，low[]记录某个点或其子树回边的最小步数的点
bool cut[N];///表示该点是否为割点
int ip;
int step,rt_son;
void init()
{
    ip=0;
    step=1;///遍历的步数
    rt_son=0;///根的孩子数量
    memset(head,-1,sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
}
void add(int u,int v)
{
    tu[ip].to=v,tu[ip].next=head[u],head[u]=ip++;
}
void tarjan(int u)
{
    dfn[u] = low[u] = step++;
    for(int i = head[u]; i!=-1 ; i=tu[i].next)
    {
        int to = tu[i].to;
        if(!dfn[to])///表示未被访问的点
        {
            tarjan(to);
            if(u==1)rt_son++;///必须写在里面，因为输入的原因可能会有重边
            else
            {
                low[u]=min(low[u],low[to]);
                if(low[to]>=dfn[u])
                    cut[u]=1;
            }
        }
        else
            low[u]=min(low[u],dfn[to]);
    }
}
if(rt_son>1)cut[1]=1;  ///表示1为割点