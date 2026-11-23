#include <boost/test/unit_test.hpp>

#include <vector>

#include "edge_inference/postprocessing.hpp"

BOOST_AUTO_TEST_SUITE(PostprocessingTest)

BOOST_AUTO_TEST_CASE(ArgmaxIncludesFirstClass) {
  const edge_inference::Prediction best =
      edge_inference::argmax({0.9f, 0.2f, 0.1f});
  BOOST_CHECK_EQUAL(best.label, 0u);
}

BOOST_AUTO_TEST_CASE(RankOrdersByConfidence) {
  const std::vector<edge_inference::Prediction> ranked =
      edge_inference::rank({0.1f, 0.9f, 0.5f});
  BOOST_CHECK_EQUAL(ranked.size(), 3u);
  BOOST_CHECK_EQUAL(ranked[0].label, 1u);
  BOOST_CHECK(ranked[0].confidence >= ranked[1].confidence);
}

BOOST_AUTO_TEST_CASE(EmptyScoresProduceEmptyRanking) {
  BOOST_CHECK(edge_inference::rank({}).empty());
}

BOOST_AUTO_TEST_SUITE_END()
