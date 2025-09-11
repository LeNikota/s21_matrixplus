#include "s21_matrix_oop.h"

S21Matrix S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "Incorrect input, matrices should have the same size";

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; i < cols_; i++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}