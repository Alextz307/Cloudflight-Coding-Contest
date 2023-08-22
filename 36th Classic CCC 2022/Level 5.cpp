#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 50;
const int kM = 1e5;
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
const char dirs[] = {'U', 'R', 'D', 'L'};
int n, xPac, yPac;
char a[1 + kN][1 + kN];
bitset<kN> ghosts[1 + kM][1 + kN], vis[1 + kM][1 + kN];

struct ghost {
  int x, y, len, ptr, add;
  string moves;
} g[1 + kM];

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

void print(int t, int x, int y) {
  if (t == 0) {
    return;
  }
  for (int k = 0; k < 4; ++k) {
    int iv = x + di[k], jv = y + dj[k];
    if (inside(iv, jv) && vis[t - 1][iv][jv]) {
      print(t - 1, iv, jv);
      fout << rev(dirs[k]);
      return;
    }
  }
}

int main() {
  fin >> n;
  int xC = -1, yC = -1;
  for (int i = 0; i < n; ++i) {
    fin >> a[i];
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 'C') {
        xC = i, yC = j;
      }
    }
  }
  int x, y;
  fin >> x >> y;
  x -= 1;
  y -= 1;
  xPac = x, yPac = y;
  int G;
  fin >> G;
  for (int i = 0; i < G; ++i) {
    fin >> g[i].x >> g[i].y >> g[i].len >> g[i].moves;
    g[i].x -= 1, g[i].y -= 1;
    g[i].ptr = 0;
    g[i].add = 1;
  }
  for (int pas = 1; pas <= kM; ++pas) {
    for (int j = 0; j < G; ++j) {
      if (g[j].ptr == g[j].len) {
        g[j].ptr = g[j].len - 1;
        g[j].add = -1;
      }
      if (g[j].ptr == -1) {
        g[j].ptr = 0;
        g[j].add = 1;
      }
      char c = g[j].moves[g[j].ptr];
      if (g[j].add == -1) {
        c = rev(c);
      }
      tie(g[j].x, g[j].y) = newCell(g[j].x, g[j].y, c);
      ghosts[pas][g[j].x][g[j].y] = true;
      g[j].ptr += g[j].add;
    }
  }
  vis[0][x][y] = true;
  int tmax = -1;
  for (int t = 1; t <= kM; ++t) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (!ghosts[t][i][j] && a[i][j] != 'W') {
          for (int k = 0; k < 4; ++k) {
            int iv = i + di[k], jv = j + dj[k];
            if (inside(iv, jv) && vis[t - 1][iv][jv]) {
              vis[t][i][j] = true;
              break;
            }
          }
        }
      }
    }
    if (vis[t][xC][yC]) {
      tmax = t;
      break;
    }
  }
  print(tmax, xC, yC);
  return 0;
}

