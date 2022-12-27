#pragma once

#include "Lib/redbud/io/color.h"

#define green redbud::io::state::manual << redbud::io::hfg::green
#define red redbud::io::state::manual << redbud::io::hfg::red

#define EXPECT_EQ(v1, v2) do { \
  if (v1 == v2) {                                               \
    std::cout << green << " EXPECT_EQ succeeded!\n";            \
  }                                                             \
  else {                                                        \
    std::cout << red << " EXPECT_EQ failed!\n";                 \
    std::cout << red << " Expect:" << v1 << "\n";               \
    std::cout << red << " Actual:" << v2 << "\n";               \
}} while(0)




#define PASSED std::cout << "[ PASSED ]\n"

#define EXPECT_EQUAL 1