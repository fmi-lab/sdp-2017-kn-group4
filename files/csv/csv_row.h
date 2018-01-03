#ifndef CSV_ROW_H
#define CSV_ROW_H

#include <istream>
#include <vector>
#include <string>

class CSVRow {
  std::vector<std::string> cells;

public:

  size_t size() const;

  std::string const& operator[](size_t index) const;

  friend std::istream& operator>>(std::istream& stream, CSVRow& row);
};

#endif
