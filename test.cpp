#include <gtest/gtest.h>
#include <NFA.h>

TEST(test_all, test1) {
  string reg = "ab+c.aba.*.bac.+.+*", str = "babc";
  int32_t ans = getAns(reg, str);

  ASSERT_EQ(ans, 3);
}

TEST(test_all, test2) {
  string reg = "acb..bab.c.*.ab.ba.+.+*a.", str = "abbaa";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 5);
}

// проверим как работает функция умножения автоматов

TEST(test_mul, test1) {
  string reg = "aaa..", str = "acaab";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 2);
}

TEST(test_mul, test2) {
  string reg = "abc..", str = "abaabcab";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 3);
}

TEST(test_mul, test3) {
  string reg = "abb..", str = "ccccc";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 0);
}

TEST(test_mul, test4) {
  string reg = "abc..", str = "cab";
  int32_t ans = getAns(reg, str);
  std::cout << ans << "\n";
  ASSERT_EQ(ans, 2);
}

// проверим как работает функция сложения автоматов

TEST(test_add, test1) {
  string reg = "abc..ab.+", str = "abcab";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 3);
}

TEST(test_add, test2) {
  string reg = "abc..ab.+", str = "abababa";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 2);
}

TEST(test_add, test3) {
  string reg = "aa.bb.+", str = "a";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 1);
}

TEST(test_add, test4) {
  string reg = "ab+", str = "ccccc";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 0);
}

// проверим как работает функция для клинни

TEST(test_kleenne, test1) {
  string reg = "ab.*", str = "baba";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 4);
}

TEST(test_kleenne, test2) {
  string reg = "ab.c+*", str = "babca";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 5);
}

TEST(test_kleenne, test3) {
  string reg = "a*", str = "aaaaa";
  int32_t ans = getAns(reg, str);
  ASSERT_EQ(ans, 5);
}

TEST(test_kleenne, test4) {
    string reg = "a*", str = "cccccc";
    int32_t ans = getAns(reg, str);
    ASSERT_EQ(ans, 0);
}
