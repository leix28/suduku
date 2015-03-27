#include "SudukuStructure.h"

#include <iostream>
#define FIND_RESULT_EXCEPTION 0x0000FFFF

void dfs(SudukuStructure &suduku) {
  if (suduku.emptyEntity() == 0) {
    throw FIND_RESULT_EXCEPTION;
  }
  int index = suduku.firstTodo();
  assert(index != -1);
  int choise = suduku.entityChoise(index / 9, index % 9);
  for (int i = 1; i <= 9; i++) {
    if (!(choise & (1 << (i - 1)))) {
      continue;
    }
    suduku.setValue(index / 9, index % 9, i);
    dfs(suduku);
    suduku.setValue(index / 9, index % 9, 0);
  }
}

int main () {
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);


  std::string board, line;
  for (int i = 0; i < 9; i++) {
    std::cin >> line;
    board += line;
  }
  SudukuStructure suduku(board);

  try {
    dfs(suduku);
  } catch(int E) {
    if (E == FIND_RESULT_EXCEPTION) {
      board = suduku.getBoard();
      for (int i = 0; i < 9; i++) {
        std::cout << board.substr(i * 9, 9) << std::endl;
      }
    }
  }
  return 0;
}
