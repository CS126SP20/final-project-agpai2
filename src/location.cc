//
// Created by Aniruddha Pai on 4/18/20.
//

#include <mylibrary/location.h>

namespace mylibrary {

Location::Location(int row, int col) : row_(row), col_(col) {}

Location Location::operator+(const Location& rhs) const {
  return { row_ + rhs.row_, col_ + rhs.col_ };
}

bool Location::operator==(const Location& rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}

int mod(int a, int b) {
  int c = a % b;
  return c + (c < 0 ? b : 0);
}

Location Location::operator%(const Location& rhs) const {
  return {mod(row_, rhs.row_), mod(col_, rhs.col_)};
}

int Location::Row() const { return row_; }
int Location::Col() const { return col_; }

}
