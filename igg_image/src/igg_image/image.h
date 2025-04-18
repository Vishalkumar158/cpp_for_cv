#pragma once

#include <vector>

namespace igg {

class Image {
 public:
  ///////////////////// Create the public interface here ///////////////////////
  Image();
  Image(int rows, int cols);
  int rows();
  int cols();
  int& at(const int& row, const int& col);
  bool FillFromPgm(const std::string& file_name);
  void WriteToPgm(const std::string& file_name);
 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

}  // namespace igg
