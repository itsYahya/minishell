#include <gtest/gtest.h>
#include <string>

extern "C" {
	#include "token.h"
}

int test_scan_literal(std::string str)
{
  return scan_literal((char *) str.c_str());
}

#define STR(S) #S 

TEST(scan_literal, basic_input) {
  std::string str = STR('basic');
  ASSERT_EQ(test_scan_literal(str), 7);

  str = STR('basic' ds);
  ASSERT_EQ(test_scan_literal(str), 7);

  str = STR("basic");
  ASSERT_EQ(test_scan_literal(str), 7);

  str = STR("basic" ss);
  ASSERT_EQ(test_scan_literal(str), 7);
}

TEST(scan_literal, chabka) {
  std::string str = STR('bas""ic');
  ASSERT_EQ(test_scan_literal(str), 9);

  str = STR('bas"ds"ic');
  ASSERT_EQ(test_scan_literal(str), 11);

  str = STR("bas''ic");
  ASSERT_EQ(test_scan_literal(str), 9);

  str = STR("bas'ic");
  ASSERT_EQ(test_scan_literal(str), 8);
}
