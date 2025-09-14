#include <gtest/gtest.h>

#include <cmath>

#include "../s21_matrix_oop.h"

// Determinant Tests
TEST(ComplexArithmetics, Determinant1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5.0;

  EXPECT_DOUBLE_EQ(m.Determinant(), 5.0);
}

TEST(ComplexArithmetics, Determinant2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(m.Determinant(), -2.0);  // 1*4 - 2*3 = -2
}

TEST(ComplexArithmetics, Determinant3x3) {
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

TEST(ComplexArithmetics, DeterminantNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(ComplexArithmetics, DeterminantZero) {
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

  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

TEST(ComplexArithmetics, DeterminantLarge) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.0;
  m(0, 1) = 0.0;
  m(0, 2) = 2.0;
  m(0, 3) = -1.0;
  m(1, 0) = 3.0;
  m(1, 1) = 0.0;
  m(1, 2) = 0.0;
  m(1, 3) = 5.0;
  m(2, 0) = 2.0;
  m(2, 1) = 1.0;
  m(2, 2) = 4.0;
  m(2, 3) = -3.0;
  m(3, 0) = 1.0;
  m(3, 1) = 0.0;
  m(3, 2) = 5.0;
  m(3, 3) = 0.0;

  // Expected determinant: 30
  EXPECT_DOUBLE_EQ(m.Determinant(), 30.0);
}

// TEST(ComplexArithmetics, DeterminantEmpty) {
//   S21Matrix m;

//   EXPECT_THROW(m.Determinant(), std::invalid_argument);
// }

// CalcComplements Tests
TEST(ComplexArithmetics, CalcComplements1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5.0;

  S21Matrix result = m.CalcComplements();

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);  // Complement of 1x1 is always 1
}

TEST(ComplexArithmetics, CalcComplements2x2) {
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

TEST(ComplexArithmetics, CalcComplements3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 0.0;
  m(1, 1) = 4.0;
  m(1, 2) = 2.0;
  m(2, 0) = 5.0;
  m(2, 1) = 2.0;
  m(2, 2) = 1.0;

  S21Matrix result = m.CalcComplements();

  // Expected complements matrix:
  // [ (4*1 - 2*2), -(0*1 - 2*5), (0*2 - 4*5) ]
  // [ -(2*1 - 3*2), (1*1 - 3*5), -(1*2 - 2*5) ]
  // [ (2*2 - 3*4), -(1*2 - 3*0), (1*4 - 2*0) ]

  EXPECT_NEAR(result(0, 0), 0.0, 1e-10);    // 4*1 - 2*2 = 0
  EXPECT_NEAR(result(0, 1), 10.0, 1e-10);   // -(0*1 - 2*5) = 10
  EXPECT_NEAR(result(0, 2), -20.0, 1e-10);  // 0*2 - 4*5 = -20

  EXPECT_NEAR(result(1, 0), 4.0, 1e-10);    // -(2*1 - 3*2) = 4
  EXPECT_NEAR(result(1, 1), -14.0, 1e-10);  // 1*1 - 3*5 = -14
  EXPECT_NEAR(result(1, 2), 8.0, 1e-10);    // -(1*2 - 2*5) = 8

  EXPECT_NEAR(result(2, 0), -8.0, 1e-10);  // 2*2 - 3*4 = -8
  EXPECT_NEAR(result(2, 1), -2.0, 1e-10);  // -(1*2 - 3*0) = -2
  EXPECT_NEAR(result(2, 2), 4.0, 1e-10);   // 1*4 - 2*0 = 4
}

TEST(ComplexArithmetics, CalcComplementsNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.CalcComplements());
}

// InverseMatrix Tests
TEST(ComplexArithmetics, InverseMatrix2x2) {
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

TEST(ComplexArithmetics, InverseMatrix3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 2.0;
  m(0, 1) = 5.0;
  m(0, 2) = 7.0;
  m(1, 0) = 6.0;
  m(1, 1) = 3.0;
  m(1, 2) = 4.0;
  m(2, 0) = 5.0;
  m(2, 1) = -2.0;
  m(2, 2) = -3.0;

  S21Matrix result = m.InverseMatrix();

  // Expected inverse (verified with external calculator):
  EXPECT_NEAR(result(0, 0), 1.0, 1e-10);
  EXPECT_NEAR(result(0, 1), -1.0, 1e-10);
  EXPECT_NEAR(result(0, 2), 1.0, 1e-10);

  EXPECT_NEAR(result(1, 0), -38.0, 1e-10);
  EXPECT_NEAR(result(1, 1), 41.0, 1e-10);
  EXPECT_NEAR(result(1, 2), -34.0, 1e-10);

  EXPECT_NEAR(result(2, 0), 27.0, 1e-10);
  EXPECT_NEAR(result(2, 1), -29.0, 1e-10);
  EXPECT_NEAR(result(2, 2), 24.0, 1e-10);
}

TEST(ComplexArithmetics, InverseMatrixSingular) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 2.0;
  m(1, 1) = 4.0;  // det = 0

  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(ComplexArithmetics, InverseMatrixNonSquare) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(ComplexArithmetics, InverseMatrixIdentity) {
  S21Matrix m(3, 3);
  // Create identity matrix
  m(0, 0) = 1.0;
  m(0, 1) = 0.0;
  m(0, 2) = 0.0;
  m(1, 0) = 0.0;
  m(1, 1) = 1.0;
  m(1, 2) = 0.0;
  m(2, 0) = 0.0;
  m(2, 1) = 0.0;
  m(2, 2) = 1.0;

  S21Matrix result = m.InverseMatrix();

  // Inverse of identity is identity
  EXPECT_TRUE(m.EqMatrix(result));
}

TEST(ComplexArithmetics, InverseMatrixVerification) {
  // Test that A * A⁻¹ = I
  S21Matrix m(2, 2);
  m(0, 0) = 3.0;
  m(0, 1) = 1.0;
  m(1, 0) = 2.0;
  m(1, 1) = 4.0;

  S21Matrix inverse = m.InverseMatrix();
  S21Matrix identity = m * inverse;

  // Should be approximately identity matrix
  EXPECT_NEAR(identity(0, 0), 1.0, 1e-10);
  EXPECT_NEAR(identity(0, 1), 0.0, 1e-10);
  EXPECT_NEAR(identity(1, 0), 0.0, 1e-10);
  EXPECT_NEAR(identity(1, 1), 1.0, 1e-10);
}

// Edge Cases and Complex Scenarios
TEST(ComplexArithmetics, LargeMatrixDeterminant) {
  S21Matrix m(5, 5);
  // Create a matrix with known determinant
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      m(i, j) = (i == j) ? 2.0 : 0.0;  // Diagonal matrix with 2s
    }
  }

  // Determinant of diagonal matrix is product of diagonal elements
  // 2^5 = 32
  EXPECT_DOUBLE_EQ(m.Determinant(), 32.0);
}

