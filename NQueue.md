# NQueue problem

+ 位运算实现

```c++

#include <bits/stdc++.h>
using namespace std;
 
int ans;
int lim;
 
void NQueue(int row, int ld, int rd){
    int pos, p;
    if(row ^ lim){
        pos = lim & (~(row | ld | rd));
        while(pos){
            p = pos & (~pos + 1);
            pos ^= p;
            NQueue(row | p, (ld | p) << 1, (rd | p) >> 1);
        }
    } else {
        ans++;
    }
}
 
int main()
{
    int n;
    while(scanf("%d", &n) != EOF && n){
        ans = 0;
        lim = (1 << n) - 1;
        NQueue(0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}

```

