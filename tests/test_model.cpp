#include <boost/test/unit_test.hpp>

#include <limits>
#include <vector>

#include "edge_inference/model.hpp"
#include "edge_inference/preprocessing.hpp"

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(ProducesThreeRankings) {
  const edge_inference::Model model;
  const edge_inference::Tensor input =
      edge_inference::preprocess({0.1f, 0.4f, 0.7f, 0.2f, 0.9f, 0.3f, 0.6f, 0.5f});
  const edge_inference::InferenceResult result = model.infer(input);
  BOOST_CHECK(result.ok());
  BOOST_CHECK_EQUAL(result.rankings.size(), 3u);
}

BOOST_AUTO_TEST_CASE(RejectsNonFiniteInput) {
  edge_inference::Tensor input;
  input.shape = {1, edge_inference::kInputSize};
  input.data.assign(edge_inference::kInputSize, 0.5f);
  input.data[2] = std::numeric_limits<float>::infinity();

  const edge_inference::Model model;
  BOOST_CHECK(!model.infer(input).ok());
}

BOOST_AUTO_TEST_CASE(RejectsWrongShape) {
  edge_inference::Tensor input;
  input.shape = {1, 1};
  input.data = {0.5f};

  const edge_inference::Model model;
  BOOST_CHECK(!model.infer(input).ok());
}

BOOST_AUTO_TEST_SUITE_END()