TEST(ComplexArithmetics, MatrixChainOperations) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  // Test chain: transpose -> calc complements -> determinant
  S21Matrix transposed = m.Transpose();
  S21Matrix complements = transposed.CalcComplements();
  double det = complements.Determinant();

  // This should be mathematically valid
  EXPECT_NEAR(det, -2.0, 1e-10);  // Same as original determinant
}

TEST(ComplexArithmetics, PrecisionTesting) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0000000001;
  m(0, 1) = 2.0000000002;
  m(1, 0) = 3.0000000003;
  m(1, 1) = 4.0000000004;

  double det = m.Determinant();
  // Should handle precision correctly
  EXPECT_NEAR(det, -2.0, 1e-8);
}

TEST(ComplexArithmetics, ZeroMatrixOperations) {
  S21Matrix zero(2, 2);  // All zeros

  EXPECT_DOUBLE_EQ(zero.Determinant(), 0.0);
  EXPECT_THROW(zero.InverseMatrix(), std::invalid_argument);
}

TEST(ComplexArithmetics, IdentityMatrixOperations) {
  S21Matrix identity(3, 3);
  identity(0, 0) = 1.0;
  identity(0, 1) = 0.0;
  identity(0, 2) = 0.0;
  identity(1, 0) = 0.0;
  identity(1, 1) = 1.0;
  identity(1, 2) = 0.0;
  identity(2, 0) = 0.0;
  identity(2, 1) = 0.0;
  identity(2, 2) = 1.0;

  EXPECT_DOUBLE_EQ(identity.Determinant(), 1.0);

  S21Matrix inverse = identity.InverseMatrix();
  EXPECT_TRUE(identity.EqMatrix(inverse));
}

TEST(ComplexArithmetics, EmptyMComplexArithmetics) {
  S21Matrix empty1;
  S21Matrix empty2;

  // EqMatrix should work
  EXPECT_TRUE(empty1.EqMatrix(empty2));

  // OtherSimpleArithmetics should throw
  EXPECT_ANY_THROW(empty1.SumMatrix(empty2));
  EXPECT_ANY_THROW(empty1.SubMatrix(empty2));
  EXPECT_ANY_THROW(empty1.MulMatrix(empty2));
}

TEST(ComplexArithmetics, LargeMComplexArithmetics) {
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

// Complex operation chains
TEST(ComplexArithmetics, OperationChaining) {
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
