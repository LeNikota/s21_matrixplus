#include "s21_matrix_oop.h"

void S21Matrix::AllocateMatrix() {
  if (matrix_ != nullptr) throw "DeallocateMatrix before AllocateMatrix";

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::ReallocateMatrix(int rows, int cols) {
  if (rows == rows_ && cols == cols_) return;

  S21Matrix temp(rows, cols);

  int rows_limit = rows > rows_ ? rows_ : rows;
  int cols_limit = cols > cols_ ? cols_ : cols;

  for (int i = 0; i < rows_limit; i++) {
    for (int j = 0; j < cols_limit; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }

  DeallocateMatrix();
  rows_ = rows;
  cols_ = cols;
  AllocateMatrix();
  memcpy(matrix_, temp.matrix_, rows_ * cols_ * sizeof(double));
}

void S21Matrix::DeallocateMatrix() {
  if (matrix_ == nullptr) return;

  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;

  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix S21Matrix::GetMinor(int row, int col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0, mi = 0; i < rows_; i++) {
    if (i == row) continue;
    for (int j = 0, mj = 0; j < cols_; j++) {
      if (j == col) continue;
      minor.matrix_[mi][mj] = matrix_[i][j];
      mj++;
    }
    mi++;
  }

  return minor;
}

void S21Matrix::Print() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << std::setw(5) << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
