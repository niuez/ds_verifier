#include <verifier.hpp>
#include <queries/init/init_once.hpp>
#include <queries/query_process.hpp>
#include <queries/init/random_init_vector.hpp>
#include <queries/foldl_from0.hpp>
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
      1,
      ds::init_once<
        ds::random_init_vector<composite, 500>,
        ds::query_process<500, ds::foldl_from0<composite>>
      >
    >;
    VERIFY(seg_verify()("segment_tree_foldl0"));
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
}
VERIFY_END();

