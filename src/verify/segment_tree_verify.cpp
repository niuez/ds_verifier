#include <verifier.hpp>
#include <init_methods/random_init_vector.hpp>
#include <queries/accum_from0.hpp>
#include <queries/random_choise.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/segment_tree.hpp>
#include <data/int32.hpp>
#include <unit_test/test.hpp>
#include <vector>
#include <random>

VERIFY_START() {
  using i32 = ds::int32;
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<i32, niu::segment_tree<i32>>,
      ds::array_wrapper<i32, std::vector<i32>>,
      std::mt19937,
      ds::random_init_vector<i32, 500>,
      500,
      ds::accum_from0<i32>
        >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_accum"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<i32, niu::segment_tree<i32>>,
      ds::array_wrapper<i32, std::vector<i32>>,
      std::mt19937,
      ds::random_init_vector<i32, 500>,
      500,
      ds::update_at<i32>
        >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_update_at"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<i32, niu::segment_tree<i32>>,
      ds::array_wrapper<i32, std::vector<i32>>,
      std::mt19937,
      ds::random_init_vector<i32, 500>,
      500,
      ds::random_choise<
        ds::accum_from0<i32>,
        ds::update_at<i32>
        >
      >;

    std::mt19937 gen(1);
    VERIFY(seg_verify()(gen, "segment_tree_accum0_update"));
  }
}
VERIFY_END();

