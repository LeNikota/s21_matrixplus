#include <gtest/gtest.h>

#include <cmath>

#include "../s21_matrix_oop.h"

// EqMatrix Tests
TEST(MatrixOperations, EqMatrixSame) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2.EqMatrix(m1));
}

TEST(MatrixOperations, EqMatrixDifferentValues) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 5.0;

  EXPECT_FALSE(m1.EqMatrix(m2));
  EXPECT_FALSE(m2.EqMatrix(m1));
}

TEST(MatrixOperations, EqMatrixDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);
  S21Matrix m3(3, 2);

  EXPECT_FALSE(m1.EqMatrix(m2));
  EXPECT_FALSE(m1.EqMatrix(m3));
  EXPECT_FALSE(m2.EqMatrix(m3));
}

TEST(MatrixOperations, EqMatrixEmpty) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2.EqMatrix(m1));
}

TEST(MatrixOperations, EqMatrixPrecision) {
  S21Matrix m1(1, 1);
  S21Matrix m2(1, 1);
  m1(0, 0) = 1.0000001;
  m2(0, 0) = 1.0000002;

  // Should be equal within reasonable precision
  EXPECT_TRUE(m1.EqMatrix(m2));

  m2(0, 0) = 1.0001;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

// SumMatrix Tests
TEST(MatrixOperations, SumMatrixValid) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;

  m1.SumMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12.0);

  // m2 should remain unchanged
  EXPECT_DOUBLE_EQ(m2(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 6.0);
}

TEST(MatrixOperations, SumMatrixInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);
  S21Matrix m3(3, 2);

  EXPECT_ANY_THROW(m1.SumMatrix(m2));
  EXPECT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(MatrixOperations, SumMatrixWithZero) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);  // All zeros by default
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m1.SumMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 4.0);
}

// SubMatrix Tests
TEST(MatrixOperations, SubMatrixValid) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 10.0;
  m1(0, 1) = 20.0;
  m1(1, 0) = 30.0;
  m1(1, 1) = 40.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  m1.SubMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 9.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 18.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 27.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 36.0);
}

TEST(MatrixOperations, SubMatrixInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);

  EXPECT_ANY_THROW(m1.SubMatrix(m2));
}

// MulNumber Tests
TEST(MatrixOperations, MulNumberPositive) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m.MulNumber(2.5);

  EXPECT_DOUBLE_EQ(m(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(m(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(m(1, 1), 10.0);
}

TEST(MatrixOperations, MulNumberNegative) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m.MulNumber(-2.0);

  EXPECT_DOUBLE_EQ(m(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(m(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(m(1, 0), -6.0);
  EXPECT_DOUBLE_EQ(m(1, 1), -8.0);
}

TEST(MatrixOperations, MulNumberZero) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m.MulNumber(0.0);

  EXPECT_DOUBLE_EQ(m(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

// MulMatrix Tests
TEST(MatrixOperations, MulMatrixValid) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);

  // m1 = [1, 2, 3]
  //      [4, 5, 6]
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  // m2 = [7, 8]
  //      [9, 10]
  //      [11, 12]
  m2(0, 0) = 7.0;
  m2(0, 1) = 8.0;
  m2(1, 0) = 9.0;
  m2(1, 1) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;

  m1.MulMatrix(m2);

  // Result should be 2x2 matrix:
  // [1*7 + 2*9 + 3*11, 1*8 + 2*10 + 3*12] = [58, 64]
  // [4*7 + 5*9 + 6*11, 4*8 + 5*10 + 6*12] = [139, 154]
  EXPECT_DOUBLE_EQ(m1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 154.0);

  // m2 should remain unchanged
  EXPECT_DOUBLE_EQ(m2(0, 0), 7.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 8.0);
}

TEST(MatrixOperations, MulMatrixInvalidDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);  // Incompatible dimensions

  EXPECT_ANY_THROW(m1.MulMatrix(m2));
}

// Transpose Tests
TEST(MatrixOperations, TransposeSquare) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m.Transpose();

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(MatrixOperations, TransposeRectangular) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;

  S21Matrix result = m.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

// Determinant Tests
TEST(MatrixOperations, Determinant1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5.0;

  EXPECT_DOUBLE_EQ(m.Determinant(), 5.0);
}

TEST(MatrixOperations, Determinant2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(m.Determinant(), -2.0);  // 1*4 - 2*3 = -2
}

TEST(MatrixOperations, Determinant3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;
  m(2, 0) = 7.0;
  m(2, 1) = 8.0;
  m(2, 2) = 9.0;

  // det = 1*(5*9 - 6*8) - 2*(4*9 - 6*7) + 3*(4*8 - 5*7)
  //     = 1*(45-48) - 2*(36-42) + 3*(32-35)
  //     = 1*(-3) - 2*(-6) + 3*(-3)
  //     = -3 + 12 - 9 = 0
  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

TEST(MatrixOperations, DeterminantNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

// CalcComplements Tests
TEST(MatrixOperations, CalcComplements2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m.CalcComplements();

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
}

TEST(MatrixOperations, CalcComplementsNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.CalcComplements());
}

// InverseMatrix Tests
TEST(MatrixOperations, InverseMatrix2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 4.0;
  m(0, 1) = 7.0;
  m(1, 0) = 2.0;
  m(1, 1) = 6.0;

  S21Matrix result = m.InverseMatrix();

  // det = 4*6 - 7*2 = 24 - 14 = 10
  // inverse = (1/10) * [6, -7; -2, 4] = [0.6, -0.7; -0.2, 0.4]
  EXPECT_NEAR(result(0, 0), 0.6, 1e-10);
  EXPECT_NEAR(result(0, 1), -0.7, 1e-10);
  EXPECT_NEAR(result(1, 0), -0.2, 1e-10);
  EXPECT_NEAR(result(1, 1), 0.4, 1e-10);
}

TEST(MatrixOperations, InverseMatrixSingular) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 2.0;
  m(1, 1) = 4.0;  // det = 0

  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(MatrixOperations, InverseMatrixNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.InverseMatrix());
}

// Complex operation chains
TEST(MatrixOperations, OperationChaining) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;

  // (m1 + m2) * 2
  m1.SumMatrix(m2);
  m1.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(m1(0, 0), 12.0);  // (1+5)*2
  EXPECT_DOUBLE_EQ(m1(0, 1), 16.0);  // (2+6)*2
  EXPECT_DOUBLE_EQ(m1(1, 0), 20.0);  // (3+7)*2
  EXPECT_DOUBLE_EQ(m1(1, 1), 24.0);  // (4+8)*2
}

// Edge cases
TEST(MatrixOperations, EmptyMatrixOperations) {
  S21Matrix empty1;
  S21Matrix empty2;

  // EqMatrix should work
  EXPECT_TRUE(empty1.EqMatrix(empty2));

  // Other operations should throw
  EXPECT_ANY_THROW(empty1.SumMatrix(empty2));
  EXPECT_ANY_THROW(empty1.SubMatrix(empty2));
  EXPECT_ANY_THROW(empty1.MulMatrix(empty2));
}

TEST(MatrixOperations, LargeMatrixOperations) {
  // Test with larger matrices
  S21Matrix m1(10, 10);
  S21Matrix m2(10, 10);

  // Fill with values
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      m1(i, j) = i + j;
      m2(i, j) = i - j;
    }
  }

  // Test sum
  m1.SumMatrix(m2);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      EXPECT_DOUBLE_EQ(m1(i, j), (i + j) + (i - j));
    }
  }
}