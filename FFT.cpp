#include <bits/stdc++.h>
using namespace std;
#define pi acos (-1)
#define maxn 200010

struct plex {       // 定义复数类
    double x, y;
    plex (double _x = 0.0, double _y = 0.0) : x (_x), y (_y) {}
    plex operator + (const plex &a) const {
        return plex (x + a.x, y + a.y);
    }
    plex operator - (const plex &a) const {
        return plex (x - a.x, y - a.y);
    }
    plex operator * (const plex &a) const {
        return plex (x * a.x - y * a.y, x * a.y + y * a.x);
    }
};

void change (plex *y, int len) {
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void fft(plex y[], int len, int on) {   // FFT过程，on==1时，将系数表达转换成点值表达，on==-1时，将点值表达转换成系数表达
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        plex wn(cos(-on * 2 * pi / h), sin(-on * 2 * pi / h));
        for(int j = 0; j < len; j += h) {
            plex w(1, 0);
            for(int k = j; k < j + h / 2; k++) {
                plex u = y[k];
                plex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1) {
        for(int i = 0; i < len; i++)
            y[i].x /= len;
    }
}

char a[maxn], b[maxn];
plex x1[maxn], x2[maxn];
int ans[maxn];

int main () {
    while (scanf ("%s%s", a, b) == 2) {
        int len = 2, l1 = strlen(a), l2 = strlen(b);
        while (len < l1 * 2 || len < l2 * 2) len *= 2;      // 扩充多项式长度到2^n
        for (int i = 0; i < l1; i++)
            x1[i] = plex(a[l1 - i - 1] - '0', 0);           // 补0
        for (int i = l1; i < len; i++)
            x1[i] = plex(0, 0);
        for (int i = 0; i < l2; i++)
            x2[i] = plex(b[l2 - i - 1] - '0', 0);
        for (int i = l2; i < len; i++)
            x2[i] = plex(0, 0);
        fft(x1, len, 1);                // DFT过程
        fft(x2, len, 1);
        for (int i = 0; i < len; i++)   // 点值形式下相乘
            x1[i] = x1[i] * x2[i];
        fft(x1, len, -1);               // 逆DFT过程
        for (int i = 0; i < len; i++) ans[i] = (int)(x1[i].x + 0.5);
        for (int i = 0; i < len; i++) {    // 需要进位
            if (ans[i] >= 10) {
                ans[i + 1] += ans[i] / 10;
                ans[i] %= 10;
            }
        }
        len = l1 + l2 - 1;
        while (ans[len] <= 0 && len > 0) len--;
        for (int i = len; i >= 0; i--)
            printf("%d", ans[i]);
        puts("");
    }
    return 0;
}

// hdu 1402