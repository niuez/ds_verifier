#include <verifier.hpp>
#include <queries/init/init_once.hpp>
#include <queries/query_process.hpp>
#include <queries/init/random_init_vector.hpp>
#include <queries/foldl_from0.hpp>
#include <queries/foldl_from0_all.hpp>
#include <queries/foldl_range.hpp>
#include <queries/random_select.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/segment_tree.hpp>
#include <array_wrapper/fenwick_tree.hpp>
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
      1,
      ds::query_process<
        10,
        ds::random_init_vector<composite, 500>,
        ds::foldl_from0_all<composite>
      >
    >;
    VERIFY(seg_verify()("segment_tree_foldl0_all"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<composite, niu::segment_tree<composite>>,
      ds::array_wrapper<composite, std::vector<composite>>,
      std::mt19937,
      1,
      ds::init_once<
        ds::random_init_vector<composite, 500>,
        ds::query_process<500,
          ds::random_select<
            ds::foldl_from0<composite>,
            ds::update_at<composite>
          >
        >
      >
    >;
    VERIFY(seg_verify()("segment_tree_foldl0_update_at"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<composite, niu::segment_tree<composite>>,
      ds::array_wrapper<composite, std::vector<composite>>,
      std::mt19937,
      1,
      ds::init_once<
        ds::random_init_vector<composite, 500>,
        ds::query_process<500,
          ds::random_select<
            ds::foldl_range<composite>,
            ds::update_at<composite>
          >
        >
      >
    >;
    VERIFY(seg_verify()("segment_tree_foldl_range_update_at"));
  }
  {
    using seg_verify = ds::verifier<
      ds::array_wrapper<fp, niu::segment_tree<fp>>,
      ds::array_wrapper<fp, niu::fenwick_tree<fp, std::plus<fp>>>,
      std::mt19937,
      1,
      ds::init_once<
        ds::random_init_vector<fp, 2000>,
        ds::query_process<2000,
          ds::random_select<
            ds::foldl_range<fp>,
            ds::modify_at<fp>
          >
        >
      >
    >;
    VERIFY(seg_verify()("segment_tree_foldl_range_update_at"));
  }
}
VERIFY_END();

