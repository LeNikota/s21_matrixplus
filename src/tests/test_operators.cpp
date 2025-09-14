#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

// ====================   +   ====================
TEST(Operator, AdditionOperator) {
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

  S21Matrix result = m1 + m2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);

  // Original matrices unchanged
  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(0, 0), 5.0);
}

TEST(Operator, AdditionOperatorInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_ANY_THROW(m1 + m2);
}

TEST(Operator, AdditionEmptyMatrices) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_ANY_THROW(m1 + m2);
}

TEST(Operator, AdditionDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  S21Matrix m3(2, 3);

  EXPECT_ANY_THROW(m1 + m2);
  EXPECT_ANY_THROW(m1 + m3);
  EXPECT_ANY_THROW(m3 + m1);
}

TEST(Operator, AdditionSelfAddition) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  S21Matrix m2 = m1 + m1;

  EXPECT_DOUBLE_EQ(m2(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m2(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m2(1, 1), 8.0);

  // Original unchanged
  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);
}

TEST(Operator, AdditionZeroMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix zero(2, 2);  // All zeros
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  S21Matrix result = m1 + zero;

  EXPECT_TRUE(m1 == result);
}

TEST(Operator, AdditionLargeMatrices) {
  S21Matrix m1(100, 100);
  S21Matrix m2(100, 100);

  // Fill with values
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      m1(i, j) = i + j;
      m2(i, j) = i - j;
    }
  }

  S21Matrix result = m1 + m2;

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), (i + j) + (i - j));
    }
  }
}

// ====================   +=   ====================
TEST(Operator, AdditionAssignmentEmptyMatrices) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_ANY_THROW(m1 += m2);
}

TEST(Operator, AdditionAssignmentDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_ANY_THROW(m1 += m2);
}

TEST(Operator, AdditionAssignmentSelfAdditionAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m += m;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 8.0);
}

TEST(Operator, AdditionAssignmentZeroMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix zero(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m1 += zero;

  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 4.0);
}

TEST(Operator, AdditionAssignmentChainedOperation) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  S21Matrix m3(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;
  m3(0, 0) = 9.0;
  m3(0, 1) = 10.0;
  m3(1, 0) = 11.0;
  m3(1, 1) = 12.0;

  (m1 += m2) += m3;

  EXPECT_DOUBLE_EQ(m1(0, 0), 15.0);  // 1 + 5 + 9
  EXPECT_DOUBLE_EQ(m1(0, 1), 18.0);  // 2 + 6 + 10
  EXPECT_DOUBLE_EQ(m1(1, 0), 21.0);  // 3 + 7 + 11
  EXPECT_DOUBLE_EQ(m1(1, 1), 24.0);  // 4 + 8 + 12
}

TEST(Operator, AdditionAssignmentReturnReference) {
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

  S21Matrix& ref = (m1 += m2);

  // Should return reference to m1
  EXPECT_EQ(&ref, &m1);
  EXPECT_DOUBLE_EQ(ref(0, 0), 6.0);
}

// ====================   -   ====================
TEST(Operator, MinusBasicSubtraction) {
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

  S21Matrix result = m1 - m2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 9.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 18.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 27.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 36.0);

  // Original matrices unchanged
  EXPECT_DOUBLE_EQ(m1(0, 0), 10.0);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
}

TEST(Operator, MinusNegativeValues) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 5.0;
  m1(0, 1) = -3.0;
  m1(1, 0) = -2.0;
  m1(1, 1) = 8.0;
  m2(0, 0) = 2.0;
  m2(0, 1) = 4.0;
  m2(1, 0) = -1.0;
  m2(1, 1) = 3.0;

  S21Matrix result = m1 - m2;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);   // 5 - 2
  EXPECT_DOUBLE_EQ(result(0, 1), -7.0);  // -3 - 4
  EXPECT_DOUBLE_EQ(result(1, 0), -1.0);  // -2 - (-1) = -2 + 1
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);   // 8 - 3
}

TEST(Operator, MinusSelfSubtraction) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m - m;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);

  // Original unchanged
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
}

TEST(Operator, MinusZeroMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix zero(2, 2);  // All zeros
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  S21Matrix result = m1 - zero;

  EXPECT_TRUE(m1 == result);
}

