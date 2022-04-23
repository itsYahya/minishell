#include <gtest/gtest.h>
#include <string>

extern "C" {
	#include "token.h"
}

int test_scan_var(std::string str)
{
  return scan_var((char *) str.c_str());
}


TEST(scan_var, basic_input) {
  std::string str = "$var";
  ASSERT_EQ(test_scan_var(str), 4);

  str = "$1 r";
  ASSERT_EQ(test_scan_var(str), 2);

  str = "$? r";
  ASSERT_EQ(test_scan_var(str), 2);
}

TEST(scan_var, chabka) {
  std::string str = "$21232";
  ASSERT_EQ(test_scan_var(str), 2);

  str = "$2whatever";
  ASSERT_EQ(test_scan_var(str), 2);

  str = "$var34 sd";
  ASSERT_EQ(test_scan_var(str), 6);

  str = "$var_one ";
  ASSERT_EQ(test_scan_var(str), 8);

  str = "$var??sa";
  ASSERT_EQ(test_scan_var(str), 4);

  str = "$var@@";
  ASSERT_EQ(test_scan_var(str), 4);

  str = "$var|";
  ASSERT_EQ(test_scan_var(str), 4);
}
