#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_)
    throw "Incorrect input, index is out of range";

  return matrix_[row][col];
}