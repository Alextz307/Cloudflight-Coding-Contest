#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 2e3;
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
const char dirs[] = {'U', 'R', 'D', 'L'};
char a[kN][kN], lastDir[kN][kN];
pair<int, int> last[kN][kN];
bitset<kN> vis[kN], mark[kN];

char rev(const char &c) {
  if (c == 'U') {
    return 'D';
  }
  if (c == 'D') {
    return 'U';
  }
  if (c == 'L') {
    return 'R';
  }
  return 'L';
}

int main() {
  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> a[i];
  }
  int x, y, len;
  fin >> x >> y >> len;
  x -= 1;
  y -= 1;
  vis[x][y] = true;
  queue<pair<int, int>> q;
  q.emplace(x, y);
  while (!q.empty()) {
    int i, j;
    tie(i, j) = q.front();
    q.pop();
    for (int k = 0; k < 4; ++k) {
      int iv = i + di[k], jv = j + dj[k];
      if (iv >= 0 && jv >= 0 && iv < n && jv < n && a[iv][jv] != 'W' && a[iv][jv] != 'G' && !vis[iv][jv]) {
        last[iv][jv] = {i, j};
        vis[iv][jv] = true;
        lastDir[iv][jv] = dirs[k];
        q.emplace(iv, jv);
      }
    }
  }
  string sol = "";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 'C' && !mark[i][j]) {
        assert(vis[i][j]);
        int X = i, Y = j;
        string t = "";
        while (X != x || Y != y) {
          mark[X][Y] = true;
          t += lastDir[X][Y];
          tie(X, Y) = last[X][Y];
        }
        mark[X][Y] = true;
        reverse(t.begin(), t.end());
        sol += t;
        reverse(t.begin(), t.end());
        for (char c : t) {
          sol += rev(c);
        }
      }
    }
  }
  fout << sol;
  return 0;
}
