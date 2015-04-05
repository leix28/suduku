#ifndef __suduku_board_h__
#define __suduku_board_h__

#include <string>
#include <cassert>
#include <set>

class SudukuStructure {
  int board[9][9];
  int count[9][9];                  //number of choice
  int hash[9 + 9 + 9];              //horizon ＋ vertical ＋ box
  std::set< std::pair<int, int> > seq; //Todo list sort by choice

public:
  SudukuStructure();
  SudukuStructure(std::string);     //init structure with partly filled suduku, 0 for empty entity
  void clear();
  int valueAt(int, int);
  void setValue(int, int, int);     //(index, value), empty is not required and assert fail when conflict
  int emptyEntity();                //get the number of unfilled entities
  int entityChoise(int, int);       //get all the choice of an entity in bitset
  int firstTodo();                  //get the index of an empty entity with the fewest choice
  std::string getBoard();           //get the status of board in string

private:
  void setStatus(int, int, int, int);
  void removeEmptyEntity(int, int);
  void addEmptyEntity(int, int);
  void flushSeq(int, int);
  void flushCount(int, int);
};

#endif
