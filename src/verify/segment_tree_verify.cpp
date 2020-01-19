#include <verifier.hpp>
#include <init_methods/random_init_vector.hpp>
#include <queries/accum_from0.hpp>
#include <queries/random_select.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/segment_tree.hpp>
#include <data/modint.hpp>
#include <data/composite.hpp>
#include <unit_test/test.hpp>
#include <vector>
#include <random>

VERIFY_START() {
  using fp = ds::modint998244353;
  using composite = ds::composite<fp>;
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<composite, niu::segment_tree<composite>>,
      ds::array_wrapper<composite, std::vector<composite>>,
      std::mt19937,
      ds::random_init_vector<composite, 500>,
      500,
      ds::accum_from0<composite>
        >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_accum"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<composite, niu::segment_tree<composite>>,
      ds::array_wrapper<composite, std::vector<composite>>,
      std::mt19937,
      ds::random_init_vector<composite, 500>,
      500,
      ds::update_at<composite>
        >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_update_at"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<composite, niu::segment_tree<composite>>,
      ds::array_wrapper<composite, std::vector<composite>>,
      std::mt19937,
      ds::random_init_vector<composite, 500>,
      500,
      ds::random_select<
        ds::accum_from0<composite>,
        ds::update_at<composite>
        >
      >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_accum0_update"));
  }
}
VERIFY_END();

