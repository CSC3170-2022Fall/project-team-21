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

#define EXPECT_CON_EQ(c1, c2) do {                                  \
  auto first1 = std::begin(c1), last1 = std::end(c1);               \
  auto first2 = std::begin(c2), last2 = std::end(c2);               \
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {  \
    if (*first1 != *first2)  break;                                 \
  }                                                                 \
  if (first1 == last1 && first2 == last2) {                         \
    std::cout << green << " EXPECT_CON_EQ succeeded!\n";            \
  }                                                                 \
  else {                                                            \
    std::cout << red << " EXPECT_CON_EQ failed!\n";                 \
    std::cout << red << " Expect:" << *first1 << "\n";              \
    std::cout << red << " Actual:" << *first2 << "\n";              \
}} while(0)

#define COUT(container, container_name) do {                             \
  std::cout << " " << container_name << " :";                  \
  for (auto it : container)                              \
    std::cout << " " << it;                              \
  std::cout << "\n";                                     \
} while(0)

#define PASSED std::cout << "[ PASSED ]\n"