#pragma once

#include <cstring>
// #include <exception>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  // Utility
  void S21Matrix::AllocateMatrix();
  void S21Matrix::DeallocateMatrix();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix SumMatrix(const S21Matrix& other);

  S21Matrix operator+(const S21Matrix& other);
  double& operator()(int i, int j) const;
};
