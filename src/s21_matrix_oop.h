#pragma once

#include <cstring>
#include <iomanip>  // For std::setw
#include <iostream>

// TODO: If the matrix increases in size, it is filled with zeros.
// TODO: If it  decreases in size, the excess is simply discarded;
// TODO: Delete print if not used
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_ = nullptr;

  // Utility
  void AllocateMatrix();
  void ReallocateMatrix(int rows, int cols);
  void DeallocateMatrix();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);

  void SumMatrix(const S21Matrix& other);

  S21Matrix operator+(const S21Matrix& other);
  double& operator()(int i, int j) const;

  // Utility
  void Print() const;
};
