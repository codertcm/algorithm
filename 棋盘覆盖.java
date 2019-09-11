

package com.company;

import java.util.Scanner;

public class Main {
    final static int N = 110;
    public static int cnt;
    public static int [][] mp;

    public static void chessBoard(int x, int y, int sz, int dr, int dc){
        if(sz == 1)
            return;
        sz/=2;
        int t = cnt++;
        if(dr < x+sz && dc < y+sz){
            chessBoard(x, y, sz, dr, dc);
        } else {
            mp[x + sz - 1][y + sz - 1] = t;
            chessBoard(x, y, sz, x + sz - 1, y + sz - 1);
        }
        if(dr < x+sz && dc >= y+sz){
            chessBoard(x, y+sz, sz, dr, dc);
        } else {
            mp[x+sz-1][y+sz] = t;
            chessBoard(x, y+sz, sz, x+sz-1, y+sz);
        }
        if(dr >= x+sz && dc < y+sz){
            chessBoard(x+sz, y, sz, dr, dc);
        } else {
            mp[x+sz][y+sz-1] = t;
            chessBoard(x+sz, y, sz, x+sz, y+sz-1);
        }
        if(dr >= x+sz && dc >= y+sz){
            chessBoard(x+sz, y+sz, sz, dr, dc);
        } else {
            mp[x + sz][y + sz] = t;
            chessBoard(x + sz, y + sz, sz, x + sz, y + sz);
        }
    }

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int n,dr,dc;
        n = cin.nextInt();
        dr = cin.nextInt();
        dc = cin.nextInt();
        mp = new int [N][N];
        int [] fac = new int [N];
        fac[0] = 1;
        for(int i=1;i<=6;i++){
            fac[i] =fac[i-1] * 2;
        }
        mp[dr][dc] = cnt++;
        chessBoard(0, 0, fac[n], dr, dc);
        for(int i=0;i<fac[n];i++){
            for(int j=0;j<fac[n];j++){
                System.out.print(mp[i][j] + " ");
            }
            System.out.println();
        }
    }
}

