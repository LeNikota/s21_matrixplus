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

  if (rows < 0 || cols < 0) {
    throw "Rows and columns must be positive";
  }

  if (rows == 0 || cols == 0) {
    DeallocateMatrix();

    rows_ = rows;
    cols_ = cols;

    return;
  }

  S21Matrix temp(rows, cols);

  int rows_to_copy = std::min(rows, rows_);
  int cols_to_copy = std::min(cols, cols_);

  for (int i = 0; i < rows_to_copy; i++) {
    for (int j = 0; j < cols_to_copy; j++) {
      temp(i, j) = matrix_[i][j];
    }
  }

  std::swap(rows_, temp.rows_);
  std::swap(cols_, temp.cols_);
  std::swap(matrix_, temp.matrix_);
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
