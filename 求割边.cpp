const int N=110;
struct data
{
    int to,next;
} tu[N*N];
int head[N],low[N],dfn[N];
int ip;
int step;
void init()
{
    ip=0;
    step=1;///遍历的步数
    memset(head,-1,sizeof(head));
    memset(dfn, 0, sizeof(dfn));
}
void add(int u,int v)
{
    tu[ip].to=v,tu[ip].next=head[u],head[u]=ip++;
}
void tarjan(int u,int pre)
{
    dfn[u] = low[u] = step++;
    for(int i = head[u]; i!=-1 ; i=tu[i].next)
    {
        int to = tu[i].to;
        if(!dfn[to])
        {
            tarjan(to,u);
            low[u]=min(low[u],low[to]);
            if(low[to]>dfn[u])
                printf("%d--%d\n",u,to);///表示u到to是一条割边
        }
        else if(to!=pre)
            low[u]=min(low[u],dfn[to]);
    }
}