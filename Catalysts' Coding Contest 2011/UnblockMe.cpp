// Full solution for levels 1-4 and partial solution for level 5
#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

struct interval {
  int x, y;

  //interval(int _x, int _y) : x(_x), y(_y) {}
};

struct block_t {
  int id;
  char dir;
  int x, y;
  int len;

  void read() {
    fin >> id >> dir >> x >> y >> len;
  }

  void moveBlock(const int &steps) {
    if (dir == 'h') {
      x += steps;
    } else {
      y += steps;
    }
  }

  bool overlap(const block_t &rhs) {
    if (dir == rhs.dir) {
      interval left, right;
      if (dir == 'h') {
        if (y != rhs.y) {
          return false;
        }
        left = {x, x + len - 1};
        right = {rhs.x, rhs.x + rhs.len - 1};
      } else {
        if (x != rhs.x) {
          return false;
        }
        left = {y, y + len - 1};
        right = {rhs.y, rhs.y + rhs.len - 1};
      }
      if (right.x < left.x) {
        swap(left, right);
      }
      if (right.x <= left.y) {
        return true;
      } else {
        return false;
      }
    } else {
      if (dir == 'h') {
        if (x <= rhs.x && rhs.x <= x + len - 1 && rhs.y <= y && y <= rhs.y + rhs.len - 1) {
          return true;
        } else {
          return false;
        }
      } else {
        if (rhs.x <= x && x <= rhs.x + rhs.len - 1 && y <= rhs.y && rhs.y <= y + len - 1) {
          return true;
        } else {
          return false;
        }
      }
    }
  }
};

vector<block_t> blocks;

bool isInside(const int &w, const int &h, const block_t &block) {
  if (block.x <= 0 || block.y <= 0
      || (block.dir == 'h' && block.x + block.len - 1 > w)
      || (block.dir == 'v' && block.y + block.len - 1 > h)) {
    return false;
  }
  return true;
}

bool validMove(const int &w, const int &h, const int &numBlocks, const int &id, const int &steps) {
  block_t block;
  for (const block_t &itr : blocks) {
    if (itr.id == id) {
      block = itr;
    }
  }
  block.moveBlock(steps);
  if (!isInside(w, h, block)) {
    return false;
  }
  for (const block_t &itr : blocks) {
    if (itr.id != block.id && block.overlap(itr)) {
      return false;
    }
  }
  return true;
}

int findDistance(const int &w) {
  int res = -1;
  for (const block_t &block : blocks) {
    if (block.id == 0) {
      res = w - (block.x + block.len - 1);
    }
  }
  assert(res >= 0);
  return res;
}

int distanceBetweenBlocks(const block_t &firstBlock, const block_t &secondBlock) {
  assert(firstBlock.dir == secondBlock.dir);
  interval left, right;
  if (firstBlock.dir == 'h') {
    left = {firstBlock.x, firstBlock.x + firstBlock.len - 1};
    right = {secondBlock.x, secondBlock.x + secondBlock.len - 1};
  } else {
    left = {firstBlock.y, firstBlock.y + firstBlock.len - 1};
    right = {secondBlock.y, secondBlock.y + secondBlock.len - 1};
  }
  if (right.x < left.x) {
    swap(left, right);
  }
  assert(left.y < right.x);
  return right.x - left.y - 1;
}

bool solveGame(const int &w, const int &h, const int &numBlocks, const int &id, const int &steps) {
  if (validMove(w, h, numBlocks, id, steps)) {
    for (block_t &block : blocks) {
      if (block.id == id) {
        block.moveBlock(steps);
      }
    }
    fout << id << ' ' << steps << ' ';
    return true;
  }
  block_t block;
  for (const block_t &itr : blocks) {
    if (itr.id == id) {
      block = itr;
    }
  }
  block_t aux = block;
  block.moveBlock(steps);
  if (!isInside(w, h, block)) {
    return false;
  }
  for (const block_t &itr : blocks) {
    if (block.id != itr.id && block.overlap(itr)) {
      if (block.dir == itr.dir) {
        int req = steps - distanceBetweenBlocks(aux, itr);
        if (!solveGame(w, h, numBlocks, itr.id, req)) {
          return false;
        }
      } else {
        int firstTry, secondTry;
        if (block.dir == 'h') {
          int down = itr.y, up = itr.y + itr.len - 1;
          firstTry = -(up - aux.y + 1);
          secondTry = aux.y - down + 1;
        } else {
          int left = itr.x, right = itr.x + itr.len - 1;
          firstTry = -(right - aux.x + 1);
          secondTry = aux.x - left + 1;
        }
        bool flag = solveGame(w, h, numBlocks, itr.id, firstTry);
        if (!flag) {
          flag = solveGame(w, h, numBlocks, itr.id, secondTry);
        }
        if (!flag) {
          return false;
        }
      }
    }
  }
  for (block_t &block : blocks) {
    if (block.id == id) {
      block.moveBlock(steps);
    }
  }
  fout << id << ' ' << steps << ' ';
  return true;
}

int main() {
  // Reading the <InitialGameSetup>
  int w, h;
  int numBlocks;
  fin >> w >> h >> numBlocks;
  blocks.resize(numBlocks);
  for (auto &block : blocks) {
    block.read();
  }

  /*

  Initial validMove function, declared locally, used for the first 4 levels.

  auto validMove = [&](const int &id, const int &steps) -> bool {
    block_t block;
    for (const block_t &itr : blocks) {
      if (itr.id == id) {
        block = itr;
      }
    }
    block.moveBlock(steps);
    if (!isInside(w, h, block)) {
      return false;
    }
    for (const block_t &itr : blocks) {
      if (itr.id != block.id && block.overlap(itr)) {
        return false;
      }
    }
    return true;
  };
  */

  /*
  ---Level 1---
  if (blocks[0].overlap(blocks[1])) {
    fout << "true\n";
  } else {
    fout << "false\n";
  }
  */

  /*
  ---Level 2---
  int id, steps;
  fin >> id >> steps;
  if (!validMove(id, steps)) {
    fout << "true\n";
  } else {
    fout << "false\n";
  }
  */

  /*
  ---Level 3---
  vector<int> standing;
  for (const block_t &block : blocks) {
    if (!validMove(block.id, -1) && !validMove(block.id, 1)) {
      standing.emplace_back(block.id);
    }
  }
  sort(standing.begin(), standing.end());
  for (const int &id : standing) {
    fout << id << ' ';
  }
  */

  /*
  ---Level 4---
  int listSize;
  fin >> listSize;
  int res = listSize;
  for (int i = 0; i < listSize && res == listSize; ++i) {
    int id, steps;
    fin >> id >> steps;
    if (!validMove(id, steps)) {
      res = i;
    } else {
      int index = -1;
      for (size_t j = 0; j < blocks.size() && index == -1; ++j) {
        if (blocks[j].id == id) {
          index = j;
        }
      }
      blocks[index].moveBlock(steps);
    }
  }
  fout << res << '\n';
  */

  // Level 5 - full game
  assert(solveGame(w, h, numBlocks, 0, findDistance(w)));

  fin.close();
  fout.close();
  return 0;
}
