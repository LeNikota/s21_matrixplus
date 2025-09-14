#pragma once

#include <cmath>
#include <cstring>
#include <iomanip>  // For std::setw
#include <iostream>

class S21Matrix {
 private:
  int rows_ = 0;
  int cols_ = 0;
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

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double number) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double number);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int i, int j) const;

  friend S21Matrix operator*(double num, const S21Matrix& matrix);

  // Utility
  S21Matrix GetMinor(int row, int col) const;
  void Print() const;
};