TEST(Operator, MinusDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  S21Matrix m3(2, 3);

  EXPECT_ANY_THROW(m1 - m2);
  EXPECT_ANY_THROW(m1 - m3);
  EXPECT_ANY_THROW(m3 - m1);
}

TEST(Operator, MinusEmptyMatrices) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_ANY_THROW(m1 - m2);
}

TEST(Operator, MinusLargeMatrices) {
  S21Matrix m1(100, 100);
  S21Matrix m2(100, 100);

  // Fill with values
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      m1(i, j) = i + j + 100.0;
      m2(i, j) = i + j;
    }
  }

  S21Matrix result = m1 - m2;

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), 100.0);
    }
  }
}

TEST(Operator, MinusChainedSubtraction) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  S21Matrix m3(2, 2);
  m1(0, 0) = 20.0;
  m1(0, 1) = 20.0;
  m1(1, 0) = 20.0;
  m1(1, 1) = 20.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;
  m3(0, 0) = 2.0;
  m3(0, 1) = 2.0;
  m3(1, 0) = 2.0;
  m3(1, 1) = 2.0;

  S21Matrix result = m1 - m2 - m3;

  EXPECT_DOUBLE_EQ(result(0, 0), 13.0);  // 20 - 5 - 2
  EXPECT_DOUBLE_EQ(result(0, 1), 12.0);  // 20 - 6 - 2
  EXPECT_DOUBLE_EQ(result(1, 0), 11.0);  // 20 - 7 - 2
  EXPECT_DOUBLE_EQ(result(1, 1), 10.0);  // 20 - 8 - 2
}

TEST(Operator, MinusOperatorInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);

  EXPECT_ANY_THROW(m1 - m2);
}

// ====================   -=   ====================
TEST(Operator, MinusAssignmentEmptyMatrices) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_ANY_THROW(m1 -= m2);
}

TEST(Operator, MinusAssignmentChainedOperation) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  S21Matrix m3(2, 2);
  m1(0, 0) = 20.0;
  m1(0, 1) = 20.0;
  m1(1, 0) = 20.0;
  m1(1, 1) = 20.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(1, 0) = 7.0;
  m2(1, 1) = 8.0;
  m3(0, 0) = 2.0;
  m3(0, 1) = 2.0;
  m3(1, 0) = 2.0;
  m3(1, 1) = 2.0;

  (m1 -= m2) -= m3;

  EXPECT_DOUBLE_EQ(m1(0, 0), 13.0);  // 20 - 5 - 2
  EXPECT_DOUBLE_EQ(m1(0, 1), 12.0);  // 20 - 6 - 2
  EXPECT_DOUBLE_EQ(m1(1, 0), 11.0);  // 20 - 7 - 2
  EXPECT_DOUBLE_EQ(m1(1, 1), 10.0);  // 20 - 8 - 2
}

TEST(Operator, MinusAssignmentAdditionAssignmentOperator) {
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

  m1 += m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12.0);

  // m2 should be unchanged
  EXPECT_DOUBLE_EQ(m2(0, 0), 5.0);
}

TEST(Operator, MinusAssignmentBasicSubtractionAssignment) {
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

  m1 -= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 9.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 18.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 27.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 36.0);

  // m2 unchanged
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
}

TEST(Operator, MinusAssignmentSelfSubtractionAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m -= m;

  EXPECT_DOUBLE_EQ(m(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST(Operator, MinusAssignmentZeroMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix zero(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m1 -= zero;

  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 4.0);
}

TEST(Operator, MinusAssignmentDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_ANY_THROW(m1 -= m2);
}

TEST(Operator, MinusAssignmentReturnReference) {
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

  S21Matrix& ref = (m1 -= m2);

  // Should return reference to m1
  EXPECT_EQ(&ref, &m1);
  EXPECT_DOUBLE_EQ(ref(0, 0), 9.0);
}

TEST(Operator, MinusAssignmentNegativeResult) {
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

  m1 -= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), -4.0);  // 1 - 5
  EXPECT_DOUBLE_EQ(m1(0, 1), -4.0);  // 2 - 6
  EXPECT_DOUBLE_EQ(m1(1, 0), -4.0);  // 3 - 7
  EXPECT_DOUBLE_EQ(m1(1, 1), -4.0);  // 4 - 8
}

TEST(Operator, MinusAssignmentPrecisionTest) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0000001;
  m1(0, 1) = 2.0000002;
  m1(1, 0) = 3.0000003;
  m1(1, 1) = 4.0000004;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  m1 -= m2;

  EXPECT_NEAR(m1(0, 0), 0.0000001, 1e-10);
  EXPECT_NEAR(m1(0, 1), 0.0000002, 1e-10);
  EXPECT_NEAR(m1(1, 0), 0.0000003, 1e-10);
  EXPECT_NEAR(m1(1, 1), 0.0000004, 1e-10);
}

