#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, ParameterizedConstructor) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}