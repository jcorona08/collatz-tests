// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <map>

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// ----
// read
// ----

TEST(CollatzFixture, read) {
  istringstream r("1 10\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, i);
  ASSERT_EQ(10, j);
}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
  const int v = collatz_eval(1, 10);
  ASSERT_EQ(20, v);
}

TEST(CollatzFixture, eval_2) {
  const int v = collatz_eval(100, 200);
  ASSERT_EQ(125, v);
}

TEST(CollatzFixture, eval_3) {
  const int v = collatz_eval(201, 210);
  ASSERT_EQ(89, v);
}

TEST(CollatzFixture, eval_4) {
  const int v = collatz_eval(900, 1000);
  ASSERT_EQ(174, v);
}

// test two lowest cases
TEST(CollatzFixture, eval_5) {
  const int v = collatz_eval(1, 2);
  ASSERT_EQ(2, v);
}

// test wide range
TEST(CollatzFixture, eval_6) {
  const int v = collatz_eval(1, 1000);
  ASSERT_EQ(179, v);
}

// test cache reads instead of computation
TEST(CollatzFixture, eval_7) {
  const int v = collatz_eval(500, 1000);
  ASSERT_EQ(179, v);
}

// test large range + inverted floor/ceiling
TEST(CollatzFixture, eval_8) {
  const int v = collatz_eval(20000, 1000);
  ASSERT_EQ(279, v);
}

// test 1 against itself - base case?
TEST(CollatzFixture, eval_9) {
  const int v = collatz_eval(1, 1);
  ASSERT_EQ(1, v);
}

// -----
// logic
// -----

// test lowest value function receives
TEST(CollatzFixture, logic_1) {
  const int l = collatz_logic(2);
  ASSERT_EQ(1, l);
}

// test odds
TEST(CollatzFixture, logic_2) {
  const int l = collatz_logic(3);
  ASSERT_EQ(10, l);
}

// test large number
TEST(CollatzFixture, logic_3) {
  const int l = collatz_logic(100001);
  ASSERT_EQ(300004, l);
}

// -----
// print
// -----

TEST(CollatzFixture, print_1) {
  ostringstream w;
  collatz_print(w, 1, 10, 20);
  ASSERT_EQ("1 10 20\n", w.str());
}

// test inverted floor/ceiling prints correctly
TEST(CollatzFixture, print_2) {
  ostringstream w;
  collatz_print(w, 20000, 1000, 279);
  ASSERT_EQ("20000 1000 279\n", w.str());
}

// test using same number prints correctly
TEST(CollatzFixture, print_3) {
  ostringstream w;
  collatz_print(w, 1, 1, 1);
  ASSERT_EQ("1 1 1\n", w.str());
}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
  istringstream r("1 10\n100 200\n201 210\n900 1000\n1 2\n1 1000\n500 "
                  "1000\n20000 1000\n1 1\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n1 2 2\n1 1000 "
            "179\n500 1000 179\n20000 1000 279\n1 1 1\n",
            w.str());
}
