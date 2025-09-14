#include <gtest/gtest.h>

#include <cmath>

#include "../s21_matrix_oop.h"

// EqMatrix Tests
TEST(SimpleArithmetics, EqMatrixSame) {
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

TEST(SimpleArithmetics, EqMatrixDifferentValues) {
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

TEST(SimpleArithmetics, EqMatrixDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);
  S21Matrix m3(3, 2);

  EXPECT_FALSE(m1.EqMatrix(m2));
  EXPECT_FALSE(m1.EqMatrix(m3));
  EXPECT_FALSE(m2.EqMatrix(m3));
}

TEST(SimpleArithmetics, EqMatrixEmpty) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2.EqMatrix(m1));
}

TEST(SimpleArithmetics, EqMatrixPrecision) {
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
TEST(SimpleArithmetics, SumMatrixValid) {
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

TEST(SimpleArithmetics, SumMatrixInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);
  S21Matrix m3(3, 2);

  EXPECT_ANY_THROW(m1.SumMatrix(m2));
  EXPECT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(SimpleArithmetics, SumMatrixWithZero) {
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
TEST(SimpleArithmetics, SubMatrixValid) {
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

TEST(SimpleArithmetics, SubMatrixInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);

  EXPECT_ANY_THROW(m1.SubMatrix(m2));
}

// MulNumber Tests
TEST(SimpleArithmetics, MulNumberPositive) {
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

TEST(SimpleArithmetics, MulNumberNegative) {
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

TEST(SimpleArithmetics, MulNumberZero) {
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
TEST(SimpleArithmetics, MulMatrixValid) {
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

TEST(SimpleArithmetics, MulMatrixInvalidDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);  // Incompatible dimensions

  EXPECT_ANY_THROW(m1.MulMatrix(m2));
}

// Transpose Tests
TEST(SimpleArithmetics, TransposeSquare) {
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

TEST(SimpleArithmetics, TransposeRectangular) {
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

TEST(SimpleArithmetics, TransposeSingleElement) {
  S21Matrix m(1, 1);
  m(0, 0) = 42.0;

  S21Matrix result = m.Transpose();

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_DOUBLE_EQ(result(0, 0), 42.0);
}

TEST(SimpleArithmetics, TransposeEmpty) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.Transpose());
}

TEST(SimpleArithmetics, TransposeDoubleTranspose) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;

  S21Matrix transposed = m.Transpose();
  S21Matrix doubleTransposed = transposed.Transpose();

  EXPECT_TRUE(m.EqMatrix(doubleTransposed));
}
