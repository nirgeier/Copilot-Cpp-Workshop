#include <boost/test/unit_test.hpp>

#include <cmath>
#include <vector>

#include "mini_infer/normalize.hpp"

namespace {

void check_close(double actual, double expected) {
  BOOST_CHECK(std::fabs(actual - expected) < 1e-12);
}

}  // namespace

BOOST_AUTO_TEST_SUITE(NormalizeTest)

BOOST_AUTO_TEST_CASE(MapsRangeToUnitInterval) {
  std::vector<double> values{2.0, 4.0, 6.0};
  BOOST_REQUIRE(mini_infer::normalize(values));
  BOOST_REQUIRE_EQUAL(values.size(), 3u);
  check_close(values[0], 0.0);
  check_close(values[1], 0.5);
  check_close(values[2], 1.0);
}

BOOST_AUTO_TEST_CASE(HandlesNegativeValues) {
  std::vector<double> values{-10.0, 0.0, 10.0};
  BOOST_REQUIRE(mini_infer::normalize(values));
  check_close(values[0], 0.0);
  check_close(values[1], 0.5);
  check_close(values[2], 1.0);
}

BOOST_AUTO_TEST_CASE(ConstantInputIsRejectedAndUnchanged) {
  std::vector<double> values{5.0, 5.0, 5.0};
  BOOST_CHECK(!mini_infer::normalize(values));
  BOOST_CHECK_EQUAL(values[0], 5.0);
  BOOST_CHECK_EQUAL(values[1], 5.0);
  BOOST_CHECK_EQUAL(values[2], 5.0);
}

BOOST_AUTO_TEST_CASE(EmptyInputIsRejected) {
  std::vector<double> values;
  BOOST_CHECK(!mini_infer::normalize(values));
  BOOST_CHECK(values.empty());
}

BOOST_AUTO_TEST_CASE(SingleValueIsConstant) {
  std::vector<double> values{7.0};
  BOOST_CHECK(!mini_infer::normalize(values));
  BOOST_CHECK_EQUAL(values[0], 7.0);
}

BOOST_AUTO_TEST_SUITE_END()
