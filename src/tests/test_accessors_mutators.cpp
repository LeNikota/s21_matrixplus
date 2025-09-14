#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(AccessorMutatorTests, GetRowsGetColsBasic) {
  // Test basic getters
  S21Matrix matrix(3, 4);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(AccessorMutatorTests, GetRowsGetColsEmpty) {
  // Test getters on empty matrix
  S21Matrix matrix;

  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(AccessorMutatorTests, SetRowsIncrease) {
  // Test increasing rows
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  matrix.SetRows(4);

  EXPECT_EQ(matrix.GetRows(), 4);
  EXPECT_EQ(matrix.GetCols(), 3);

  // Original values should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 6.0);

  // New rows should be filled with zeros
  EXPECT_DOUBLE_EQ(matrix(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(3, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(3, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(3, 2), 0.0);
}

TEST(AccessorMutatorTests, SetRowsDecrease) {
  // Test decreasing rows
  S21Matrix matrix(4, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;
  matrix(3, 0) = 10.0;
  matrix(3, 1) = 11.0;
  matrix(3, 2) = 12.0;

  matrix.SetRows(2);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);

  // Only first 2 rows should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 6.0);

  // Rows 2 and 3 should be gone (test that accessing them throws)
  EXPECT_ANY_THROW(matrix(2, 0));
  EXPECT_ANY_THROW(matrix(3, 0));
}

TEST(AccessorMutatorTests, SetRowsSame) {
  // Test setting same number of rows
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 6.0;

  matrix.SetRows(3);  // Same as current

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 2);

  // All values should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(2, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 6.0);
}

TEST(AccessorMutatorTests, SetRowsToZero) {
  // Test setting rows to zero
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetRows(0);

  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 2);  // Columns should remain unchanged

  // Matrix should be empty (no elements accessible)
  EXPECT_ANY_THROW(matrix(0, 0));
}

TEST(AccessorMutatorTests, SetRowsInvalid) {
  // Test invalid row values
  S21Matrix matrix(2, 2);

  EXPECT_ANY_THROW(matrix.SetRows(-1));
  EXPECT_ANY_THROW(matrix.SetRows(-100));
}

TEST(AccessorMutatorTests, SetColsIncrease) {
  // Test increasing columns
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetCols(4);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 4);

  // Original values should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);

  // New columns should be filled with zeros
  EXPECT_DOUBLE_EQ(matrix(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(0, 3), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 3), 0.0);
}

TEST(AccessorMutatorTests, SetColsDecrease) {
  // Test decreasing columns
  S21Matrix matrix(2, 4);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(0, 3) = 4.0;
  matrix(1, 0) = 5.0;
  matrix(1, 1) = 6.0;
  matrix(1, 2) = 7.0;
  matrix(1, 3) = 8.0;

  matrix.SetCols(2);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 2);

  // Only first 2 columns should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 6.0);

  // Columns 2 and 3 should be gone (test that accessing them throws)
  EXPECT_ANY_THROW(matrix(0, 2));
  EXPECT_ANY_THROW(matrix(0, 3));
}

TEST(AccessorMutatorTests, SetColsSame) {
  // Test setting same number of columns
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  matrix.SetCols(3);  // Same as current

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);

  // All values should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 6.0);
}

TEST(AccessorMutatorTests, SetColsToZero) {
  // Test setting columns to zero
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetCols(0);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 0);

  // Matrix should have rows but no columns (no elements accessible)
  EXPECT_ANY_THROW(matrix(0, 0));
  EXPECT_ANY_THROW(matrix(1, 0));
}

TEST(AccessorMutatorTests, SetColsInvalid) {
  // Test invalid column values
  S21Matrix matrix(2, 2);

  EXPECT_ANY_THROW(matrix.SetCols(-1));
  EXPECT_ANY_THROW(matrix.SetCols(-100));
}

TEST(AccessorMutatorTests, SetBothRowsAndCols) {
  // Test setting both rows and columns
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetRows(3);
  matrix.SetCols(3);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);

  // Original values should be preserved
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);

  // New elements should be zeros
  EXPECT_DOUBLE_EQ(matrix(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 2), 0.0);
}

TEST(AccessorMutatorTests, SetOnEmptyMatrix) {
  // Test setting dimensions on empty matrix
  S21Matrix matrix;

  matrix.SetRows(2);
  matrix.SetCols(3);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);

  // All elements should be zeros
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(matrix(i, j), 0.0);
    }
  }
}

TEST(AccessorMutatorTests, ConstGetRowsGetCols) {
  // Test that getters work on const objects
  const S21Matrix matrix(5, 7);

  EXPECT_EQ(matrix.GetRows(), 5);
  EXPECT_EQ(matrix.GetCols(), 7);
}

TEST(AccessorMutatorTests, MultipleResizeOperations) {
  // Test multiple resize operations
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 42.0;

  matrix.SetRows(2);
  matrix.SetCols(2);
  matrix.SetRows(3);
  matrix.SetCols(1);
  matrix.SetRows(1);

  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 1);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 42.0);  // Original value should survive
}

TEST(AccessorMutatorTests, LargeResize) {
  // Test large resize operations
  S21Matrix matrix(10, 10);

  // Fill with values
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      matrix(i, j) = i + j;
    }
  }

  matrix.SetRows(5);
  matrix.SetCols(20);

  EXPECT_EQ(matrix(0, 0), 0);
  EXPECT_EQ(matrix(2, 4), 6);
  EXPECT_EQ(matrix(4, 4), 8);
  EXPECT_EQ(matrix(4, 10), 0);
  EXPECT_EQ(matrix(4, 19), 0);

  EXPECT_ANY_THROW(matrix(9, 0));
  EXPECT_ANY_THROW(matrix(9, 9));
}
