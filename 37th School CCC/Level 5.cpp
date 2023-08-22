#include <bits/stdc++.h>

using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

const int kN = 1e3;
const int di[] = {-1, -1, 0, 0, 1, 1}, dj[] = {-1, 1, -2, 2, -1, 1};
int have, istart, jstart;
bool flag;
vector<pair<int, int>> toBlock, blocked;
vector<string> a, sol;
bitset<1 + kN> block[1 + kN];

bool inside(const int &i, const int &j) {
  return 0 <= i && i < (int)a.size() && 0 <= j && j < (int)a[i].size();
}

bool reachable() {
  queue<pair<int, int>> q;

  vector<vector<bool>> vis(a.size(), vector<bool>(a[0].size()));

  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)a[i].size(); ++j) {
      if (a[i][j] == 'W') {
        q.emplace(i, j);
        vis[i][j] = true;
        break;
      }
    }
  }

  while (!q.empty()) {
    int i, j;
    tie(i, j) = q.front();
    q.pop();

    for (int k = 0; k < 6; ++k) {
      int iv = i + di[k], jv = j + dj[k];

      if (!inside(iv, jv)) {
        return true;
      }

      if (a[iv][jv] == 'O' && !block[iv][jv] && !vis[iv][jv]) {
        q.emplace(iv, jv);
        vis[iv][jv] = true;
      }
    }
  }

  return false;
}

void Back(int curr, int taken) {
  if (!flag) {
    return;
  }

  if (taken == have) {
    if (!reachable()) {
      flag = false;

      for (const auto &it : blocked) {
        sol[it.first][it.second] = 'X';
      }
    }
    return;
  }

  int rem = toBlock.size() - curr - 1;

  if (rem >= have - taken) {
    Back(curr + 1, taken);
  }

  blocked.emplace_back(toBlock[curr]);
  block[toBlock[curr].first][toBlock[curr].second] = true;
  
  Back(curr + 1, taken + 1);
  
  blocked.pop_back();
  block[toBlock[curr].first][toBlock[curr].second] = false;
}

void testCase() {
  string aux;
  getline(fin, aux);

  have = stoi(aux);

  string s;

  a.clear();

  while (getline(fin, s)) {
    if (s == "") {
      break;
    }
    a.push_back(s);
  }

  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)a[i].size(); ++j) {
      if (a[i][j] == 'W') {
        istart = i, jstart = j;
        break;
      }
    }
  }

  sol = a;

  int neigh = 0;

  for (int k = 0; k < 6; ++k) {
    int iv = istart + di[k], jv = jstart + dj[k];

    if (inside(iv, jv) && a[iv][jv] == 'O') {
      neigh += 1;
    }
  }

  if (neigh == have) {
    for (int k = 0; k < 6; ++k) {
      int iv = istart + di[k], jv = jstart + dj[k];

      if (inside(iv, jv) && a[iv][jv] == 'O') {
        sol[iv][jv] = 'X';
      }
    }

    for (const string &s : sol) {
      fout << s << '\n';
    }

    fout << '\n';

    return;
  }

  toBlock.clear();

  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)a[i].size(); ++j) {
      if (a[i][j] == 'O') {
        toBlock.emplace_back(i, j);
      }
    }
  }

  for (int rep = 0; rep < 69; ++rep) {
    random_shuffle(toBlock.begin(), toBlock.end());
  }

  flag = true;

  Back(0, 0);

  for (const string &s : sol) {
    fout << s << '\n';
  }

  fout << '\n';
}

int main() {

  int tests;
  fin >> tests;

  fout << tests << '\n' << '\n';

  string aux;
  getline(fin, aux);
  getline(fin, aux);

  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }

  fin.close();
  fout.close();

  return 0;
}
