#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 1e3;
const int kM = 1e6;
char a[kN][kN], s[kM];
bitset<kN> vis[kN];

struct ghost {
  int x, y, len;
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

int main() {
  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> a[i];
  }
  int x, y;
  fin >> x >> y;
  x -= 1;
  y -= 1;
  int M;
  fin >> M >> s;
  int G;
  fin >> G;
  for (int i = 0; i < G; ++i) {
    fin >> g[i].x >> g[i].y >> g[i].len >> g[i].moves;
    g[i].x -= 1, g[i].y -= 1;
  }
  bool alive = true;
  int cntC = 0;
  for (int pas = 0; pas < M; ++pas) {
    tie(x, y) = newCell(x, y, s[pas]);
    if (x < 0 || y < 0 || x >= n || y >= n || a[x][y] == 'W') {
      alive = false;
      break;
    }
    for (int j = 0; j < G; ++j) {
      if (pas < g[j].len) {
        tie(g[j].x, g[j].y) = newCell(g[j].x, g[j].y, g[j].moves[pas]);
        if (g[j].x == x && g[j].y == y) {
          alive = false;
          break;
        }
      }
    }
    if (!alive) {
      break;
    }
    if (a[x][y] == 'C' && !vis[x][y]) {
      cntC += 1;
      vis[x][y] = true;
    }
  }
  fout << cntC << ' ';
  if (alive) {
    fout << "YES";
  } else {
    fout << "NO";
  }
  return 0;
}
