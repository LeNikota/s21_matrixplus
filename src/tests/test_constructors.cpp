#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(Constructor, DefaultConstructor) {
  // Test default constructor
  S21Matrix matrix;

  // Should initialize to 0x0 matrix with nullptr
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);

  // Test that accessing elements throws exception
  EXPECT_ANY_THROW(matrix(0, 0));
}

TEST(Constructor, ParameterizedConstructorValid) {
  // Test valid parameterized constructor
  S21Matrix matrix(3, 4);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);

  // Test that all elements are initialized to 0.0
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_DOUBLE_EQ(matrix(i, j), 0.0);
    }
  }
}

TEST(Constructor, ParameterizedConstructorInvalid) {
  // Test invalid dimensions - should throw exceptions
  EXPECT_ANY_THROW(S21Matrix(-1, 5));
  EXPECT_ANY_THROW(S21Matrix(5, -1));
  EXPECT_ANY_THROW(S21Matrix(0, 5));
  EXPECT_ANY_THROW(S21Matrix(5, 0));
  EXPECT_ANY_THROW(S21Matrix(-1, -1));
}

TEST(Constructor, ParameterizedConstructorSingleElement) {
  // Test 1x1 matrix
  S21Matrix matrix(1, 1);

  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 1);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
}

TEST(Constructor, CopyConstructor) {
  // Create original matrix
  S21Matrix original(2, 3);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(0, 2) = 3.0;
  original(1, 0) = 4.0;
  original(1, 1) = 5.0;
  original(1, 2) = 6.0;

  // Test copy constructor
  S21Matrix copy(original);

  // Check dimensions match
  EXPECT_EQ(copy.GetRows(), 2);
  EXPECT_EQ(copy.GetCols(), 3);

  // Check values are copied
  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(copy(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(copy(0, 2), 3.0);
  EXPECT_DOUBLE_EQ(copy(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(copy(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(copy(1, 2), 6.0);

  // Verify it's a deep copy (modifying original shouldn't affect copy)
  original(0, 0) = 99.0;
  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);  // Copy should remain unchanged
}

TEST(Constructor, CopyConstructorEmpty) {
  // Test copying empty matrix
  S21Matrix empty;
  S21Matrix copy(empty);

  EXPECT_EQ(copy.GetRows(), 0);
  EXPECT_EQ(copy.GetCols(), 0);
  EXPECT_ANY_THROW(copy(0, 0));
}

TEST(Constructor, MoveConstructor) {
  // Create original matrix
  S21Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(1, 0) = 3.0;
  original(1, 1) = 4.0;

  // Test move constructor
  S21Matrix moved(std::move(original));

  // Moved matrix should have the data
  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 2);
  EXPECT_DOUBLE_EQ(moved(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(moved(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(moved(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(moved(1, 1), 4.0);

  // Original should be in valid but empty state
  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetCols(), 0);
  EXPECT_ANY_THROW(original(0, 0));
}

TEST(Constructor, MoveConstructorEmpty) {
  // Test moving empty matrix
  S21Matrix empty;
  S21Matrix moved(std::move(empty));

  EXPECT_EQ(moved.GetRows(), 0);
  EXPECT_EQ(moved.GetCols(), 0);
  EXPECT_EQ(empty.GetRows(), 0);
  EXPECT_EQ(empty.GetCols(), 0);
}

TEST(Constructor, Destructor) {
  // Test that destructor properly cleans up memory
  // This is mostly tested through valgrind/sanitizers, but we can test behavior

  {
    S21Matrix matrix(100, 100);  // Large matrix to ensure allocation
    for (int i = 0; i < 100; ++i) {
      for (int j = 0; j < 100; ++j) {
        matrix(i, j) = i * 100.0 + j;
      }
    }
  }  // Destructor called here

  // If destructor works properly, no memory leaks should occur
  // This test passes if no crashes happen

  // Test destructor on empty matrix
  { S21Matrix empty; }  // Should handle nullptr correctly
}

TEST(Constructor, MultipleConstructors) {
  // Test interaction between different constructors

  // Default -> Parameterized
  S21Matrix m1;
  S21Matrix m2(3, 3);

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m2.GetRows(), 3);

  // Parameterized -> Copy
  S21Matrix m3(m2);
  EXPECT_EQ(m3.GetRows(), 3);

  // Copy -> Move
  S21Matrix m4(std::move(m3));
  EXPECT_EQ(m4.GetRows(), 3);
  EXPECT_EQ(m3.GetRows(), 0);  // m3 should be moved-from
}

TEST(Constructor, CopyConstructorSelfAssignment) {
  // Test that copy constructor handles self-copy correctly
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5.0;

  // This should work fine (copying same object)
  S21Matrix copy(matrix);
  EXPECT_DOUBLE_EQ(copy(0, 0), 5.0);
}

TEST(Constructor, ChainedOperations) {
  // Test constructors in complex scenarios
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;

  // Copy -> Modify -> Copy again
  S21Matrix m2(m1);
  m2(0, 0) = 10.0;

  S21Matrix m3(m2);
  EXPECT_DOUBLE_EQ(m3(0, 0), 10.0);
  EXPECT_DOUBLE_EQ(m3(1, 1), 4.0);

  // Move the copy
  S21Matrix m4(std::move(m3));
  EXPECT_DOUBLE_EQ(m4(0, 0), 10.0);
  EXPECT_EQ(m3.GetRows(), 0);  // m3 should be empty
}

//
// ----- Edge case tests -----
//

TEST(Constructor, LargeMatrix) {
  // Test with large matrix (stress test)
  const int size = 1000;
  S21Matrix large(size, size);

  EXPECT_EQ(large.GetRows(), size);
  EXPECT_EQ(large.GetCols(), size);

  // Fill with values
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      large(i, j) = i + j;
    }
  }

  // Test copy constructor with large matrix
  S21Matrix copy(large);
  EXPECT_EQ(copy.GetRows(), size);
  EXPECT_DOUBLE_EQ(copy(999, 999), 1998.0);
}

TEST(Constructor, MoveThenUse) {
  // Test that moved-from object can still be used safely
  S21Matrix original(2, 2);
  original(0, 0) = 42.0;

  S21Matrix moved(std::move(original));

  // Original should be reusable
  original.SetRows(3);
  original.SetCols(3);
  original(0, 0) = 100.0;  // Should work fine

  EXPECT_EQ(original.GetRows(), 3);
  EXPECT_DOUBLE_EQ(original(0, 0), 100.0);
}