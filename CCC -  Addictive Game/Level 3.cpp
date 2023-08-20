#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int N, M, points;
vector < vector < int > > grid, a;
 
int main() {
    fin >> N >> M >> points;
    grid = vector < vector < int > >(N + 1, vector < int >(M + 1));
    for(int i = 0; i < points; ++i) {
        int index, colour;
        fin >> index >> colour;
        int lin = index / M + 1;
        if(index % M == 0)
            --lin;
        int col = index % M;
        if(col == 0)
            col = M;
        grid[lin][col] = colour;
    }
    int n_paths;
    fin >> n_paths;
    for(int itr = 0; itr < n_paths; ++itr) {
        int colour, index, lg;
        fin >> colour >> index >> lg;
        int lin = index / M + 1;
        if(index % M == 0)
            --lin;
        int col = index % M;
        if(col == 0)
            col = M;
        a = grid;
        a[lin][col] = -1;
        int ok = 1, cnt = 0, ans = 0;
        bool reached = false;
        for(int i = 0; i < lg; ++i) {
            char dir;
            fin >> dir;
            fin.get();
            if(ok == 1) {
                ++cnt;
                if(dir == 'N')
                    --lin;
                else
                    if(dir == 'E')
                        ++col;
                else
                    if(dir == 'S')
                        ++lin;
                else
                    --col;
                if(lin < 1 || col < 1 || lin > N || col > M) {
                    ok = -1;
                    ans = cnt;
                }
                if(a[lin][col] != 0) {
                    if(a[lin][col] == colour) {
                        if(i == lg - 1) {
                            reached = true;
                            ans = cnt;
                        }
                    }
                    else {
                        ok = -1;
                        ans = (lin - 1) * M + col;
                    }
                }
                a[lin][col] = -1;
            }
        }
        if(!reached) {
            ok = -1;
            ans = cnt;
        }
        fout << ok << ' ' << ans;
    }
}
 
