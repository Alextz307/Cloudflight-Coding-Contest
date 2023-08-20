#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 1e3;
bitset<1 + kN> A, B;

struct car_t {
  int st, en, startTime, endTime, curr, index;
  bool active, started;

  void read() {
    fin >> st;
    fin.get();
    fin >> en;
    fin.get();
    fin >> endTime;
    startTime = 1;
    curr = st;
    active = true;
    started = false;
  }
};

int main() {
  int n, m;
  fin >> n >> m;
  int idx = 0;
  vector<car_t> cars(m);
  for (auto &car : cars) {
    car.read();
    car.index = idx++;
    car.startTime += rand() % 20;
  }
  int active = m, currTime = 1;
  vector<int> sol(m);
  while (active) {
    B.reset();
    for (auto &car : cars) {
      if (car.started) {
        if (car.active && !A[car.curr + 1]) {
          car.curr += 1;
          B[car.curr] = true;
          if (car.curr == car.en) {
            sol[car.index] = car.endTime - (currTime + 1);
            car.active = false;
            active -= 1;
          }
        } else if (car.active) {
          B[car.curr] = true;
        }
      } else if (currTime >= car.startTime && !A[car.st - 1] && !A[car.st]) {
        car.started = true;
        B[car.st] = true;
      }
    }
    A = B;
    currTime += 1;
  }
  for (int i = 0; i < m; ++i) {
    fout << sol[i];
    if (i < m - 1) {
      fout << ',';
    }
  }
  fin.close();
  fout.close();
  return 0;
}
