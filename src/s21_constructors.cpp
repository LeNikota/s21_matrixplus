#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { AllocateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  AllocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMatrix();
  memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { DeallocateMatrix(); }

// Utility
void S21Matrix::AllocateMatrix() {
  matrix_ = new double*[rows_];
  for (size_t i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::DeallocateMatrix() {
  if (!matrix_) return;

  for (size_t i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;

  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}
