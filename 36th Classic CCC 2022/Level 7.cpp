#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 50;
const int kL = 100;
const int INF = 1e9;
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
const char dirs[] = {'U', 'R', 'D', 'L'};
const char revD[] = {'D', 'L', 'U', 'R'};
int n, d[kN][kN], gId[kN][kN], C[kN][kN], dp[1 + kL][kN][kN];
string a[kN];
char lastDir[kN][kN];
pair<int, int> lastCell[kN][kN];
bitset<kN> ghosts[1 + kL][kN];

struct ghost {
  int x, y, len, ptr, add;
  string moves;
} g[kN];

pair<int, int> newCell(int x, int y, char d) {
  if (d == 'L') {
    y -= 1;
  } else if (d == 'R') {
    y += 1;
  } else if (d == 'U') {
    x -= 1;
  } else {
    x += 1;
  }
  return {x, y};
}

bool inside(int i, int j) {
  return 0 <= min(i, j) && max(i, j) < n;
}

char rev(char c) {
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

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

int main() {
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> a[i];
  }
  int xPac, yPac;
  fin >> xPac >> yPac;
  xPac -= 1, yPac -= 1;
  int G;
  fin >> G;
  for (int i = 0; i < G; ++i) {
    fin >> g[i].x >> g[i].y;
    g[i].x -= 1, g[i].y -= 1;
    g[i].ptr = 0;
    g[i].add = 1;
    g[i].moves = "";
    gId[g[i].x][g[i].y] = i;
  }
  int numCoins;
  fin >> numCoins;
  for (int i = 0; i < numCoins; ++i) {
    int xC, yC, w;
    fin >> xC >> yC >> w;
    xC -= 1, yC -= 1;
    C[xC][yC] += w;
  }
  int L;
  fin >> L;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      d[i][j] = INF;
    }
  }
  d[xPac][yPac] = 0;
  queue<pair<int, int>> q;
  q.emplace(xPac, yPac);
  while (!q.empty()) {
    int i, j;
    tie(i, j) = q.front();
    q.pop();
    for (int k = 0; k < 4; ++k) {
      int iv = i + di[k], jv = j + dj[k];
      if (inside(iv, jv) && a[iv][jv] != 'W') {
        if (d[iv][jv] > d[i][j] + 1) {
          d[iv][jv] = d[i][j] + 1;
          lastDir[iv][jv] = revD[k];
          lastCell[iv][jv] = {i, j};
          q.emplace(iv, jv);
        } else if (d[iv][jv] == d[i][j] + 1 && revD[k] < lastDir[iv][jv]) {
          lastDir[iv][jv] = revD[k];
          lastCell[iv][jv] = {i, j};
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 'G') {
        int id = gId[i][j], steps = d[i][j], x = i, y = j;
        for (int rep = 0; rep < steps; ++rep) {
          g[id].moves += lastDir[x][y];
          tie(x, y) = lastCell[x][y];
        }
        g[id].len = g[id].moves.size();
      }
    }
  }
  for (int pas = 1; pas <= L; ++pas) {
    for (int i = 0; i < G; ++i) {
      if (g[i].ptr == g[i].len) {
        g[i].ptr = g[i].len - 1;
        g[i].add = -1;
      }
      if (g[i].ptr == -1) {
        g[i].ptr = 0;
        g[i].add = 1;
      }
      char c = g[i].moves[g[i].ptr];
      if (g[i].add == -1) {
        c = rev(c);
      }
      tie(g[i].x, g[i].y) = newCell(g[i].x, g[i].y, c);
      ghosts[pas][g[i].x][g[i].y] = true;
      g[i].ptr += g[i].add;
    }
  }
  for (int t = 0; t <= L; ++t) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[t][i][j] = -INF;
      }
    }
  }
  dp[0][xPac][yPac] = 0;
  for (int t = 1; t <= L; ++t) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (a[i][j] != 'W' && !ghosts[t][i][j]) {
          for (int k = 0; k < 4; ++k) {
            int iv = i + di[k], jv = j + dj[k];
            if (inside(iv, jv)) {
              maxSelf(dp[t][i][j], dp[t - 1][iv][jv] + C[i][j]);
            }
          }
        }
      }
    }
  }
  int res = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      maxSelf(res, dp[L][i][j]);
    }
  }
  fout << res << '\n';
  return 0;
}
