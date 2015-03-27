#include "SudukuStructure.h"

SudukuStructure::SudukuStructure() {
  clear();
}

SudukuStructure::SudukuStructure(std::string str) {
  assert(str.size() == 81);
  clear();
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      setValue(i, j, str[i * 9 + j] - '0');
    }
  }
}

void SudukuStructure::clear() {
  memset(board, 0, sizeof(board));
  memset(hash, 0, sizeof(hash));
  seq.clear();
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      count[i][j] = 9;
      seq.insert(std::make_pair(9, i * 9 + j));
    }
  }
}

int SudukuStructure::emptyEntity() {
  return seq.size();
}

int SudukuStructure::valueAt(int x, int y) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9);
  return board[x][y];
}

void SudukuStructure::setValue(int x, int y, int z) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9 && 0 <= z && z <= 9);
  if (board[x][y] == z) {
    return;
  }
  if (board[x][y] != 0) {
    setStatus(x, y, board[x][y], 0);
    board[x][y] = 0;
    addEmptyEntity(x, y);
  }
  if (z != 0) {
    setStatus(x, y, z, 1);
    board[x][y] = z;
    removeEmptyEntity(x, y);
  }
  flushSeq(x, y);
}

void SudukuStructure::setStatus(int x, int y, int z, int flag) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9 && 0 <= z && z <= 9);
  assert(flag == 0 || flag == 1);

  //horizon
  assert(((hash[x] >> (z - 1)) & 1) != flag);
  hash[x] ^= (1 << (z - 1));

  //vertical
  assert(((hash[9 + y] >> (z - 1)) & 1) != flag);
  hash[9 + y] ^= (1 << (z - 1));

  //box
  int t = (x / 3) * 3 + (y / 3);
  assert(((hash[18 + t] >> (z - 1)) & 1) != flag);
  hash[18 + t] ^= (1 << (z - 1));
}

void SudukuStructure::removeEmptyEntity(int x, int y) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9);
  std::set< std::pair<int, int> >::iterator itr;
  itr = seq.find(std::make_pair(count[x][y], x * 9 + y));
  assert(itr != seq.end());
  seq.erase(itr);
}

void SudukuStructure::addEmptyEntity(int x, int y) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9);
  seq.insert(std::make_pair(count[x][y], x * 9 + y));
}

void SudukuStructure::flushSeq(int x, int y) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9);
  for (int i = 0; i < 9; i++) {
    flushCount(i, y);
    flushCount(x, i);
    flushCount(x - x % 3 + i / 3, y - y % 3 + i % 3);
    if (x == y) {
      flushCount(i, i);
    }
    if (x + y == 8) {
      flushCount(i, 8 - i);
    }
  }
}

void SudukuStructure::flushCount(int x, int y) {
  assert(0 <= x && x < 9 && 0 <= y && y < 9);
  int mask = entityChoise(x, y);
  int cnt = 0;
  while (mask) {
    mask ^= (mask & (-mask));
    cnt++;
  }
  if (board[x][y] == 0 && count[x][y] != cnt) {
    removeEmptyEntity(x, y);
    count[x][y] = cnt;
    addEmptyEntity(x, y);
  }
  count[x][y] = cnt;
}

int SudukuStructure::entityChoise(int x, int y) {
  int mask = hash[x] | hash[9 + y] | hash[18 + (x / 3) * 3 + y / 3];
  return mask ^ 511;
}

int SudukuStructure::firstTodo() {
  if (seq.size() == 0) {
    return -1;
  }
  return seq.begin()->second;
}

std::string SudukuStructure::getBoard() {
  std::string res;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      res += board[i][j] + '0';
    }
  }
  return res;
}
