#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

#include "edge_inference/preprocessing.hpp"

BOOST_AUTO_TEST_SUITE(PreprocessingTest)

BOOST_AUTO_TEST_CASE(ProducesFixedWidthTensor) {
  const edge_inference::Tensor tensor =
      edge_inference::preprocess({0.1f, 0.2f, 0.3f});
  BOOST_CHECK_EQUAL(tensor.shape.size(), 2u);
  BOOST_CHECK_EQUAL(tensor.shape[1], edge_inference::kInputSize);
  BOOST_CHECK_EQUAL(tensor.data.size(), edge_inference::kInputSize);
}

BOOST_AUTO_TEST_CASE(NormalizesToUnitRange) {
  const edge_inference::Tensor tensor = edge_inference::preprocess(
      {0.2f, 0.4f, 0.6f, 0.8f, 0.3f, 0.5f, 0.7f, 0.9f});
  const auto bounds = std::minmax_element(tensor.data.begin(), tensor.data.end());
  BOOST_CHECK(std::fabs(*bounds.first - 0.0f) < 1e-5f);
  BOOST_CHECK(std::fabs(*bounds.second - 1.0f) < 1e-5f);
}

BOOST_AUTO_TEST_SUITE_END()
