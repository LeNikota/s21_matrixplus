#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

void S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return;

  ReallocateMatrix(other.rows_, other.cols_);
  memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const double number) {
  this->MulNumber(number);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_)
    throw "Incorrect input, index is out of range";

  return matrix_[row][col];
}
