#include <boost/test/unit_test.hpp>

#include <cstddef>
#include <vector>

#include "mini_infer/argmax.hpp"

BOOST_AUTO_TEST_SUITE(ArgmaxTest)

BOOST_AUTO_TEST_CASE(FindsLargestValue) {
  const std::vector<double> values{1.0, 3.0, 2.0};
  BOOST_CHECK_EQUAL(mini_infer::argmax(values), 1u);
}

BOOST_AUTO_TEST_CASE(StartsAtIndexZero) {
  const std::vector<double> values{9.0, 1.0, 2.0};
  BOOST_CHECK_EQUAL(mini_infer::argmax(values), 0u);
}

BOOST_AUTO_TEST_CASE(FirstMaximumWinsTie) {
  const std::vector<double> values{1.0, 5.0, 5.0, 2.0};
  BOOST_CHECK_EQUAL(mini_infer::argmax(values), 1u);
}

BOOST_AUTO_TEST_CASE(EmptyInputReturnsZero) {
  const std::vector<double> values;
  BOOST_CHECK_EQUAL(mini_infer::argmax(values), 0u);
}

BOOST_AUTO_TEST_CASE(SingleElementReturnsZero) {
  const std::vector<double> values{42.0};
  BOOST_CHECK_EQUAL(mini_infer::argmax(values), 0u);
}

BOOST_AUTO_TEST_SUITE_END()
