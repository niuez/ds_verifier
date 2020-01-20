#include <verifier.hpp>
#include <queries/query_process.hpp>
#include <queries/init/random_init_vector.hpp>
#include <queries/init/init_once.hpp>
#include <queries/foldl_from0.hpp>
#include <queries/foldl_from0_all.hpp>
#include <queries/random_select.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/fenwick_tree.hpp>
#include <data/modint.hpp>
#include <vector>
#include <random>

VERIFY_START() {
  using fp = ds::modint998244353;
  {
    using fen_verify = ds::verifier<
      ds::array_wrapper<fp, niu::fenwick_tree<fp, std::plus<fp>>>,
      ds::array_wrapper<fp, std::vector<fp>>,
      std::mt19937,
      ds::query_process<100, ds::random_init_vector<fp, 500>, ds::foldl_from0_all<fp>>
    >;
    std::mt19937 gen(1);
    VERIFY(fen_verify()(gen, "fenwick_tree_accum0_to_all"));
  }
  {
    using fen_verify = ds::verifier<
      ds::array_wrapper<fp, niu::fenwick_tree<fp, std::plus<fp>>>,
      ds::array_wrapper<fp, std::vector<fp>>,
      std::mt19937,
      ds::init_once<
        ds::random_init_vector<fp, 500>,
        ds::query_process<500,
          ds::foldl_from0<fp>,
          ds::modify_at<fp>
        >
      >
    >;
    std::mt19937 gen(1);
    VERIFY(fen_verify()(gen, "fenwick_tree_accum0_modify_at"));
  }
}
VERIFY_END();

