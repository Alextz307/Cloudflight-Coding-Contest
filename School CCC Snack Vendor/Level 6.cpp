#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
const int di[] = {0, -1, -1, -1, 0, 1, 1, 1},
          dj[] = {1, 1, 0, -1, -1, -1, 0, 1};
 
int main() {
    string cell;
    fin >> cell;
    int rows = cell[0] - 'A' + 1, cols = cell[1] - '0';
    if(cell.size() > 2)
        cols = cols * 10 + (cell[2] - '0');
    fin >> cell;
    int i_start = cell[0] - 'A' + 1, j_start = cell[1] - '0';
    if(cell.size() > 2)
        j_start = j_start * 10 + (cell[2] - '0');
    fin >> cell;
    int i_stop = cell[0] - 'A' + 1, j_stop = cell[1] - '0';
    if(cell.size() > 2)
        j_stop = j_stop * 10 + (cell[2] - '0');
    queue < pair < int , int > > Q;
    Q.emplace(i_start, j_start);
    vector < vector < int > > a(rows + 1, vector < int >(cols + 1));
    a[i_start][j_start] = 1;
    auto inside = [&](int lin, int col) {
        return lin > 0 && col > 0 && lin <= rows && col <= cols;
    };
    int dir;
    fin >> dir;
    while(!Q.empty()) {
        int i = Q.front().first,
            j = Q.front().second;
        Q.pop();
        for(int k = 0; k < 8; ++k)
            if(k != dir) {
                int iv = i + di[k],
                    jv = j + dj[k];
                if(inside(iv, jv) && a[iv][jv] == 0) {
                    a[iv][jv] = a[i][j] + 1;
                    Q.emplace(iv, jv);
                }
            }
    }
    fout << a[i_stop][j_stop] - 1;
}
 
