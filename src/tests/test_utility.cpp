#include <stdexcept>

#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

// GetMinor Tests
TEST(GetMinor, Basic3x3) {
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

  S21Matrix minor = m.GetMinor(1, 1);  // Remove row 1, column 1

  EXPECT_EQ(minor.GetRows(), 2);
  EXPECT_EQ(minor.GetCols(), 2);
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST(GetMinor, TopLeftCorner) {
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

  S21Matrix minor = m.GetMinor(0, 0);  // Remove row 0, column 0

  EXPECT_EQ(minor.GetRows(), 2);
  EXPECT_EQ(minor.GetCols(), 2);
  EXPECT_DOUBLE_EQ(minor(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 8.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST(GetMinor, BottomRightCorner) {
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

  S21Matrix minor = m.GetMinor(2, 2);  // Remove row 2, column 2

  EXPECT_EQ(minor.GetRows(), 2);
  EXPECT_EQ(minor.GetCols(), 2);
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 5.0);
}

TEST(GetMinor, CenterElement4x4) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(0, 3) = 4.0;
  m(1, 0) = 5.0;
  m(1, 1) = 6.0;
  m(1, 2) = 7.0;
  m(1, 3) = 8.0;
  m(2, 0) = 9.0;
  m(2, 1) = 10.0;
  m(2, 2) = 11.0;
  m(2, 3) = 12.0;
  m(3, 0) = 13.0;
  m(3, 1) = 14.0;
  m(3, 2) = 15.0;
  m(3, 3) = 16.0;

  S21Matrix minor = m.GetMinor(1, 2);  // Remove row 1, column 2

  EXPECT_EQ(minor.GetRows(), 3);
  EXPECT_EQ(minor.GetCols(), 3);

  // Expected minor matrix:
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(minor(0, 2), 4.0);

  EXPECT_DOUBLE_EQ(minor(1, 0), 9.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 10.0);
  EXPECT_DOUBLE_EQ(minor(1, 2), 12.0);

  EXPECT_DOUBLE_EQ(minor(2, 0), 13.0);
  EXPECT_DOUBLE_EQ(minor(2, 1), 14.0);
  EXPECT_DOUBLE_EQ(minor(2, 2), 16.0);
}

TEST(GetMinor, NonSquareMatrix) {
  S21Matrix m(3, 4);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(0, 3) = 4.0;
  m(1, 0) = 5.0;
  m(1, 1) = 6.0;
  m(1, 2) = 7.0;
  m(1, 3) = 8.0;
  m(2, 0) = 9.0;
  m(2, 1) = 10.0;
  m(2, 2) = 11.0;
  m(2, 3) = 12.0;

  S21Matrix minor = m.GetMinor(1, 2);

  EXPECT_EQ(minor.GetRows(), 2);
  EXPECT_EQ(minor.GetCols(), 3);

  // Expected minor after removing row 1, column 2:
  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(minor(0, 2), 4.0);

  EXPECT_DOUBLE_EQ(minor(1, 0), 9.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 10.0);
  EXPECT_DOUBLE_EQ(minor(1, 2), 12.0);
}

TEST(GetMinor, 2x2Matrix) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  S21Matrix minor = m.GetMinor(0, 0);

  EXPECT_EQ(minor.GetRows(), 1);
  EXPECT_EQ(minor.GetCols(), 1);
  EXPECT_DOUBLE_EQ(minor(0, 0), 4.0);
}

TEST(GetMinor, OutOfBoundsAccess) {
  S21Matrix m(3, 4);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(0, 3) = 4.0;
  m(1, 0) = 5.0;
  m(1, 1) = 6.0;
  m(1, 2) = 7.0;
  m(1, 3) = 8.0;
  m(2, 0) = 9.0;
  m(2, 1) = 10.0;
  m(2, 2) = 11.0;
  m(2, 3) = 12.0;

  EXPECT_ANY_THROW(m.GetMinor(-1, -1));
  EXPECT_ANY_THROW(m.GetMinor(3, 4));
  EXPECT_ANY_THROW(m.GetMinor(4, 4));
}

TEST(GetMinor, EmptyMatrix) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.GetMinor(0, 0));
  EXPECT_ANY_THROW(m.GetMinor(1, 1));
}

TEST(GetMinor, 1x1Matrix) {
  S21Matrix m(1, 1);

  EXPECT_ANY_THROW(m.GetMinor(0, 0));
}