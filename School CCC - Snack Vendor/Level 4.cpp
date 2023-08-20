#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    string cell;
    fin >> cell;
    int rows = cell[0] - 'A' + 1, cols = cell[1] - '0';
    if(cell.size() > 2)
        cols = cols * 10 + (cell[2] - '0');
    vector < vector < int > > grid(rows, vector < int >(cols));
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            fin >> grid[i][j];
    vector < vector < int > > stock(rows, vector < int >(cols));
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            fin >> stock[i][j];
    int T, ans = 0;
    fin >> T;
    while(T--) {
        fin >> cell;
        int row = cell[0] - 'A', col = cell[1] - '0' - 1;
        if(cell.size() > 2) {
            ++col;
            col = col * 10 + (cell[2] - '0' - 1);
        }
        int price = grid[row][col];
        if(stock[row][col] > 0) {
            ans += price;
            --stock[row][col];
        }
    }
    fout << ans;
}
 
