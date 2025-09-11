#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix matrixA(2, 2);
  S21Matrix matrixB(2, 2);

  matrixA(0, 0) = 1;
  matrixA(0, 1) = 2;
  matrixA(1, 0) = 3;
  matrixA(1, 1) = 4;

  matrixB(0, 0) = 5;
  matrixB(0, 1) = 6;
  matrixB(1, 0) = 7;
  matrixB(1, 1) = 8;

  matrixA.SumMatrix(matrixB);

  EXPECT_EQ(matrixA(0, 0), 6);
  EXPECT_EQ(matrixA(0, 1), 8);
  EXPECT_EQ(matrixA(1, 0), 10);
  EXPECT_EQ(matrixA(1, 1), 12);
}
