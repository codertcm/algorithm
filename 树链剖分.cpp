
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=1e5+10;
struct edge{
    int next,to;
}e[2*maxn];
struct Node{
    int sum,lazy,l,r,ls,rs;
}node[2*maxn];
int rt,n,m,r,p,a[maxn],cnt,head[maxn],f[maxn],d[maxn],size[maxn],son[maxn],rk[maxn],top[maxn],id[maxn];
int mod(int a,int b)
{
    return (a+b)%p;
}
void add_edge(int x,int y)
{
    e[++cnt].next=head[x];
    e[cnt].to=y;
    head[x]=cnt;
}
void dfs1(int u,int fa,int depth)
{
    f[u]=fa;
    d[u]=depth;
    size[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa)
            continue;
        dfs1(v,u,depth+1);
        size[u]+=size[v];
        if(size[v]>size[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int t)
{
    top[u]=t;
    id[u]=++cnt;
    rk[cnt]=u;
    if(!son[u])
        return;
    dfs2(son[u],t);
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v!=son[u]&&v!=f[u])
            dfs2(v,v);
    }
}
void pushup(int x)
{
    node[x].sum=(node[node[x].ls].sum+node[node[x].rs].sum+node[x].lazy*(node[x].r-node[x].l+1))%p;
}
void build(int li,int ri,int cur)
{
    if(li==ri)
    {
        node[cur].l=node[cur].r=li;
        node[cur].sum=a[rk[li]];
        return;
    }
    int mid=(li+ri)>>1;
    node[cur].ls=cnt++;
    node[cur].rs=cnt++;
    build(li,mid,node[cur].ls);
    build(mid+1,ri,node[cur].rs);
    node[cur].l=node[node[cur].ls].l;
    node[cur].r=node[node[cur].rs].r;
    pushup(cur);
}
void update(int li,int ri,int c,int cur)
{
    if(li<=node[cur].l&&node[cur].r<=ri)
    {
        node[cur].sum=mod(node[cur].sum,c*(node[cur].r-node[cur].l+1));
        node[cur].lazy=mod(node[cur].lazy,c);
        return;
    }
    int mid=(node[cur].l+node[cur].r)>>1;
    if(li<=mid)
        update(li,ri,c,node[cur].ls);
    if(mid<ri)
        update(li,ri,c,node[cur].rs);
    pushup(cur);
}
int query(int li,int ri,int cur)
{
    if(li<=node[cur].l&&node[cur].r<=ri)
        return node[cur].sum;
    int tot=node[cur].lazy*(min(node[cur].r,ri)-max(node[cur].l,li)+1)%p;
    int mid=(node[cur].l+node[cur].r)>>1;
    if(li<=mid)
        tot=mod(tot,query(li,ri,node[cur].ls));
    if(mid<ri)
        tot=mod(tot,query(li,ri,node[cur].rs));
    return tot%p;
}
int sum(int x,int y)
{
    int ans=0;
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(d[fx]>=d[fy])
        {
            ans=mod(ans,query(id[fx],id[x],rt));
            x=f[fx],fx=top[x];
        }
        else
        {
            ans=mod(ans,query(id[fy],id[y],rt));
            y=f[fy],fy=top[y];
        }
    }
    if(id[x]<=id[y])
        ans=mod(ans,query(id[x],id[y],rt));
    else
        ans=mod(ans,query(id[y],id[x],rt));
    return ans%p;
}
void updates(int x,int y,int c)
{
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(d[fx]>=d[fy])
        {
            update(id[fx],id[x],c,rt);
            x=f[fx],fx=top[x];
        }
        else
        {
            update(id[fy],id[y],c,rt);
            y=f[fy],fy=top[y];
        }
    }
    if(id[x]<=id[y])
        update(id[x],id[y],c,rt);
    else
        update(id[y],id[x],c,rt);
}
signed main()
{
    scanf("%d%d%d%d",&n,&m,&r,&p);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    cnt=0;
    dfs1(r,0,1);
    dfs2(r,r);
    cnt=0;
    rt=cnt++;
    build(1,n,rt);
    for(int i=1;i<=m;i++)
    {
        int op,x,y,z;
        scanf("%lld",&op);
        if(op==1)
        {
            scanf("%lld%lld%lld",&x,&y,&z);
            updates(x,y,z);
        }
        else if(op==2)
        {
            scanf("%lld%lld",&x,&y);
            printf("%lld\n",sum(x,y));
        }
        else if(op==3)
        {
            scanf("%lld%lld",&x,&z );
            //子树也有连续区间的性质
            update(id[x],id[x]+size[x]-1,z,rt);
        }
        else if(op==4)
        {
            scanf("%lld",&x);
            printf("%lld\n",query(id[x],id[x]+size[x]-1,rt));
        }
    }
    return 0;
}


