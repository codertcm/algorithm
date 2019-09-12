//#include <bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

typedef long long int LL;
const int N = 1e5 + 10;
const int M = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int cnt,n,m,s,t,u,v,w;

struct Edge {
    int u,v,w,_next;
};

Edge e[M];
int head[N];
int dep[N]; // 表示节点深度
int cur[N]; // 当前弧优化

void add(int u, int v, int w){
    e[cnt].w = w;
    e[cnt].v = v;
    e[cnt].u = u;
    e[cnt]._next = head[u];
    head[u] = cnt++;
}

// 源点: 只有流出去的点
// 汇点: 只有流进来的点
// 流量: 一条边上流过的流量
// 容量: 一条边上可供流过的最大流量
// 残量: 一条边上的容量

int bfs(){
    memset(dep, -1, sizeof(dep));
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    while(!q.empty()){
        int u = q.front();  // 正常BFS
        q.pop();
        for(int i=head[u]; ~i; i = e[i]._next){
            int v = e[i].v;
            if(dep[v] == -1 && e[i].w != 0){
                dep[v] = dep[u] + 1; // 分层，即该点在第几层里
                if(v == t) return 1; // 搜到t的边就可以停止了
                q.push(v);
            }
        }
    }
    if(dep[t] != -1) return 1; // t被联通了
    else return 0; // 汇点深度不在， 说明不存在分层图，无增广路
}

int dfs(int u, int f){ // 当前到达的点和当前到达的流量
    if(u == t || f == 0)      // 当前到达了汇点，返回当前流量
        return f;
    for(int i=cur[u]; ~i; i=e[i]._next){
        cur[u] = i; // 去掉榨干的边
        int v = e[i].v;
        if(dep[v] == dep[u]+1 && e[i].w != 0){ // 是分层图 && 残量不为零 (还可以再分配流量)
            // 每一次由u推出v的深度必须是u的深度+1
            int ts = dfs(v, min(e[i].w, f)); // 向下增广
            if(ts > 0){  // 增广成功
                e[i].w -= ts; // 正边增
                e[i^1].w += ts; // 反边加
                return ts; // 返回这次增广的值
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    while(cin >> m >> n){
        s = 1;
        t = n;
        cnt = 0;
        memset(head, -1, sizeof(head));
        for(int i=1;i<=m;i++){
            cin >> u >> v >>w;
            add(u,v,w);
            add(v,u,0);
        }
        int ans = 0;

        while(bfs()){  // 直到不存在增广路为止
            for(int i=0;i<N;i++){
                cur[i] = head[i]; // 恢复原值
            }
            ans += dfs(s, INF); // INF 使得dfs增广值为e[i].w, "灌满"第一条路
        }
        cout << ans << endl;
    }
	return 0;
}
