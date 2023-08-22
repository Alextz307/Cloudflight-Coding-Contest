#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int INF = 1e9;
const int kSigma = 256;
int ids;
map<char, int> mp;
map<int, char> rev;
vector<int> pos, freq;

bool isLetter(char c) {
  return 'A' <= c && c <= 'Z';
}

int id(char c) {
  if (mp.find(c) != mp.end()) {
    return mp[c];
  }
  ids += 1;
  mp[c] = ids;
  rev[ids] = c;
  return ids;
}

vector<char> solve(vector<string> d, bool flag) {
  int n = d.size();
  ids = 0;
  mp.clear();
  rev.clear();
  pos = vector<int>(kSigma, INF);
  freq = vector<int>(kSigma, 0);
  for (int i = 0; i < n; ++i) {
    if (pos[id(d[i][0])] == INF) {
      pos[id(d[i][0])] = i;
    }
    for (char c : d[i]) {
      freq[id(c)] += 1;
    }
  }
  vector<pair<int, int>> a;
  for (int i = 0; i < kSigma; ++i) {
    if (pos[i] != INF) {
      a.emplace_back(freq[i], i);
    }
  }
  sort(a.rbegin(), a.rend());
  vector<char> sol;
  for (auto it : a) {
    sol.emplace_back(rev[it.second]);
  }
  return sol;
}

int main() {
  string s;
  getline(fin, s);
  string t = "";
  vector<string> d1;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] == ' ') {
      if (!t.empty()) {
        d1.push_back(t);
      }
      t = "";
    } else {
      t += s[i];
    }
  }
  if (!t.empty()) {
    d1.push_back(t);
  }
  int n;
  fin >> n;
  vector<string> d2(n);
  for (string &s : d2) {
    fin >> s;
  }
  vector<char> s1 = solve(d1, false), s2 = solve(d2, true);
  vector<tuple<int, char, char>> sol;
  for (int i = 0; i < (int)s1.size(); ++i) {
    sol.emplace_back(pos[mp[s1[i]]], s1[i], s2[i]);
  }
  sort(sol.begin(), sol.end());
  for (auto it : sol) {
    fout << get<1>(it) << ' ' << get<2>(it) << '\n';
  }
  return 0;
}
