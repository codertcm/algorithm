#include <bits/stdc++.h>
using namespace std;

typedef long long int LL;
const int N = 4e2 + 10;
const int INF = 0x3f3f3f3f;

int maxData = 0x7f7f7f7f;
int capacity[N][N];
int flow[N];
int pre[N];
int n,m;
queue<int> myqueue;

int bfs(int src, int des){
	int i,j;
	while(!myqueue.empty())
		myqueue.pop();
	for(i=1;i<=n;i++){
		pre[i] = -1;
	}
	pre[src] = 0;
	flow[src] = maxData;
	myqueue.push(src);
	while(!myqueue.empty()){
		int index = myqueue.front();
		myqueue.pop();
		if(index == des)
			break;
		for(i=1;i<=n;i++){
			if(i!=src && capacity[index][i] > 0 && pre[i] == -1){
				pre[i] = index;
				flow[i] = min( capacity[index][i], flow[index] );
				myqueue.push(i);
			}
		}
	}
	if(pre[des] == -1)
		return -1;
	else
		return flow[des];
}

int maxFlow(int src, int des){

	int increasement = 0;
	int sumflow = 0;
	while( (increasement = bfs(src, des)) != -1){
		int k = des;
		while(k != src){
			int last = pre[k];
			capacity[last][k] -= increasement;
			capacity[k][last] += increasement;
			k = last;
 		}
 		sumflow += increasement;
	}
	return sumflow;
}

int main(int argc, char **argv)
{
	int i,j;
	int start, ed, ci, st, se;
	//freopen("testdata.in" , "r", stdin);
	//freopen("aaa.out","w", stdout );
    // O(n * m ^ 2);
	while(cin >> m >> n){
		memset(capacity, 0, sizeof(capacity));
		memset(flow, 0, sizeof(flow));
		for(i=0;i<m;i++){
			cin >> start >> ed >> ci;
			if(start == ed)
				continue;
			capacity[start][ed] += ci;
		}
		cout << maxFlow(1,n) << endl;	
	}
	return 0;
}
