#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }
void S21Matrix::SetRows(int rows) { ReallocateMatrix(rows, cols_); }

int S21Matrix::GetCols() const { return cols_; }
void S21Matrix::SetCols(int cols) { ReallocateMatrix(rows_, cols); }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "Incorrect input, matrices should have the same size";

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}