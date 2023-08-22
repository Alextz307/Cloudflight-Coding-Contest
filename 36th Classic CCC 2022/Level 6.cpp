#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 80;
const int kG = 30;
const int kC = 10;
const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
const char dirs[] = {'U', 'R', 'D', 'L'};
int n, C[kN][kN];
string a[kN];
bitset<kN> ghosts[1 + 2 * kG][kN];

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

int encode(int x, int y, int z, int t) {
  return (((((x << 7) | y) << 10) | z) << 7) | t;
}

bool isBetter(const string &s, const string &t) {
  if (s.size() > t.size()) {
    return false;
  }
  if (s.size() < t.size()) {
    return true;
  }
  return s < t;
}

int main() {
  fin >> n;
  int cntC = 0;
  for (int i = 0; i < n; ++i) {
    fin >> a[i];
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 'C') {
        C[i][j] = cntC;
        cntC += 1;
      }
    }
  }
  int x, y;
  fin >> x >> y;
  x -= 1;
  y -= 1;
  int G;
  fin >> G;
  for (int i = 0; i < G; ++i) {
    fin >> g[i].x >> g[i].y >> g[i].len >> g[i].moves;
    g[i].x -= 1, g[i].y -= 1;
    g[i].ptr = 0;
    g[i].add = 1;
  }
  int L = g[0].len;
  for (int pas = 1; pas <= 2 * L; ++pas) {
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
  int MAX;
  fin >> MAX;
  string sol;
  unordered_map<int, string> dp;
  dp[encode(x, y, 0, 0)] = "";
  queue<tuple<short, short, short, short>> q;
  q.emplace(x, y, 0, 0);
  while (!q.empty()) {
    int i, j, mask, t;
    tie(i, j, mask, t) = q.front();
    q.pop();
    string path = dp[encode(i, j, mask, t)];
    if (mask == (1 << cntC) - 1) {
      if (sol.empty()) {
        sol = path;
      } else if (isBetter(path, sol)) {
        sol = path;
      }
      continue;
    }
    for (int k = 0; k < 4; ++k) {
      int iv = i + di[k], jv = j + dj[k], newT = t + 1;
      if (newT == 2 * L + 1) {
        newT = 1;
      }
      if (inside(iv, jv) && a[iv][jv] != 'W' && !ghosts[newT][iv][jv]) {
        path.push_back(dirs[k]);
        int newMask = mask;
        if (a[iv][jv] == 'C') {
          newMask |= 1 << C[iv][jv];
        }
        int newH = encode(iv, jv, newMask, newT);
        if (dp.find(newH) == dp.end() || isBetter(path, dp[newH])) {
          dp[newH] = path;
          q.emplace(iv, jv, newMask, newT);
        }
        path.pop_back();
      }
    }
  }
  fout << sol << '\n';
  return 0;
}
