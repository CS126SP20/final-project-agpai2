//
// Created by Aniruddha Pai on 4/18/20.
//

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

namespace zelda {

class Location {
 public:
  Location(int row, int col);

  // Vector operators.
  Location operator+(const Location& rhs) const;
  // Note: Always returns positive coordinates.
  Location operator%(const Location& rhs) const;

  bool operator==(const Location& rhs) const;

  // Accessors.
  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;
};

} // namespace zelda

#endif  // FINALPROJECT_LOCATION_H