// ====================   *= (scalar)   ====================
TEST(Operator, ScalarMultiplicationAssignmentOperator) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m *= 2.5;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(m(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(m(1, 1), 10.0);
}

TEST(Operator, ScalarMultiplicationAssignmentChaining) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  (m *= 2.0) *= 3.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 6.0);   // 1 * 2 * 3
  EXPECT_DOUBLE_EQ(m(0, 1), 12.0);  // 2 * 2 * 3
  EXPECT_DOUBLE_EQ(m(1, 0), 18.0);  // 3 * 2 * 3
  EXPECT_DOUBLE_EQ(m(1, 1), 24.0);  // 4 * 2 * 3
}

TEST(Operator, ScalarMultiplicationAssignmentNegative) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m *= -2.0;

  EXPECT_DOUBLE_EQ(m(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(m(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(m(1, 0), -6.0);
  EXPECT_DOUBLE_EQ(m(1, 1), -8.0);
}

TEST(Operator, ScalarMultiplicationAssignmentOne) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m *= 1.0;  // Identity multiplication

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST(Operator, ScalarMultiplicationAssignmentFraction) {
  S21Matrix m(2, 2);
  m(0, 0) = 4.0;
  m(0, 1) = 8.0;
  m(1, 0) = 12.0;
  m(1, 1) = 16.0;

  m *= 0.5;  // Multiply by 1/2

  EXPECT_DOUBLE_EQ(m(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 8.0);
}

TEST(Operator, ScalarMultiplicationAssignmentReturnReference) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix& ref = (m *= 2.0);

  EXPECT_EQ(&ref, &m);  // Should return reference to itself
  EXPECT_DOUBLE_EQ(ref(0, 0), 2.0);
}

TEST(Operator, ScalarMultiplicationAssignmentEmptyMatrix) {
  S21Matrix m;

  EXPECT_THROW(m *= 2.0, std::invalid_argument);
}

TEST(Operator, ScalarMultiplicationAssignmentPrecision) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0000001;
  m(0, 1) = 2.0000002;
  m(1, 0) = 3.0000003;
  m(1, 1) = 4.0000004;

  m *= 2.0;

  EXPECT_NEAR(m(0, 0), 2.0000002, 1e-10);
  EXPECT_NEAR(m(0, 1), 4.0000004, 1e-10);
  EXPECT_NEAR(m(1, 0), 6.0000006, 1e-10);
  EXPECT_NEAR(m(1, 1), 8.0000008, 1e-10);
}

// ====================   *= (matrix)   ====================
TEST(Operator, MatrixMultiplicationAssignmentOperator) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  m2(0, 0) = 7.0;
  m2(0, 1) = 8.0;
  m2(1, 0) = 9.0;
  m2(1, 1) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;

  m1 *= m2;

  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(m1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(m1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(m1(1, 1), 154.0);
}

TEST(Operator, MatrixMultiplicationAssignmentSquareMatrices) {
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

  m1 *= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 19.0);  // 1*5 + 2*7
  EXPECT_DOUBLE_EQ(m1(0, 1), 22.0);  // 1*6 + 2*8
  EXPECT_DOUBLE_EQ(m1(1, 0), 43.0);  // 3*5 + 4*7
  EXPECT_DOUBLE_EQ(m1(1, 1), 50.0);  // 3*6 + 4*8
}

TEST(Operator, MatrixMultiplicationAssignmentReturnReference) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  // Initialize matrices...

  S21Matrix& ref = (m1 *= m2);

  EXPECT_EQ(&ref, &m1);  // Should return reference to itself
}

TEST(Operator, MatrixMultiplicationAssignmentIncompatibleDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 2);  // Incompatible: 3 != 4

  EXPECT_THROW(m1 *= m2, std::invalid_argument);
}

