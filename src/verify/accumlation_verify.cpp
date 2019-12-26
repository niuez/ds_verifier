#include <verifier.hpp>
#include <init_methods/random_init_vector.hpp>
#include <queries/accum_from0.hpp>
#include <array_wrapper/vector.hpp>
#include <array_wrapper/accumulation.hpp>
#include <data/int32.hpp>
#include <unit_test/test.hpp>
#include <vector>
#include <random>

TEST_START() {
  using i32 = ds::int32;
  using accum_verify = ds::verifier<
    ds::array_wrapper<i32, ds::accumulation<i32>>,
    ds::array_wrapper<i32, std::vector<i32>>,
    std::mt19937,
    ds::random_init_vector<i32, 100>,
    300,
    ds::accum_from0_query<i32>
    >;

  std::mt19937 gen(1);
  std::cout << accum_verify()(gen, "accumulation_example1").to_json().dump() << std::endl;
  return 1;
}
TEST_END()

