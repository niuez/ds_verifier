#include <verifier.hpp>
#include <queries/query_process.hpp>
#include <queries/init/init_once.hpp>
#include <queries/init/random_init_vector.hpp>
#include <queries/foldl_from0.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/accumulation.hpp>
#include <data/int32.hpp>
#include <unit_test/test.hpp>
#include <vector>
#include <random>

VERIFY_START() {
  using i32 = ds::int32;
  using foldl_verify = ds::verifier<
    ds::array_wrapper<i32, ds::accumulation<i32>>,
    ds::array_wrapper<i32, std::vector<i32>>,
    std::mt19937,
    ds::init_once<
      ds::random_init_vector<i32, 100>,
      ds::query_process<100, ds::foldl_from0<i32>>
    >
    >;

  std::mt19937 gen(1);
  VERIFY(foldl_verify()(gen, "accumulation"));
}
VERIFY_END();