TEST(Operator, MatrixMultiplicationAssignmentEmptyMatrix) {
  S21Matrix m1;
  S21Matrix m2(2, 2);

  EXPECT_THROW(m1 *= m2, std::invalid_argument);
  EXPECT_THROW(m2 *= m1, std::invalid_argument);
}

TEST(Operator, MatrixMultiplicationAssignmentIdentity) {
  S21Matrix m1(2, 2);
  S21Matrix identity(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  identity(0, 0) = 1.0;
  identity(0, 1) = 0.0;
  identity(1, 0) = 0.0;
  identity(1, 1) = 1.0;

  m1 *= identity;

  EXPECT_TRUE(m1 == m1);  // Should remain unchanged
}

// ====================   ()   ====================
TEST(Operator, ParenthesesOperatorGet) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST(Operator, ParenthesesOperatorSet) {
  S21Matrix m(2, 2);

  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST(Operator, ParenthesesOperatorConstAccess) {
  const S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST(Operator, ParenthesesOperatorOutOfBounds) {
  S21Matrix m(2, 2);

  EXPECT_THROW(m(-1, 0), std::out_of_range);
  EXPECT_THROW(m(0, -1), std::out_of_range);
  EXPECT_THROW(m(2, 0), std::out_of_range);
  EXPECT_THROW(m(0, 2), std::out_of_range);
  EXPECT_THROW(m(10, 10), std::out_of_range);
}

TEST(Operator, ParenthesesOperatorEmptyMatrix) {
  S21Matrix m;

  EXPECT_THROW(m(0, 0), std::out_of_range);
}

TEST(Operator, ParenthesesOperatorModifyAndRead) {
  S21Matrix m(2, 2);

  // Write using operator()
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  // Read back using operator()
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);

  // Modify and read again
  m(0, 0) = 5.0;
  EXPECT_DOUBLE_EQ(m(0, 0), 5.0);
}

// ====================   * (scalar)   ====================
TEST(Operator, ScalarMultiplicationOperator) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m * 2.5;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(result(1, 1), 10.0);
}

TEST(Operator, ScalarMultiplicationOperatorZero) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m * 0.0;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST(Operator, ScalarMultiplicationCommutative) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result1 = m * 2.5;
  S21Matrix result2 = 2.5 * m;  // If you implement friend operator*

  EXPECT_TRUE(result1 == result2);
}

TEST(Operator, ScalarMultiplicationNegative) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m * -1.0;

  EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST(Operator, ScalarMultiplicationOriginalUnchanged) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix result = m * 2.0;

  // Original should be unchanged
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

// ====================   * (matrix)   ====================
TEST(Operator, MatrixMultiplicationOperator) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  m2(0, 0) = 7.0;
  m2(0, 1) = 8.0;
  m2(1, 0) = 9.0;
  m2(1, 1) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;

  S21Matrix result = m1 * m2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);   // 1*7 + 2*9 + 3*11
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);   // 1*8 + 2*10 + 3*12
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);  // 4*7 + 5*9 + 6*11
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);  // 4*8 + 5*10 + 6*12
}

TEST(Operator, MatrixMultiplicationInvalidDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);  // Incompatible dimensions

  EXPECT_ANY_THROW(m1 * m2);
}

TEST(Operator, MatrixMultiplicationWithZeroMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix zero(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  S21Matrix result = m1 * zero;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST(Operator, MatrixMultiplicationWithIdentity) {
  S21Matrix m1(2, 2);
  S21Matrix identity(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  identity(0, 0) = 1.0;
  identity(0, 1) = 0.0;
  identity(1, 0) = 0.0;
  identity(1, 1) = 1.0;

  S21Matrix result = m1 * identity;

  EXPECT_TRUE(result == m1);  // Should be unchanged
}

TEST(Operator, MatrixMultiplicationOriginalMatricesUnchanged) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  // Initialize matrices...

  S21Matrix result = m1 * m2;

  // Originals should be unchanged
  EXPECT_DOUBLE_EQ(m1(0, 0), 1.0);  // Or whatever initial values
  EXPECT_DOUBLE_EQ(m2(0, 0), 7.0);
}

TEST(Operator, MatrixMultiplicationLargeMatrices) {
  S21Matrix m1(10, 10);
  S21Matrix m2(10, 10);

  // Fill with predictable values
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      m1(i, j) = i + j;
      m2(i, j) = i - j;
    }
  }

  S21Matrix result = m1 * m2;

  // Spot check some values
  EXPECT_NEAR(result(0, 0), -285.0, 1e-10);  // Sum of products
  EXPECT_NEAR(result(9, 9), 285.0, 1e-10);
}

