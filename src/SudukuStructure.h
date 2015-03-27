#ifndef __suduku_board_h__
#define __suduku_board_h__

#include <string>
#include <cassert>
#include <set>

class SudukuStructure {
  int board[9][9];
  int count[9][9];
  int hash[9 + 9 + 9]; //horizon ＋ vertical ＋ box
  std::set< std::pair<int, int> > seq;

public:
  SudukuStructure();
  SudukuStructure(std::string);
  void clear();
  int valueAt(int, int);
  void setValue(int, int, int);
  int emptyEntity();
  int entityChoise(int, int);
  int firstTodo();
  std::string getBoard();

private:
  void setStatus(int, int, int, int);
  void removeEmptyEntity(int, int);
  void addEmptyEntity(int, int);
  void flushSeq(int, int);
  void flushCount(int, int);
};

#endif
