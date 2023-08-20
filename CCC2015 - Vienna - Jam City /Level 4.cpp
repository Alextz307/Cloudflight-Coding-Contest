#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int kN = 1e3;
bitset<1 + kN> A[1 + kN], B[1 + kN];

struct road_t {
  int len, seg;

  void read() {
    fin >> len;
    fin.get();
    fin >> seg;
  }
};

struct car_t {
  int startRoad, startSeg;
  int endRoad, endSeg;
  int startTime;
  int index;
  int state, d;
  int curr;
  bool active, started;

  void read() {
    fin >> startRoad;
    startRoad -= 1;
    fin.get();
    fin >> startSeg;
    fin.get();
    fin >> endRoad;
    endRoad -= 1;
    fin.get();
    fin >> endSeg;
    fin.get();
    fin >> startTime;
    state = 0;
    active = true;
    started = false;
  }
};

int main() {
  int len, n;
  fin >> len >> n;
  vector<road_t> roads(n);
  for (auto &road : roads) {
    road.read();
  }
  int m, idx = 0;
  fin >> m;
  vector<car_t> cars(m);
  for (auto &car : cars) {
    car.read();
    car.index = idx++;
    if (roads[car.startRoad].seg < roads[car.endRoad].seg) {
      car.d = 1;
    } else {
      car.d = -1;
    }
  }
  int active = m, currTime = 1;
  vector<int> sol(m);
  while (active) {
    for (int i = 0; i <= n; ++i) {
      B[i].reset();
    }
    for (auto &car : cars) {
      if (car.started) {
        if (car.state == 0) {
          if (car.curr > 1) {
            if (!A[car.startRoad][car.curr - 1]) {
              car.curr -= 1;
            }
            B[car.startRoad][car.curr] = true;
          } else {
            int seg = roads[car.startRoad].seg;
            if (!A[n][seg - 1] && !A[n][seg]) {
              car.state = 1;
              car.curr = seg;
              B[n][seg] = true;
            } else {
              B[car.startRoad][1] = true;
            }
          }
        } else if (car.state == 1) {
          int seg = roads[car.endRoad].seg;
          if (car.curr != seg) {
            if (!A[n][car.curr + car.d]) {
              car.curr += car.d;
            }
            B[n][car.curr] = true;
          } else {
            if (!A[car.endRoad][1]) {
              car.state = 2;
              car.curr = 1;
              B[car.endRoad][1] = true;
            } else {
              B[n][seg] = true;
            }
          }
        } else if (car.active) {
          if (car.curr == car.endSeg) {
            sol[car.index] = currTime;
            car.active = false;
            active -= 1;
          } else {
            if (!A[car.endRoad][car.curr + 1]) {
              car.curr += 1;
            }
            B[car.endRoad][car.curr] = true;
          }
        }
      } else if (car.startTime <= currTime && !A[car.startRoad][car.startSeg + 1] && !A[car.startRoad][car.startSeg]) {
        car.started = true;
        car.curr = car.startSeg;
        B[car.startRoad][car.startSeg] = true;
      }
    }
    for (int i = 0; i <= n; ++i) {
      A[i] = B[i];
    }
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
