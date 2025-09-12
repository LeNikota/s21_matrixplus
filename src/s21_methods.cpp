#include "s21_matrix_oop.h"

// S21Matrix S21Matrix::Transpose();
// S21Matrix S21Matrix::CalcComplements();
// double S21Matrix::Determinant();
// S21Matrix S21Matrix::InverseMatrix();

int S21Matrix::GetRows() const { return rows_; }
void S21Matrix::SetRows(int rows) { ReallocateMatrix(rows, cols_); }

int S21Matrix::GetCols() const { return cols_; }
void S21Matrix::SetCols(int cols) { ReallocateMatrix(rows_, cols); }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "Matrices must have the same size";

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw "Matrices must have the same size";

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw "The number of columns of the first matrix is not equal to the number of rows of the second matrix.";

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  matrix_ = result.matrix_;
}