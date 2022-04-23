#include <gtest/gtest.h>
#include <string>

extern "C" {
	#include "token.h"
}

int test_scan_word(std::string str)
{
  return scan_word((char *) str.c_str());
}


TEST(scan_word, basic_input) {
  std::string str = "test1";
  ASSERT_EQ(test_scan_word(str), 5);

  str = "test1 test2";
  ASSERT_EQ(test_scan_word(str), 5);

  str = " test1 test2";
  ASSERT_EQ(test_scan_word(str), 0);
}

TEST(scan_word, special) {
  std::string str = "test1_t$est2";
  ASSERT_EQ(test_scan_word(str), 7);

  str = "tes*t1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "tes|t1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "tes<t1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "tes&&t1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "tes>t1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "tes&hjd ds";
  ASSERT_EQ(test_scan_word(str), 7);
}

TEST(scan_word, qoutes) {
  std::string str = "\"test1 test2\"";

  str = "tes't1 test2' test3";
  ASSERT_EQ(test_scan_word(str), 3);

  str = "test1\"test2' test3";
  ASSERT_EQ(test_scan_word(str), 5);
}
