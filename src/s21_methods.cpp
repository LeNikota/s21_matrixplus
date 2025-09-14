#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }
void S21Matrix::SetRows(int rows) { ReallocateMatrix(rows, cols_); }

int S21Matrix::GetCols() const { return cols_; }
void S21Matrix::SetCols(int cols) { ReallocateMatrix(rows_, cols); }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
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
  result.matrix_ = nullptr;  // Prevent double free
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw "The matrix is not square";

  int n = rows_;
  double det = 1.0;

  S21Matrix temp(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }

  for (int col = 0; col < n; col++) {
    // Partial pivoting:
    // find the row with the largest element in current column
    int max_row = col;
    for (int row = col + 1; row < n; row++) {
      if (fabs(temp.matrix_[row][col]) > fabs(temp.matrix_[max_row][col])) {
        max_row = row;
      }
    }

    // If the maximum element is zero, the matrix is singular
    if (fabs(temp.matrix_[max_row][col]) < 1e-8) return 0.0;

    // Swap rows if needed
    if (max_row != col) {
      for (int j = 0; j < n; j++) {
        double tmp = temp.matrix_[col][j];
        temp.matrix_[col][j] = temp.matrix_[max_row][j];
        temp.matrix_[max_row][j] = tmp;
      }
      det *= -1;  // Row swap changes the sign of determinant
    }

    // Perform elimination for all rows below
    for (int row = col + 1; row < n; row++) {
      double factor = temp.matrix_[row][col] / temp.matrix_[col][col];
      for (int j = col; j < n; j++) {
        temp.matrix_[row][j] -= factor * temp.matrix_[col][j];
      }
    }
  }

  // Calculate determinant as product of diagonal elements
  for (int i = 0; i < n; i++) {
    det *= temp.matrix_[i][i];
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw "The matrix is not square.";
  if (rows_ == 1 && cols_ == 1) {
    S21Matrix result(1, 1);
    result(0, 0) = 1;
    return result;
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = this->GetMinor(i, j);
      double det = minor.Determinant();

      result.matrix_[i][j] = det * ((i + j) % 2 ? -1 : 1);
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) throw "The matrix is not square.";

  double det = this->Determinant();
  if (fabs(det) < 1e-7) throw "Matrix determinant is 0.";

  S21Matrix adjugate = this->CalcComplements().Transpose();
  adjugate.MulNumber(1.0 / det);

  return adjugate;
}