// ====================   =   ====================
TEST(Operator, SelfAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m = m;  // Should handle gracefully

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
}

TEST(Operator, EmptyToNonEmpty) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  S21Matrix empty;

  m1 = empty;

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
  EXPECT_ANY_THROW(m1(0, 0));
}

TEST(Operator, NonEmptyToEmpty) {
  S21Matrix empty;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 4.0;

  empty = m2;

  EXPECT_EQ(empty.GetRows(), 2);
  EXPECT_EQ(empty.GetCols(), 2);
  EXPECT_DOUBLE_EQ(empty(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(empty(0, 1), 2.0);
}

TEST(Operator, DifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 5.0;
  m2(0, 1) = 6.0;
  m2(0, 2) = 7.0;
  m2(1, 0) = 8.0;
  m2(1, 1) = 9.0;
  m2(1, 2) = 10.0;
  m2(2, 0) = 11.0;
  m2(2, 1) = 12.0;
  m2(2, 2) = 13.0;

  m1 = m2;  // Should reallocate memory

  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_EQ(m1.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(m1(2, 2), 13.0);
}

TEST(Operator, ChainedAssignment) {
  S21Matrix m1(2, 2), m2, m3;
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m3 = m2 = m1;

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m1 == m3);
  EXPECT_TRUE(m2 == m3);
}

TEST(Operator, AssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  S21Matrix m2;
  m2 = m1;

  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m2(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(m2(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m2(1, 1), 4.0);

  // Test deep copy
  m1(0, 0) = 99.0;
  EXPECT_DOUBLE_EQ(m2(0, 0), 1.0);  // m2 should be unchanged
}

TEST(Operator, AssignmentOperatorSelfAssignment) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m = m;  // Self-assignment should work

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
}

TEST(Operator, AssignmentOperatorChaining) {
  S21Matrix m1(2, 2), m2, m3;
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  m3 = m2 = m1;  // Chained assignment

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m1 == m3);
  EXPECT_TRUE(m2 == m3);
}

// ====================   ==   ====================
TEST(Operator, EqualityOperatorTrue) {
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

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m1);
}

TEST(Operator, EqualityOperatorFalse) {
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

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m2 == m1);
}

TEST(Operator, EqualityEmptyMatrices) {
  S21Matrix m1;
  S21Matrix m2;

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m1);
}

TEST(Operator, EqualityDifferentDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 3);
  S21Matrix m3(3, 2);

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m2 == m3);
}

TEST(Operator, EqualitySameDimensionsDifferentValues) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = 2.0;
  m2(1, 0) = 3.0;
  m2(1, 1) = 5.0;  // Different

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m2 == m1);
}

TEST(Operator, EqualityPrecisionComparison) {
  S21Matrix m1(1, 1);
  S21Matrix m2(1, 1);
  m1(0, 0) = 1.0000000001;
  m2(0, 0) = 1.0000000002;

  // Should be equal within reasonable precision
  EXPECT_TRUE(m1 == m2);

  m2(0, 0) = 1.0001;
  EXPECT_FALSE(m1 == m2);
}

TEST(Operator, EqualityIdentityComparison) {
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

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m1);

  // Compare with self
  EXPECT_TRUE(m1 == m1);
}

// ==================== EDGE CASE TESTS ====================
TEST(Operator, ScalarMultiplicationWithNaN) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m *= NAN;

  EXPECT_TRUE(std::isnan(m(0, 0)));
  EXPECT_TRUE(std::isnan(m(0, 1)));
  EXPECT_TRUE(std::isnan(m(1, 0)));
  EXPECT_TRUE(std::isnan(m(1, 1)));
}

TEST(Operator, ScalarMultiplicationWithInfinity) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m *= INFINITY;

  EXPECT_TRUE(std::isinf(m(0, 0)));
  EXPECT_TRUE(std::isinf(m(0, 1)));
  EXPECT_TRUE(std::isinf(m(1, 0)));
  EXPECT_TRUE(std::isinf(m(1, 1)));
}
