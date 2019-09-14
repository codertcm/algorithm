/*
共和国要组建委员会，现在有N个党派，每个党派中有两人，而且有且只有一人能参加委员会，但是现在不同党派间有些人有矛盾，因此这些人是不能同时属于委员会的。现在要你求出每个党派的派出人选，如果有多组解，则输出字典序最小的那组解。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 2e4 + 5;
vector<int> vt[maxn];
int n, m, mark[maxn], sta[maxn], top;
int dfs(int x)
{
    if(mark[x^1])
        return 0;
    if(mark[x])
        return 1;
    mark[x] = 1;
    sta[top++] = x;
    for(int i = 0; i < vt[x].size(); i++)
        if(!dfs(vt[x][i]))
            return 0;
    return 1;
}
int solve()
{
    for(int i = 0; i < 2*n; i += 2)
    {
        if(!mark[i] && !mark[i+1])
        {
            top = 0;
            if(!dfs(i))
            {
                while(top > 0)
                    mark[sta[--top]] = 0;
                if(!dfs(i+1))
                    return 0;
            }
        }
    }
    return 1;
}
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 0; i < maxn; i++) vt[i].clear();
        int x, y;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            --x, --y;  //从0开始， 这样 ^就是 奇数/偶数对应东西
            vt[x].push_back(y^1);
            vt[y].push_back(x^1);
        }
        memset(mark, 0, sizeof(mark));
        top = 0;
        if(!solve())
            puts("NIE");
        else
        {
            for(int i = 0; i < 2*n; i++)
                if(mark[i])
                    printf("%d\n", i+1);
        }
    }
    return 0;
}

